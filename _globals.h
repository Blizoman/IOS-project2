/**
 * @file globals.h
 * @brief Global definitions, shared memory structure, and semaphores for the 
 * ferry synchronization project.
 */

#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <sys/mman.h>
#include <semaphore.h>
#include <stdio.h>

/// @brief Constants for input validation
#define VALID_IN 6          // Always expect 6 arguments
#define CAR_CAPACITY 9999   // Max total cars allowed
#define MIN_CAPACITY 3      // Min ferry capacity
#define MAX_CAPACITY 100    // Max ferry capacity
#define MAX_FERRY 1000      // Max time for ferry ride
#define MAX_CAR 10000       // Max time for car/truck to dock

/**
 * @struct Args
 * @brief Command-line input arguments.
 */
typedef struct{ 
    int N;                  // Number of cars processes to generate
    int O;                  // Number of trucks processes to generate
    int K;                  // Ferry capacity 
    int TA;                 // Max time for cars/trucks to dock
    int TP;                 // Max time for ferry ride
} Args;

/**
 * @struct Docs
 * @brief Status of vehicles waiting / comming to a port.
 */
typedef struct{ 
    int cars_waiting;       // Number of cars waiting at port
    int cars_comming;       // Number of cars comming to a port
    int trucks_waiting;     // Number of trucks waiting at port
    int trucks_comming;     // Number of trucks comming to a port
} Docs;


/**
 * @struct shared_data
 * @brief Shared memory structure used by all processes.
 */
typedef struct{
    int action_counter;     // Action counter for output file (Indexing output file messages)
    int cars_on_ferry;      // Number of cars on ferry
    int trucks_on_ferry;    // Number of trucks on ferry
    int portID;             // Port on which ferry is at the moment
    int portTRUCK;          // Port where the truck will begin
    int portCAR;            // Port where the car will begin

    ////////////////////////////////////////////////////////
    //////////////////////SEMAPHORES////////////////////////
    ////////////////////////////////////////////////////////

    sem_t writerMutex;      // Mutex for synchronized output
    sem_t portIDMutex;      // Mutex for portID access
    sem_t dataMutex;        // Mutex for vehicle counters
    
    sem_t unboard_car_signal;   // Unboarding signal sent by ferry to car
    sem_t unboard_truck_signal; // Unboarding signal sent by ferry to truck
    sem_t truck_unboard_signal; // Unboarding signal sent by truck to ferry
    sem_t car_unboard_signal;   // Unboarding signal sent by car to ferry
    
    sem_t board_truck_signal0;  // Boarding signal sent by ferry to truck in dock 0
    sem_t board_car_signal0;    // Boarding signal sent by ferry to car in dock 0
    sem_t board_truck_signal1;  // Boarding signal sent by ferry to truck in dock 1
    sem_t board_car_signal1;    // Boarding signal sent by ferry to car in dock 1
    sem_t boarding_signal_done; // Boarding signal sent by truck/car to ferry
    
    ////////////////////////////////////////////////////////
    /////////////////////////PORTS//////////////////////////
    ////////////////////////////////////////////////////////

    Docs doc0;      // Doc "0"
    Docs doc1;      // Doc "1"
} shared_data;

/// @brief Global variable for parsed arguments
extern Args args;

/// @brief Pointer to shared memory
extern shared_data *data;

/// @brief Output file for writing logs
extern FILE *output; 

/**
 * @enum PROBLEMS
 * @brief Enum for input validation status.
 */
enum PROBLEMS{VALID, INVALID};

#endif //_GLOBALS_H