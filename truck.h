#ifndef TRUCK_H
#define TRUCK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "_globals.h"
#include "message.h"


/**
 * @brief Trucks process maker
 * 
 * This function simulates the lifecycle of a truck. It arrives at the port,
 * boards to the ferry, go to the other port, and leave.
 * 
 * @param id The unique identifier of the truck.
 * @param port The initial port where the truck arrives (either 0 or 1).
 */
void truck_process(int id, int port);

#endif //TRUCK_H