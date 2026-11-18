
#ifndef HAL_API_H
#define HAL_API_H

#include <stdint.h>
#include <stddef.h>  // Defines NULL

/*
 * Initialize access to the HPS hardware registers.
 *
 * Returns:
 *   0  - Initialization successful.
 *  -1  - Initialization failed.
 */
int hal_init(void);

/*
 * Return a pointer to a memory-mapped FPGA register.
 *
 * Parameters:
 *   offset - Byte offset relative to LW_BRIDGE_BASE.
 *
 * Returns:
 *   Pointer to the requested 32-bit register.
 *   NULL if the HAL is uninitialized or the offset is invalid.
 */
volatile uint32_t *hal_get_register(uint32_t offset);

/*
 * Release the hardware memory mapping
 * and associated system resources.
 */
void hal_cleanup(void);

#endif

