#include "car.h"


void car_process(int id, int port){

    // Car starts its journey
    sem_wait(&data->writerMutex);
    logger("%i: O %i: started\n", data->action_counter++, id);
    sem_post(&data->writerMutex);  

    // Random delay simulating time when car arrive to dock
    srand(time(NULL) * getpid());
    usleep(rand() % (args.TA + 1));

    // Car has arrived at the port
    sem_wait(&data->writerMutex); 
    logger("%i: O %i: arrived to %i\n", data->action_counter++, id, port);
    sem_post(&data->writerMutex);  
    

    // Update the number of cars waiting at the port
    sem_wait(&data->dataMutex);
    if (port == 0) {
        data->doc0.cars_waiting++; // Increment waiting cars at port 0
    } else {
        data->doc1.cars_waiting++; // Increment waiting cars at port 1
    }
    sem_post(&data->dataMutex);

    // Waiting for the boarding signal
    if(port == 0){
        sem_wait(&data->board_car_signal0); // Boarding signal at port 0
    }
    else{
        sem_wait(&data->board_car_signal1); // Boarding signal at port 0
    }
    
    // Boarding the ferry
    sem_wait(&data->writerMutex);
    logger("%i: O %i: boarding\n", data->action_counter++, id);
    sem_post(&data->writerMutex);
    
    // Notify that boarding is done
    sem_post(&data->boarding_signal_done);

    // Switching the actual port to the other after arriving to another
    port = (port+1) % 2;

    // Waiting to unboard
    sem_wait(&data->unboard_car_signal); // Accepting signal from ferry to unboard
    sem_wait(&data->writerMutex);
    logger("%i: O %i: leaving in %i\n", data->action_counter++, id, port);
    sem_post(&data->writerMutex);

    // Sending a signal to ferry that the unboarding was succesfful
    sem_post(&data->car_unboard_signal); 
    
    exit(VALID);
}
