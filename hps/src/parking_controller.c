/*
 * SWE-350 - Parking Occupancy Management System
 *
 * File: parking_controller.c
 *
 * Purpose:
 * Manage parking occupancy, vehicle entry and exit,
 * and parking capacity enforcement.
 */

#include <stdint.h>

// Include configuration definitions such as PARKING_CAPACITY and other system-wide settings.
#include "../../config/config.h"
#include "parking_controller.h"

/*
 * Current number of vehicles parked.
 *
 * Static ensures this variable is accessible only
 * within parking_controller.c.
 */
static uint32_t occupancy_count = 0;

/**
 * @brief Initialize the parking occupancy controller.
 *
 * Resets the current occupancy count to zero.
 */
void parking_init(void)
{
    // Initialize the parking lot as empty.
    occupancy_count = 0;
}

/**
 * @brief Processes a vehicle entry event.
 *
 * Increments the occupancy count when the parking lot
 * has not reached its maximum capacity.
 *
 * @return 0 if entry is successful.
 *        -1 if the parking lot is full.
 */
int parking_vehicle_entry(void)
{
    // Prevent occupancy from exceeding maximum capacity.
    if (occupancy_count >= PARKING_CAPACITY)
    {
        return -1;
    }

    // Admit the vehicle and update occupancy.
    occupancy_count++;

    return 0;
}

/**
 * @brief Processes a vehicle exit event.
 *
 * Decrements the occupancy count when at least
 * one vehicle is currently parked.
 *
 * @return 0 if the exit is successful.
 *        -1 if the parking lot is empty.
 */
int parking_vehicle_exit(void)
{
    // Prevent occupancy from falling below zero.
    if (occupancy_count == 0)
    {
        return -1;
    }

    // A vehicle has exited the parking lot.
    occupancy_count--;

    return 0;
}

/**
 * @brief Retrieves the current parking occupancy.
 *
 * Provides read-only access to the number of vehicles
 * currently parked.
 *
 * @return Current number of parked vehicles.
 */
uint32_t parking_get_occupancy(void)
{
    // Return the current occupancy without modifying it.
    return occupancy_count;
}

/**
 * @brief Retrieves the number of available parking spaces.
 *
 * Calculates the remaining capacity by subtracting
 * the current occupancy from the maximum parking capacity.
 *
 * @return Number of available parking spaces.
 */
uint32_t parking_get_available_spaces(void)
{
    // Calculate remaining spaces.
    return PARKING_CAPACITY - occupancy_count;
}

/**
 * Resets the parking occupancy counter.
 *
 * Clears the current occupancy when KEY0
 * generates a valid debounced press event.
 */
void parking_reset(void)
{
    occupancy_count = 0;
}

