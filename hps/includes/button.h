#ifndef PARKING_BUTTON_H
#define PARKING_BUTTON_H

/*
 * Robert Mwangi
 * SWE-350
 * November 19, 2026
 * Parking Occupancy Management System
 * 
 * File: button.h
 *
 * Purpose:
 * Declare functions for reading the DE10-Standard
 * pushbuttons through memory-mapped FPGA registers.
 */

#include <stdint.h>

/**
 * @brief Initializes access to the FPGA pushbutton register.
 *
 * Uses the existing HAL to obtain the register address.
 *
 * @return 0 on success, -1 on failure.
 */
int button_init(void);

/**
 * @brief Reads the current pushbutton states.
 *
 * Returns the active-low states of KEY0 through KEY3.
 *
 * @return Four-bit button state, or UINT32_MAX on error.
 */
uint32_t button_read(void);

#endif /* PARKING_BUTTON_H */