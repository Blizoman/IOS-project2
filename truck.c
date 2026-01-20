#include "truck.h"


void truck_process(int id, int port){

    // Truck starts its journey
    sem_wait(&data->writerMutex); 
    logger("%i: N %i: started\n", data->action_counter++, id);
    sem_post(&data->writerMutex);  
    

    // Random delay simulating time when car arrive to dock
    srand(time(NULL) * getpid());
    usleep(rand() % (args.TA + 1));

    // Truck has arrived at the port
    sem_wait(&data->writerMutex); 
    logger("%i: N %i: arrived to %i\n", data->action_counter++, id, port);
    sem_post(&data->writerMutex);  
    

    // Update the number of cars waiting at the port
    sem_wait(&data->dataMutex);
    if (port == 0) {
        data->doc0.trucks_waiting++; // Increment waiting trucks at port 0
    } else {
        data->doc1.trucks_waiting++; // Increment waiting trucks at port 1
    }
    sem_post(&data->dataMutex);

    // Waiting for the boarding signal
    if(port == 0){
        sem_wait(&data->board_truck_signal0); // Boarding signal at port 0
    }
    else{
        sem_wait(&data->board_truck_signal1); // Boarding signal at port 0
    }
    
    // Boarding the ferry
    sem_wait(&data->writerMutex); 
    logger("%i: N %i: boarding\n", data->action_counter++, id);
    sem_post(&data->writerMutex);  
    
    // Notify that boarding is done
    sem_post(&data->boarding_signal_done);
    


    
    // Switching the actual port to the other after arriving to another
    port = (port+1) % 2;

    // Waiting to unboard
    sem_wait(&data->unboard_truck_signal); //prijme signal z ferry ze sa moze vylodit

    
    sem_wait(&data->writerMutex); 
    logger("%i: N %i: leaving in %i\n", data->action_counter++, id, port);
    sem_post(&data->writerMutex);  

    // Sending a signal to ferry that the unboarding was succesfful
    sem_post(&data->truck_unboard_signal);

    //10
    exit(VALID);
}
