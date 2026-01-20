#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <stdlib.h>
#include "_globals.h"

/**
 * @brief Initializes semaphores and shared memory for synchronization.
 * 
 * This function initializes semaphores that are used for synchronization
 * between processes. 
 * It also creates shared memory to store data that is accessed by multiple processes.
 * 
 * @return Returns VALID (0) if semaphores and shared memory are successfully initialized, 
 *         or INVALID (1) if there is an error in initialization.
 */
int semaphore_init();

#endif //SEMAPHORE_H