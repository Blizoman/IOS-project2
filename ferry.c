#include "ferry.h"


bool boarding(bool next_truck, int *currentOccupancy, int portID){
    sem_wait(&data->dataMutex);
    Docs* currentPort = !portID ? &data->doc0 : &data->doc1;

    // Switch boarding preferences if searched type is not waiting.
    if(next_truck && currentPort->trucks_waiting <= 0) next_truck = !next_truck;
    if(!next_truck && currentPort->cars_waiting <= 0) next_truck = !next_truck;

    // No vehicles are waiting at this port
    if(currentPort->cars_waiting == 0 && currentPort->trucks_waiting == 0){
        sem_post(&data->dataMutex);
        return false;
    }

    // Truck boarding (takes 3 slots)
    if(next_truck && currentPort->trucks_waiting > 0 && *currentOccupancy + 3 <= args.K){
        // Selecting correct port ( 0 / 1 )
        sem_post(!portID ? &data->board_truck_signal0 : &data->board_truck_signal1); 

        currentPort->trucks_waiting--;
        data->trucks_on_ferry++; // Increment number of trucks on ferry.
        // Truck occupate 3 'space units'
        *currentOccupancy += 3;  // Increment actual occupacy of ferry. (decrement actual space)
    }

    // Car boarding (takes 1 slot)
    else if (!next_truck && currentPort->cars_waiting > 0 && *currentOccupancy + 1 <= args.K){
        // Selecting correct port ( 0 / 1 )
        sem_post(!portID ? &data->board_car_signal0 : &data->board_car_signal1); 
        currentPort->cars_waiting--;
        data->cars_on_ferry++;  // Increment number of cars on ferry.
        // Car occupate 1 'space unit'
        *currentOccupancy += 1; // Increment actual occupacy of ferry. (decrement actual space)
    }

    // If ferry is full
    else{ 
        sem_post(&data->dataMutex);
        return false; // break loop
    }

    sem_post(&data->dataMutex);

    return true;
}

void ferry_process(){
    // Action counter and portID were inicialized in semaphore function 
    
    // Messaging that ferry started moving
    
    sem_wait(&data->writerMutex); 
    logger("%i: P: started\n", data->action_counter++);
    sem_post(&data->writerMutex);  
    

    // Local variable representing number of unboarded vehicles
    int countOfUnboarded = 0;
    
    while(1){

        // Simulating travel time
        srand(time(NULL) * getpid());
        usleep(rand() % (args.TP + 1));
        
        // Announce arrival to dock
        sem_wait(&data->writerMutex); 
        logger("%i: P: arrived to %i\n", data->action_counter++, data->portID);
        sem_post(&data->writerMutex);  
        
        
        // Unloading vehicles
        for (int i = 0; i < data->cars_on_ferry; i++) {  // Giving signal to car process
            sem_post(&data->unboard_car_signal);         // that it can start boarding.
        }

        for (int i = 0; i < data->trucks_on_ferry; i++){ // Giving signal to truck process
            sem_post(&data->unboard_truck_signal);       // that it can start boarding.
        }

        for (int i = 0; i < data->cars_on_ferry; i++) {  // Receiving signal from car proc
            sem_wait(&data->car_unboard_signal);         // that vehicle was boarded.
            countOfUnboarded++;
        }

        for (int i = 0; i < data->trucks_on_ferry; i++) {// Receiving signal from truck proc
            sem_wait(&data->truck_unboard_signal);       // that vehicle was boarded.
            countOfUnboarded++;
        }

        data->cars_on_ferry = 0;    // After unboarding, number of cars and trucks
        data->trucks_on_ferry = 0;  // at ferry being reseted.
        
        // Begin of boarding
        bool next_truck = true;     // Switcher between trucks and cars.
        int portID = data->portID;  // Local variable for current port where ferry is.

        // Counter of a currently occupated space at ferry
        int currentOccupancy = 0;
        
        // If there is free space at ferry.
        while (currentOccupancy <= args.K){ 

            if(!boarding(next_truck, &currentOccupancy, portID)) break;
            next_truck = !next_truck; // Swap between cars and trucks
        }

        // Waiting for every car and truck statement that they were boarded. 
        int total_boarded = data->cars_on_ferry + data->trucks_on_ferry;
        for(int i = 0; i < total_boarded; i++){
            sem_wait(&data->boarding_signal_done);
        }
        
        // After, ferry leaves the current port
        sem_wait(&data->writerMutex); 
        logger("%i: P: leaving %i\n", data->action_counter++, data->portID);
        sem_post(&data->writerMutex);  
        

        // Stopping condition that all vehicles were transported
        if(countOfUnboarded == args.N + args.O) break;

        // Switch port
        sem_wait(&data->portIDMutex);
        data->portID = (data->portID+1) % 2;
        sem_post(&data->portIDMutex);

        continue; 

        // Again simulating travel time
        srand(time(NULL) * getpid());
        usleep(rand() % (args.TP + 1));

        // Get current portID
        sem_wait(&data->portIDMutex);
        portID = data->portID;
        sem_post(&data->portIDMutex);

        // Check if the ferry picked all the vehicles
        sem_wait(&data->dataMutex);
        if (portID == 0){  // Checking actual port
            if (!(data->cars_on_ferry > 0 || data->trucks_on_ferry > 0 || (data->doc0.cars_comming + data->doc0.trucks_comming) > 0)){  //ak su este nejake auta na privoze alebo cakaju v pristave tak opakuj
                sem_post(&data->dataMutex);
                break;
            }
        }
        else{            
            if (!(data->cars_on_ferry > 0 || data->trucks_on_ferry > 0 || (data->doc1.cars_comming + data->doc1.trucks_comming) > 0)){
                sem_post(&data->dataMutex);
                break;
            }
        }
        sem_post(&data->dataMutex);
    }
    
    // Again simulating travel time
    srand(time(NULL) * getpid());
    usleep(rand() % (args.TP + 1));

    // Message that ferry transported all the vehicles
    sem_wait(&data->writerMutex); 
    logger("%i: P: finish\n", data->action_counter++);
    sem_post(&data->writerMutex);  
    
    
    exit(VALID);
}