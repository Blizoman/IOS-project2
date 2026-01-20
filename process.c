#include "process.h"


int process_init(){
    pid_t pid;
    
    // Create ferry process
    pid = fork();
    if (pid == 0){
        ferry_process(); // Calling ferry process function
        exit(VALID);
    }

    // Create truck processes
    for (int idN = 0; idN < args.N; idN++){  // idN - Custom ID of truck
        while(1){
            pid = fork();
            if(pid == -1) wait(NULL);
            else break;
        }
        if (pid == 0){
            srand(time(NULL) * getpid()); // Create random seed for each truck
            truck_process(idN+1, data->portTRUCK = rand() % 2); //Call truck process function
            exit(VALID);
        }
    }

    // Create car processes
    for (int idO = 0; idO < args.O; idO++) {  // idO - Custom ID of car
        while(1){
            pid = fork();
            if(pid == -1) wait(NULL);
            else break;
        }
        if (pid == 0) {
            srand(time(NULL) * getpid()); // Create random seed for each car
            car_process(idO+1, data->portCAR = rand() % 2); //Call car process function
            exit(VALID);
        }
    }

    // Waitingg for all child processes to finish
    for (int i = 0; i < args.N + args.O + 1; i++) { 
        wait(NULL);
    }

    return VALID;
}