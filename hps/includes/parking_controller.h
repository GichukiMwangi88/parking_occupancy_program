#ifndef PARKING_CONTROLLER_H
#define PARKING_CONTROLLER_H

/*
 * SWE-350 - Parking Occupancy Management System
 *
 * File: parking_controller.h
 *
 * Purpose:
 * Define the parking occupancy controller interface.
 */

#include <stdint.h>

/*
 * Initialize the parking occupancy counter.
 *
 * Sets the current occupancy to zero.
 */
void parking_init(void);

 /*
 * Reset the parking occupancy counter.
 *
 * Called when the user presses KEY0.
 * Sets occupancy back to zero.
 */
void parking_reset(void);

/*
 * Process a vehicle entry event.
 *
 * Increments occupancy if parking capacity has not
 * been reached.
 *
 * Returns:
 *   0 if the vehicle was admitted.
 *  -1 if the parking lot is full.
 */


int parking_vehicle_entry(void);

/*
 * Process a vehicle exit event.
 *
 * Decrements occupancy if at least one vehicle
 * is currently parked.
 *
 * Returns:
 *   0 if a vehicle successfully exited.
 *  -1 if the parking lot is empty.
 */
int parking_vehicle_exit(void);

/*
 * Retrieve the current parking occupancy.
 *
 * Returns:
 *   Number of vehicles currently parked.
 */
uint32_t parking_get_occupancy(void);

/*
 * Retrieve the number of available parking spaces.
 *
 * Returns:
 *   Number of unoccupied spaces.
 */
uint32_t parking_get_available_spaces(void);

#endif /* PARKING_CONTROLLER_H */