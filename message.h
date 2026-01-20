#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdarg.h>
#include <stdio.h>

#include "_globals.h"

/**
 * @brief Logging function that prints formatted messages to the output file.
 *
 * This function uses a semaphore for mutual exclusion when writing to the shared
 * output file, preventing corrupted log entries when multiple processes
 * write at the same time.
 
 * @param message Format string (similar to printf).
 * @param ...     Additional arguments.
 */
void logger(char *message, ...);

#endif  // PRINT_OUT_H