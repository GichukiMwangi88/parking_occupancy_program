
#ifndef PARKING_OCCUPANCY_CONFIG_H
#define PARKING_OCCUPANCY_CONFIG_H
/*
 * SWE-350 - Parking Occupancy Management System
 *
 * File: config.h
 *
 * Description:
 * Hardware configuration for the DE10-Standard
 * ARM HPS and memory-mapped FPGA peripherals.
 */

/* Lightweight HPS-to-FPGA bridge configuration. */
#define LW_BRIDGE_BASE     0xFF200000
#define LW_BRIDGE_SPAN     0x00200000

/* FPGA peripheral offsets relative to LW_BRIDGE_BASE. */
#define LEDR_BASE          0x00003000
#define SW_BASE            0x00004000
#define KEY_BASE           0x00005000
#define HEX3_HEX0_BASE     0x00006000
#define HEX5_HEX4_BASE     0x00007000

/* Parking occupancy configuration. */
#define PARKING_CAPACITY   10

/* Hardware input masks. */
#define SWITCH_MASK        0x000003FF
#define KEY_MASK           0x0000000F

/* Active-low pushbutton bit masks. */
#define KEY_RESET          (1U << 0)
#define KEY_ENTRY          (1U << 1)
#define KEY_EXIT           (1U << 2)

/* LED output mask (10 LEDs). */
#define LED_MASK           0x000003FF

/* Button debounce interval in milliseconds. */
#define BUTTON_DEBOUNCE_MS 20U

#endif /* PARKING_OCCUPANCY_CONFIG_H */
