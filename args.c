#include "args.h"


int parse_args(int argc, char *argv[], Args *args) {
    // Check if the number of arguments is correct
    if (argc != VALID_IN) return INVALID;

    // Loop through each argument to check if they are numeric
    for (int i = 1; i < VALID_IN; i++) {
        for (int j = 0; argv[i][j] != '\0'; j++) {
            if (!isdigit(argv[i][j])) {
                return INVALID;
            }
        }
    }

    // Convert args to integers
    args->N  = atoi(argv[1]);
    args->O  = atoi(argv[2]);
    args->K  = atoi(argv[3]);
    args->TA = atoi(argv[4]);
    args->TP = atoi(argv[5]);

    // Check if the values are within allowed ranges
    if (args->N > CAR_CAPACITY) 
        return INVALID;
    if (args->O > CAR_CAPACITY) 
        return INVALID;
    if (args->K < MIN_CAPACITY || args->K > MAX_CAPACITY) 
        return INVALID;
    if (args->TA < 0 || args->TA > MAX_CAR) 
        return INVALID;
    if (args->TP < 0 || args->TP > MAX_FERRY) 
        return INVALID;

    return VALID;
}