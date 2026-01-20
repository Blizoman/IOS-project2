#ifndef CAR_H
#define CAR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "_globals.h"
#include "message.h"

/**
 * @brief Car process maker.
 * 
 * This function simulates the lifecycle of a car. It arrives at the port,
 * boards to the ferry, go to the other port, and leave.
 * 
 * @param id The unique identifier for the car process.
 * @param port The initial port where the car arrives (either 0 or 1).
 */
void car_process(int id, int port);

#endif //CAR_H