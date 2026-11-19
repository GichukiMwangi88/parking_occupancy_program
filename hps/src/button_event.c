
/*
 * SWE-350 - Parking Occupancy Management System
 *
 * File: button_event.c
 *
 * Purpose:
 * Detect new pushbutton press events by comparing
 * the current and previous button states.
 */

#include <stdint.h>

#include "config.h"
#include "button_event.h"

// /*
//  * Stores the previous state of the four pushbuttons.
//  *
//  * The buttons are active-low:
//  *   1 = Released
//  *   0 = Pressed
//  */
// static uint32_t previous_button_state = KEY_MASK;

// Most recently observed raw button state.
// Detects changes in incoming readings
static uint32_t previous_raw_state = KEY_MASK;

// Last confirmed stable button state.
// Prevents unconfirmed changes from generating events
static uint32_t stable_button_state = KEY_MASK;

// Time when the raw button state last changed.
// tracks how long the raw state has remained unchanged
// for each button , KEY0-KEY2
// KEY[0] - for Reset
// KEY[1] - Entry
// KEY[2] - Exit
static uint64_t last_change_ms[4] = {0};

/**
 * @brief Initializes the pushbutton event detector.
 *
 * Stores the initial button state so that a button
 * already pressed during startup is not counted
 * as a new event.
 *
 * Initial state of KEY0 through KEY3.
 * Initial timestamp for each key
 */
void button_event_init(uint32_t initial_state, uint64_t initial_time_ms)
{
    // Store the initial raw button state.
    previous_raw_state = initial_state & KEY_MASK;

    // Store the initial accepted stable state.
    stable_button_state = initial_state & KEY_MASK;

    // Initialize an independent debounce timestamp for each button
    for(uint32_t i = 0; i < 4; i++)
    {
        last_change_ms[i] = initial_time_ms;
    }
}
/**
 * @brief Detects newly pressed pushbuttons.
 *
 * Compares the previous and current button states
 * to identify falling edges (1 to 0).
 *
 * @param current_state Current state of KEY0–KEY3.
 *
 * @return Bit mask identifying newly pressed buttons.
 */
uint32_t button_detect_press(uint32_t current_state, uint64_t current_time_ms)
{
    uint32_t pressed_events = 0;
   
    // Keep only the four pushbutton bits.
    current_state &= KEY_MASK;

    // Detect when the raw_button_state changes using XOR 
    // XOR returns True(1) when there's been a change in inputs
    /*
    Previous raw state: 1111
    Current raw state:  1101
                    ---- XOR
    Changed buttons:    0010 // Tells us KEY1 changed
    */
    uint32_t changed_buttons =
    previous_raw_state ^ current_state;

    // Detect and record changes when at least one button changes
    if (changed_buttons != 0)
    {
        for(uint32_t i = 0; i < 4; i++)
        {
            uint32_t button_mask = (1U << i);

            // Update the timestamp only for the button that changed
            if(changed_buttons & button_mask)
            {
                last_change_ms[i] = current_time_ms;
            }
        }
    }

    // Save the latest raw button state
    previous_raw_state = current_state;

    // Check the debounce interval for each button.
    for (uint32_t i = 0; i < 4; i++)
    {
        uint32_t button_mask = (1U << i);

        // Check whether this button has been stable long enough.
        if ((current_time_ms - last_change_ms[i]) >= BUTTON_DEBOUNCE_MS)
        {
             // Check whether the raw state differs from the stable state.
            if ((current_state ^ stable_button_state) & button_mask)
            {
                // Detect newly confirmed button presses.
                pressed_events |= stable_button_state & ~current_state & button_mask;

                // Update only this button's stable state.
                stable_button_state =
                    (stable_button_state & ~button_mask) |
                    (current_state & button_mask);
            }
        }
    }

    return pressed_events;
}
