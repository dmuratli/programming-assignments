#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <fcntl.h>
#include <cstdio>

using namespace std;

struct thread_args{
    int fd;
    pthread_mutex_t lck;
};

vector<vector<string>> parse_cmd_file(const string &file_name){ // Parses commands from a text file
    vector<vector<string>> cmd_list;

    ifstream cmd_file(file_name.c_str());

    if (cmd_file.is_open()){
        string line, item;

        while(getline(cmd_file, line)){
            istringstream line_content(line);
            
            vector<string> cmd_params;

            while (line_content >> item){
                cmd_params.push_back(item);
            }

            if (cmd_params.empty() != true){
                cmd_list.push_back(cmd_params);
            }else{
                ;
            }
        }
    }else{
        perror("The file could not be opened.");
        exit(EXIT_FAILURE);
    }

    cmd_file.close();

    return cmd_list;
}

vector<vector<vector<string>>> parse_cmd_contents(const vector<vector<string>> &cmd_list){ // Loads commands and their arguments into an organised array/vector
    // For each element in cmd_contents:
    // 0: cmd-name, 1: inputs, 2: options, 3: redirection (sign and file name), 4: state (background job or not)
    
    vector<vector<vector<string>>> cmd_params;

    for (int i = 0; i < cmd_list.size(); i++){
        vector<string> cmd_name, redirection, bg_job, inputs, options;

        for (int j = 0; j < cmd_list[i].size(); j++){
            if (j == 0){
                cmd_name.push_back(cmd_list[i][j]);
                
                if (cmd_list[i][j] == "wait"){
                    break;
                }else{
                    ;
                }
            }else{
                if (cmd_list[i][j][0] == '-'){
                    options.push_back(cmd_list[i][j]);
                }else if (cmd_list[i][j] == ">" || cmd_list[i][j] == "<"){
                    redirection.push_back(cmd_list[i][j]);
                    redirection.push_back(cmd_list[i][j + 1]);
                }else if (cmd_list[i][j] == "&"){
                    bg_job.push_back(cmd_list[i][j]);
                }else{
                    if (cmd_list[i][j - 1] != "<" && cmd_list[i][j - 1] != ">"){
                        inputs.push_back(cmd_list[i][j]);
                    }else{
                        ;
                    }
                }
            }
        }
        vector<vector<string>> sub_cmd_params;
        sub_cmd_params.push_back(cmd_name);
        sub_cmd_params.push_back(inputs);
        sub_cmd_params.push_back(options);
        sub_cmd_params.push_back(redirection);
        sub_cmd_params.push_back(bg_job);

        cmd_params.push_back(sub_cmd_params);
    }

    return cmd_params;
}

void print_header(const vector<vector<string>> &cmd_content, ofstream &output_file){ // Prints information about the command being executed to the given output file
    output_file << "----------" << endl;

    output_file << "Command: " << cmd_content[0][0] << endl;

    output_file << "Inputs: ";
    for (int i = 0; i < cmd_content[1].size(); i++){
        output_file << cmd_content[1][i] << " ";
    }
    output_file << endl;

    output_file << "Options: ";
    for (int i = 0; i < cmd_content[2].size(); i++){
        output_file << cmd_content[2][i] << " ";
    }
    output_file << endl;

    output_file << "Redirection: ";
    if (cmd_content[3].empty() == false){
        output_file << cmd_content[3][0];
    }else{
        ;
    }
    output_file << endl;

    output_file << "Background Job: ";
    if (cmd_content[4].empty() == false && cmd_content[4][0] == "&"){
        output_file << "y";
    }else{
        output_file << "n";
    }
    output_file << endl;
    
    output_file << "----------" << endl;

    output_file.flush();
}

void escape_special_chr(string &str, char special_chr) {
    if (str.empty() == false && str[0] == special_chr && str[str.size() - 1] == special_chr){
        str = str.substr(1, str.size() - 2);
    }
}

vector<char*> create_arg_array(vector<vector<string>> &cmd_content) {
    vector<char*> args;
    vector<string> modifiedInputs; // Store modified strings

    args.push_back(const_cast<char*>(cmd_content[0][0].c_str())); // Command

    for (int i = 0; i < cmd_content[2].size(); i++){ // Options
        args.push_back(const_cast<char*>(cmd_content[2][i].c_str()));    
    }

    for (int i = 0; i < cmd_content[1].size(); i++){ // Inputs
        if (cmd_content[1][i][0] == '\"' || cmd_content[1][i][0] == '\''){ // The input name is written within quotation marks
            escape_special_chr(cmd_content[1][i], cmd_content[1][i][0]);
            args.push_back(const_cast<char*>(cmd_content[1][i].c_str()));
        }else{
            args.push_back(const_cast<char*>(cmd_content[1][i].c_str()));
        }
    }
    args.push_back(nullptr);
    
    return args;
}

