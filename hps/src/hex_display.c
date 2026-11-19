/*
 * SWE-350 - Parking Occupancy Management System
 *
 * File: hex_display.c
 *
 * Purpose:
 * Simulate seven-segment display output until
 * physical HEX integration is completed.
 *
 * Status: STUB - Release 2
 */

#include <stdint.h>
#include <stdio.h>

#include "hex_display.h"

/**
 * @brief Simulates writing a digit to a HEX display.
 *
 * This stub does not access FPGA hardware.
 * Instead, it prints the requested digit
 * and display index to the terminal.
 *
 * Parameter display_index HEX display number (0-5).
 * Parameter digit Decimal digit to display (0-9).
 *
 * Return 0 on simulated success.
 *        -1 for invalid arguments.
 *
 * Pseudocode:
 * 1. Validate display index.
 * 2. Validate the requested digit.
 * 3. Print the simulated display output.
 * 4. Return simulated success.
 *
 * TODO:
 * Replace terminal output with active-low
 * seven-segment encoding and FPGA register writes.
 */
int hex_display_write(uint8_t display_index, uint8_t digit)
{
    // Validate the requested display.
    if (display_index > 5)
    {
        return -1;
    }

    // Validate decimal digit.
    if (digit > 9)
    {
        return -1;
    }

    // Simulate the hardware output.
    printf("[HEX STUB] HEX%u = %u\n",
           (unsigned int)display_index,
           (unsigned int)digit);

    // Report simulated success, not hardware verification.
    return 0;
}