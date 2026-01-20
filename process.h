#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "_globals.h"
#include "ferry.h"
#include "truck.h"
#include "car.h"

/**
 * @brief Initializates other processes.
 * 
 * This function forks child processes to simulate the ferry, trucks, and cars.
 * The ferry process is initialized first, than truck and car processes.
 * It waits for all child processes to finish before returning. Called by main process.
 * 
 * @return Returns VALID (0) if the process initialization is successful.
 */
int process_init();

#endif // PROCESS_H