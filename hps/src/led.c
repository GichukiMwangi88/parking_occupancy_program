/*
 * SWE-350 - Parking Occupancy Management System
 *
 * File: led.c
 *
 * Purpose:
 * Control the DE10-Standard's red LEDs through
 * memory-mapped FPGA registers.
 */

#include <stdint.h>
#include <stddef.h>

#include "../../config/config.h"
#include "hal_api.h"
#include "led.h"

/*
 * Pointer to the FPGA LED register.
 *
 * Volatile ensures writes reach the hardware register.
 * Static restricts access to this source file.
 */
static volatile uint32_t *led_register = NULL;



int led_init(void)
{
    // Obtain the LED register through the HAL.
    led_register = hal_get_register(LEDR_BASE);

    // Check whether the register address is valid.
    if (led_register == NULL)
    {
        return -1;
    }

    return 0;
}

void led_display_occupancy(uint32_t occupancy)
{
    // Ensure the LED register has been initialized.
    if (led_register == NULL)
    {
        return;
    }
    
    // Validate the Parking Capacity
    if (occupancy > PARKING_CAPACITY)
    {
        occupancy = PARKING_CAPACITY;
    }

    // Calculate the LED pattern to be displayed depending on the current occupancy
    uint32_t led_pattern = (1U << occupancy) - 1U;

    // Write the pattern to the FPGA LED register
    *led_register = led_pattern & LED_MASK;

}