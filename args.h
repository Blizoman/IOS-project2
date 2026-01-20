#ifndef ARGS_H
#define ARGS_H

#include <stdlib.h>
#include <sys/mman.h>
#include <ctype.h>
#include "_globals.h"


/**
 * @brief Validates command-line arguments.
 * 
 * This function checks if all expected arguments are numeric, converts them,
 * and ensures that they fall within allowed ranges for the ferry system.
 * 
 * @param argc Argument count
 * @param argv Argument vector (array of strings representing the arguments)
 * @param args Pointer to Args structure to be filled with parsed values
 * 
 * @return int Returns VALID (0) on success, INVALID_INPUT (1) on failure
 */
int parse_args(int argc, char *argv[], Args *args);

#endif //ARGS_H