void* listen(void* args){ // Listens to the pipe
    thread_args* new_args = (thread_args*) args;
    bool flag = true;
    FILE* pipe_file;

    while (flag == true){ // Trying to lock while command execution is not yet finished
        pthread_mutex_lock(&(new_args->lck));
        cout << "---- " << pthread_self() << endl;

        pipe_file = fdopen(new_args->fd, "r"); // Reading the pipe
        char buffer[1024];

        if (pipe_file != nullptr){
            while (fgets(buffer, sizeof(buffer), pipe_file) != nullptr){ // Printing the pipe
                cout << buffer;
                cout.flush();
            }
        }else{
            perror("The pipe could not be read.");
            exit(EXIT_FAILURE);
        }

        cout << "---- " << pthread_self() << endl;
        flag = false;
        pthread_mutex_unlock(&(new_args->lck));
    }
    fclose(pipe_file); // Closing the pipe
    
    return NULL;
}

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int main(){
    vector<vector<string>> cmd_list = parse_cmd_file("commands.txt");
    vector<vector<vector<string>>> cmd_contents = parse_cmd_contents(cmd_list);

    ofstream output_file("parse.txt"); // Creating the output file from scratch
    output_file.close();

    ofstream append_file("parse.txt", ios::app); // Switching to append mode

    vector<int> pids; // Child process IDs
    vector<pthread_t> tids; // Thread IDs

    for (int i = 0; i < cmd_contents.size(); i++){ // Going through each command
        vector<vector<string>> cmd_content = cmd_contents[i];
        print_header(cmd_content, append_file);

        if (cmd_content[0][0] == "wait"){ // Waiting for all children to terminate
            for (int j = 0; j < pids.size(); j++){
                waitpid(pids[j], NULL, NULL);
            }
            pids.clear(); // Emptying the array/vector keeping track of running children

            for (int j = 0; j < tids.size(); j++){
                pthread_join(tids[j], NULL);
            }
            tids.clear(); // Emptying the array/vector keeping track of running tids
        }else if (cmd_content[3].empty() == false && cmd_content[3][0] == ">"){ // There is an output redirection
            int rc1 = fork();

            if (rc1 < 0){
                perror("Fork failed!");
                exit(EXIT_FAILURE);
            }else if (rc1 == 0){ // Child process
                vector<char*> args = create_arg_array(cmd_content);

                int output = open(cmd_content[3][1].c_str(), O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU); // Creating the redirected output file
                dup2(output, STDOUT_FILENO); // Replacing STDOUT with the output file
                close(output); // Closing the original output file

                execvp(cmd_content[0][0].c_str(), args.data()); // Running the command
            }else{ // Parent process
                if (cmd_content[4].empty() == false && cmd_content[4][0] == "&"){ // Background job
                    pids.push_back(rc1); // Pushing the child process ID to pids to keep track of it
                }else{ // NOT a background job
                    waitpid(rc1, NULL, NULL); // Waiting for the child
                }
            }
        }else{ // Either no redirection or input redirection
            int fds[2];
            pipe(fds);

            pthread_t listener;

            thread_args* params = new thread_args;
            params->fd = fds[0];
            params->lck = lock;

            int rc2 = fork();

            if (rc2 < 0){
                perror("Fork failed!");
                exit(EXIT_FAILURE);
            }else if (rc2 == 0){ // Child process
                vector<char*> args = create_arg_array(cmd_content);
                
                if (cmd_content[3].empty() == false && cmd_content[3][0] == "<"){ // There is an input redirection
                    int input = open(cmd_content[3][1].c_str(), O_RDONLY); // Opening the redirected input file
                    dup2(input, STDIN_FILENO); // Replacing STDIN with the input file
                    close(input);
                }else{ // No redirection
                    ;
                }
                close(fds[0]); // Closing the read end
                dup2(fds[1], STDOUT_FILENO); // Replacing STDOUT with the pipe
                close(fds[1]); // Closing the write end
                execvp(cmd_content[0][0].c_str(), args.data());
            }else{ // Parent process
                close(fds[1]); // Closing the write end
                pthread_create(&listener, NULL, listen, params);
                if (cmd_content[4].empty() == false && cmd_content[4][0] == "&"){ // Background job
                    pids.push_back(rc2);
                    tids.push_back(listener);
                }else{ // NOT a background job
                    waitpid(rc2, NULL, NULL);
                    pthread_join(listener, NULL);
                }
            }
        }
    }

    output_file.close();

    // Making sure that all processes and threads completed execution
    for (int i = 0; i < pids.size(); i++){
        waitpid(pids[i], NULL, NULL);
    }
    pids.clear();

    for (int i = 0; i < tids.size(); i++){
        pthread_join(tids[i], NULL);
    }
    tids.clear();

    pthread_mutex_destroy(&lock);

    return 0;
}