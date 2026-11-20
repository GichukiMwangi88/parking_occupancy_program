#ifndef PARKING_LED_H
#define PARKING_LED_H

/*
 * Robert Mwangi
 * SWE-350
 * November 19, 2026
 * Parking Occupancy Management System
 *
 * File: led.h
 *
 * Purpose:
 * Declare functions for controlling the
 * DE10-Standard's red LEDs.
 */

#include <stdint.h>

/**
 * @brief Initializes access to the FPGA LED register.
 *
 * Retrieves the memory-mapped LED register from the HAL.
 * hal_init() must be called before this function.
 *
 * @return 0 on success, -1 on failure.
 */
int led_init(void);

/**
 * @brief Displays parking occupancy using the LEDs.
 *
 * Illuminates one LED for each occupied parking space.
 * For example, an occupancy of 3 illuminates
 * LEDR0, LEDR1, and LEDR2.
 *
 * @param occupancy Number of vehicles currently parked.
 */
void led_display_occupancy(uint32_t occupancy);

#endif /* PARKING_LED_H */