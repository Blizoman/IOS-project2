#include "cleaner.h"

void cleaner(){
    fclose(output);
    sem_destroy(&data->writerMutex);            // for synchronized writing to output
    sem_destroy(&data->portIDMutex);            // for synchronized port switching
    sem_destroy(&data->unboard_car_signal);     // signal cars to unboard
    sem_destroy(&data->unboard_truck_signal);   // signal trucks to unboard
    sem_destroy(&data->truck_unboard_signal);   // feedback from trucks after unboarding
    sem_destroy(&data->car_unboard_signal);     // feedback from cars after unboarding
    sem_destroy(&data->board_truck_signal0);    // allow boarding of truck at dock 0
    sem_destroy(&data->board_car_signal0);      // allow boarding of car at dock 0
    sem_destroy(&data->board_truck_signal1);    // allow boarding of truck at dock 1
    sem_destroy(&data->board_car_signal1);      // allow boarding of car at dock 1
    sem_destroy(&data->boarding_signal_done);   // feedback from vehicles that they boarded
    munmap(data, sizeof(shared_data));          // Unmap shared memory segment used by processes
}