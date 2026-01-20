#include "semaphore.h"

int semaphore_init(){
    // Initialize shared memory
    data = mmap(NULL, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (data == MAP_FAILED){
        fprintf(stderr,"Error while creating map!\n");
        return INVALID;
    }

    //////////////////////////////////////////////////////////////////////////
    /////////////////////////////MUTEX SEMAPHORES/////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    if (sem_init(&data->writerMutex, 1, 1) != 0){  
        fprintf(stderr,"Error while creating writerMutex semaphore!\n");
        return INVALID;
    }
    if (sem_init(&data->portIDMutex, 1, 1) != 0){  
        fprintf(stderr,"Error while creating portIDMutex semaphore!\n");
        return INVALID;
    }
    if (sem_init(&data->dataMutex, 1, 1) != 0){  
        fprintf(stderr,"Error while creating dataMutex semaphore!\n");
        return INVALID;
    }

    //////////////////////////////////////////////////////////////////////////
    /////////////////////////////EVENTS SEMAPHORES////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    if (sem_init(&data->unboard_car_signal, 1, 0) != 0){  
        fprintf(stderr,"Error while creating Unboarding car semaphore!\n");
        return INVALID;
    }
    if (sem_init(&data->unboard_truck_signal, 1, 0) != 0){  
        fprintf(stderr,"Error while creating Unboarding truck semaphore!\n");
        return INVALID;
    }
    if (sem_init(&data->truck_unboard_signal, 1, 0) != 0){  
        fprintf(stderr,"Error while creating Unboarding truck semaphore!\n");
        return INVALID;
    }
    if (sem_init(&data->car_unboard_signal, 1, 0) != 0){ 
        fprintf(stderr,"Error while creating Unboarding car semaphore!\n");
        return INVALID;
    }
    if (sem_init(&data->board_car_signal0, 1, 0) != 0){  
        fprintf(stderr,"Error while creating Boarding car from dock '0' semaphore!\n");
        return INVALID;
    }
    if (sem_init(&data->board_truck_signal0, 1, 0) != 0){  
        fprintf(stderr,"Error while creating Boarding truck from dock '0' semaphore!\n");
        return INVALID;
    }
    if (sem_init(&data->board_car_signal1, 1, 0) != 0){  
        fprintf(stderr,"Error while creating Boarding car from dock '1' semaphore!\n");
        return INVALID;
    }
    if (sem_init(&data->board_truck_signal1, 1, 0) != 0){ 
        fprintf(stderr,"Error while creating Boarding truck from dock '1' semaphore!\n");
        return INVALID;
    }
    if (sem_init(&data->boarding_signal_done, 1, 0) != 0){ 
        fprintf(stderr,"Error while creating Boarding finished semaphore!\n");
        return INVALID;
    }

    // Initialize shared data
    data->cars_on_ferry = 0;
    data->trucks_on_ferry = 0;
    data->portID = 0;
    data->portCAR = 0;
    data->portTRUCK = 0;
    data->action_counter = 1;

    // Docks initializations
    data->doc0.cars_waiting = 0;
    data->doc0.trucks_waiting = 0;
    data->doc0.cars_comming = 0;
    data->doc0.trucks_comming = 0;

    data->doc1.cars_waiting = 0;
    data->doc1.trucks_waiting = 0;
    data->doc1.cars_comming = 0;
    data->doc1.trucks_comming = 0;

    return VALID;
}