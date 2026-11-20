#ifndef HEX_DISPLAY_H
#define HEX_DISPLAY_H

/*
 * Robert Mwangi
 * SWE-350
 * November 19, 2026
 * Parking Occupancy Management System
 * 
 * File: hex_display.h
 *
 * Purpose:
 * Declare interfaces for displaying parking availability
 * using the DE10-Standard seven-segment HEX displays.
 *
 * Status: STUB - Milestone Release 2
 *
 * Physical HEX display integration will be completed
 * in a future release.
 */

#include <stdint.h>

/**
 * Simulates writing a digit to a HEX display.
 *
 * Currently prints the selected display and digit
 * to the terminal instead of accessing FPGA hardware.
 *
 * display_index HEX display index (0-5).
 * digit Decimal digit to display (0-9).
 *
 * Return 0 if simulation succeeds.
 *        -1 if an invalid argument is provided.
 *
 * Pseudocode:
 * 1. Validate the display index.
 * 2. Validate the digit.
 * 3. Simulate output through the terminal.
 * 4. Return the simulation result.
 *
 * TODO:
 * Implement active-low seven-segment encoding
 * and memory-mapped FPGA register writes.
 */
int hex_display_write(uint8_t display_index, uint8_t digit);

/**
 * Simulates displaying available parking spaces.
 *
 * Calculates the tens and ones digits from the number
 * of available parking spaces.
 *
 * HEX1 displays the tens digit.
 * HEX0 displays the ones digit.
 *
 * Examples:
 *   10 available spaces -> HEX1 = 1, HEX0 = 0
 *    7 available spaces -> HEX1 = 0, HEX0 = 7
 *    0 available spaces -> HEX1 = 0, HEX0 = 0
 *
 * Parameter available Number of available parking spaces (0-10).
 *
 * Return 0 if simulation succeeds.
 *        -1 if an invalid value or simulated write fails.
 *
 * Pseudocode:
 * 1. Validate that available is between 0 and 10.
 * 2. Extract the tens digit using integer division.
 * 3. Extract the ones digit using modulo.
 * 4. Simulate writing the tens digit to HEX1.
 * 5. Simulate writing the ones digit to HEX0.
 * 6. Return success or failure.
 *
 * TODO:
 * Replace simulated output with physical HEX hardware
 * control while preserving this function interface.
 */
int hex_display_available_spaces(uint32_t available);

#endif /* HEX_DISPLAY_H */