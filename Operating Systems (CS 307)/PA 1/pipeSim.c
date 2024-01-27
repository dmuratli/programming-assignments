#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    printf("I'm SHELL process, with PID: %d - Main command is: man ls | grep -e \"-l\" -A 2\n", (int) getpid());

    char * man_arr[3] = {strdup("man"), strdup("ls"), NULL};
    char * grep_arr[6] = {strdup("grep"), strdup("-e"), strdup("-l"), strdup("-A"), strdup("2"), NULL};

    int rc = fork();

    if (rc < 0){ // Failed fork
        fprintf(stderr, "First fork failed!\n");
        exit(1);
    }else if (rc == 0){ 
        int fds[2];
        pipe(fds);

        int rc2 = fork();

        if (rc2 < 0){ // Failed fork
            fprintf(stderr, "Second fork failed!\n");
            exit(1);
        }else if (rc2 == 0){ // Child process
            close(fds[1]); // The write end is closed
            dup2(fds[0], STDIN_FILENO); // STDIN is replaced with pipe input

            printf("I'm GREP process, with PID: %d - My command is: grep -e \"-l\" -A 2\n", (int) getpid());

            // Rewiring STDOUT from the pipe to a file
            close(STDOUT_FILENO); // Changed back to default behaviour
            
            // Writing to a file
            FILE * output_pointer = fopen("output.txt", "w"); // Cannot close the file later because execvp() replaces the code, but that should be ok
            
            if (output_pointer == NULL){
                perror("Error opening the output file!");
                return 1;
            }else{
                execvp("grep", grep_arr);
            }
        }else{ // Parent process
            close(fds[0]); // The read end is closed; EOF

            printf("I'm MAN process, with PID: %d - My command is: man ls\n", (int) getpid());

            dup2(fds[1], STDOUT_FILENO); // STDOUT is replaced with pipe output
            close(fds[1]);

            execvp("man", man_arr);
        }
    }else{ // Shell
        wait(NULL);

        printf("I'm SHELL process, with PID: %d - execution is completed, you can find the results in output.txt\n", (int) getpid());
    }
    return 0;
}