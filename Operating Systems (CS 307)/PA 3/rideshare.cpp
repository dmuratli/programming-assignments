#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <vector>

using namespace std;

bool check_divisibility_by_two(const int &val){ // Checks divisibility by 2
    int rem = val % 2;

    if (rem == 0){
        return true;
    }else{
        return false;
    }
}

bool check_divisibility_by_four(const int &val){ // Checks divisibility by 4
    int rem = val % 4;

    if (rem == 0){
        return true;
    }else{
        return false;
    }
}

struct fan{ // Struct to hold the team information of a given fan
    char team;

    fan(char team): team(team){}
    fan(): team('X'){}
};

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;
int barrier_counter = 0;

int waitlist_A = 0, waitlist_B = 0, cid = 0; // Variables that hold the number of people waiting for a car (for A and B respectively), and the available car ID

void* fan_behaviour(void* arg){ // Function executed by the threads
    fan* person = (fan*) arg;

    pthread_mutex_lock(&lock);
    cout << "Thread ID: " << pthread_self() << ", Team: " << person->team << ", I am looking for a car." << endl;

    if (person->team == 'A'){
        waitlist_A++;
    }else if (person->team == 'B'){
        waitlist_B++;
    }else{
        ;
    }

    if ((waitlist_A >= 2 && waitlist_B >= 2) || waitlist_A == 4 || waitlist_B == 4){ // A rideshare band can be formed
        if (waitlist_A >= 2 && waitlist_B >= 2){
            waitlist_A -= 2;
            waitlist_B -= 2;
        }else if (waitlist_A == 4){
            waitlist_A -= 4;
        } else if (waitlist_B == 4){
            waitlist_B -= 4;
        }else{
            ;
        }
    }else{
        ; // Directly moving on to the barrier
    }

    pthread_mutex_unlock(&lock);

    pthread_barrier_wait(&barrier); // Barrier to hold waiting fans

    pthread_mutex_lock(&lock);

    barrier_counter++;

    cout << "Thread ID: " << pthread_self() << ", Team: " << person->team << ", I have found a spot in a car." << endl;

    if (barrier_counter % 4 == 0){ // Captain
        cout << "Thread ID: " << pthread_self() << ", Team: " << person->team << ", I am the captain and driving the car with ID " << cid << endl;
        cid++;
    }else{ // Passenger
        ; // Hanging out on the seat :)
    }

    pthread_mutex_unlock(&lock);

    delete person;

    return NULL;
}

int main(int argc, char* argv[]){
    if (argc != 3){ // Check for the number of arguments (./rideshare, # of A fans, # of B fans)
        cout << "The main terminates" << endl; // Incorrect number of arguments
        return 0;
    }else{
        vector<bool> checks;
        bool final_check = true;
        int sum = 0;

        for (int i = 1; i < argc; i++){ // Checks for divisibility by 2
            checks.push_back(check_divisibility_by_two(stoi(argv[i])));
            sum += stoi(argv[i]);
        }

        checks.push_back(check_divisibility_by_four(sum)); // Check for divisibility by 4

        for (int i; i < checks.size(); i++){ // Check to see whether all conditions are met
            if (checks[i] == false){
                final_check = false; // Incorrect arguments
                break;
            }else{
                ;
            }
        }

        if (final_check == true){ // Execution can proceed
            int A_count = stoi(argv[1]), B_count = stoi(argv[2]); // Fan counts

            int total_count = A_count + B_count; // Total fan count

            vector<char> teams;
            vector<pthread_t> threads; // Fans

            pthread_barrier_init(&barrier, NULL, 4); // Initialising the barrier for 4 threads

            for (int i = 0; i < A_count; i++){ // Adding 'A' for each A fan
                teams.push_back('A');
            }

            for (int i = 0; i < B_count; i++){ // Adding 'B' for each B fan
                teams.push_back('B');
            }

            for (int i = 0; i < total_count; i++){ // Running the threads (fans)
                pthread_t tid;
                threads.push_back(tid);
                
                fan* person = new fan(teams[i]);
                pthread_create(&threads[i], NULL, fan_behaviour, person);
            }

            for (int i = 0; i < threads.size(); i++){ // Waiting for all threads to complete
                pthread_join(threads[i], NULL);
            }
        }else{ // Incorrect input
            cout << "The main terminates" << endl;
            return 0;
        }

        pthread_barrier_destroy(&barrier); // Unnecessary as the barrier will be destroyed following program termination, but still good practice
    }
    pthread_mutex_destroy(&lock); // Unnecessary as the mutex lock will be destroyed following program termination, but still good practice

    cout << "The main terminates" << endl;
    return 0;
}