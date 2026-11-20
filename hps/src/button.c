
/*
 * Robert Mwangi
 * SWE-350
 * November 19, 2026
 * Parking Occupancy Management System
 *
 * File: button.c
 *
 * Purpose:
 * Read the DE10-Standard pushbuttons through
 * the FPGA's memory-mapped button register.
 */

#include <stdint.h>
#include <stddef.h>

#include "config.h"
#include "hal_api.h"
#include "button.h"

/*
 * Pointer to the FPGA pushbutton register.
 *
 * Static restricts access to this source file.
 * Volatile ensures reads access the hardware register.
 */
static volatile uint32_t *button_register = NULL;

/**
 * Initializes the FPGA pushbutton interface.
 *
 * Retrieves the pushbutton register address from the HAL.
 * The HAL must already be initialized using hal_init().
 *
 * 0 if initialization succeeds, -1 otherwise.
 */
int button_init(void)
{
    // Request the pushbutton register from the HAL.
    button_register = hal_get_register(KEY_BASE);

    // Verify that the register address is valid.
    if (button_register == NULL)
    {
        return -1;
    }

    return 0;
}

/**
 * Reads the current state of the DE10-Standard pushbuttons.
 *
 * Reads the memory-mapped button register and masks out
 * unused bits, keeping only KEY0 through KEY3.
 *
 * The pushbuttons are active-low:
 *   0 = Pressed
 *   1 = Released
 *
 * Four-bit button state on success.
 *         UINT32_MAX if the interface is not initialized.
 */
uint32_t button_read(void)
{
    // Ensure the button interface has been initialized.
    if (button_register == NULL)
    {
        return UINT32_MAX; // this acts a sentinel to indicate failure
    }

    // Read the hardware register and retain only KEY0-KEY3.
    // KEY_MASK only keeps the lowest 4 bits
    // Eg. 0xD - Binary value = 1101, meaning KEY[1] pressed
    return (*button_register) & KEY_MASK;
}
