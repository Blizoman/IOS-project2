#ifndef FERRY_H
#define FERRY_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include "_globals.h"
#include "message.h"

/**
 * @brief Main logic for the ferry process.
 *
 * The ferry moves between ports, unboard and board vehicles based on availability
 * and capacity. It terminates when all vehicles have been transported.
 */
void ferry_process();

/**
 * @brief Attempts to board vehicle to ferry at current port.
 *
 * This function checks if the next vehicle (next_truck or !next_truck) can board the ferry
 * depending on the current port queue and the ferrys remaining capacity.
 * It switches between trucks or cars based on `next_truck`. If there is only one type of 
 * vehicle, the ferry will be filled with the remaining ones.
 *
 * @param next_truck Boolean value, if 'true', truck should board otherwise ferry is waiting
 *                   for car.
 * @param currentOccupancy Pointer to the current occupancy counter of the ferry.
 * @param portID ID of the port where ferry is right now (0 or 1).
 * @return true if boarding was successful, false if boarding was not sucessfull.
 */
bool boarding(bool next_truck, int *currentOccupancy, int portID);

#endif // FERRY_H