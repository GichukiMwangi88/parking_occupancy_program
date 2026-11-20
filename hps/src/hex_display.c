/*
 * Robert Mwangi
 * SWE-350
 * November 19, 2026
 * Parking Occupancy Management System
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
 * Simulates writing a digit to a HEX display.
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

/**
 * Simulates displaying available parking spaces.
 *
 * HEX1 represents the tens digit.
 * HEX0 represents the ones digit.
 *
 * Parameter available Number of available spaces (0-10).
 *
 * Return 0 on simulated success, -1 on failure.
 *
 * Pseudocode:
 * 1. Verify that available does not exceed capacity.
 * 2. Calculate the tens digit.
 * 3. Calculate the ones digit.
 * 4. Simulate writing the tens digit to HEX1.
 * 5. Simulate writing the ones digit to HEX0.
 * 6. Return the result.
 *
 * TODO: Replace the simulated output with physical
 * active-low seven-segment hardware control.
 */
int hex_display_available_spaces(uint32_t available)
{
    // Reject invalid availability values.
    if (available > 10U)
    {
        return -1;
    }

    // Extract the tens and ones digits.
    uint8_t tens = (uint8_t)(available / 10U);
    uint8_t ones = (uint8_t)(available % 10U);

    // Simulate displaying the tens digit on HEX1.
    if (hex_display_write(1, tens) != 0)
    {
        return -1;
    }

    // Simulate displaying the ones digit on HEX0.
    if (hex_display_write(0, ones) != 0)
    {
        return -1;
    }

    return 0;
}