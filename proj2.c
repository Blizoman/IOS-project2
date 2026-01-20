/*
 * Project: IOS 2 - Synchronization
 * Author: xblizna00 (Andrej Bliznak)
 * Date: 3.5.2025 
 * About: Securing correct transport of vehicles by 
 *        ferry from two different ports using Semaphores.
 */

#include "args.h"       // Command line args
#include "_globals.h"   // Global variables
#include "semaphore.h"  // Semaphores initialization
#include "process.h"    // Processes initialization
#include "cleaner.h"    // Destructor

shared_data *data;      // Pointer to our shared memory struct
Args args;              // Command line args

FILE *output;           // Output file for logging

/**
 * @brief Main function of the program.
 * 
 * This function parses command-line arguments, initializes semaphores, 
 * starts processes and clean them up at the end.
 * 
 * @param argc The number of command-line arguments
 * @param argv The array of command-line arguments
 * 
 * @return int Returns VALID (0) if everything runs fine or INVALID (1) if there is an error.
 */
int main(int argc, char* argv[]){

    // Arguments check
    if (parse_args(argc, argv, &args) != VALID) {
        fprintf(stderr, "Error!\n");
        return INVALID;
    }

    output = fopen("proj2.out", "w");

    // File check 
    if (output == NULL){
        fprintf(stderr, "Error while opening a file\n");
        return INVALID;
    }

    // Initialize semaphores and shared memory
    semaphore_init();  
    
    // Initialize processes
    process_init(); 
    
    // Deallocation
    cleaner();
    return VALID;
}









