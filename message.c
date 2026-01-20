#include "message.h"


void logger(char *message, ...) { 
    
    // va_list to hold the variable arguments
    va_list args;       
    va_start(args, message);

    // Print the formatted message to the output file
    vfprintf(output, message, args);                                     
    fflush(output);  
    
    va_end(args);
}