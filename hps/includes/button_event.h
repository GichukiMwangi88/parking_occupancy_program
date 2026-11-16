
#ifndef PARKING_BUTTON_EVENT_H
#define PARKING_BUTTON_EVENT_H

/*
 * SWE-350 - Parking Occupancy Management System
 *
 * File: button_event.h
 *
 * Purpose:
 * Declare the interface for detecting new
 * pushbutton press events.
 */

#include <stdint.h>

/**
 * @brief Initializes the button event detector.
 *
 * Stores the initial button state so that buttons
 * already held during startup do not generate events.
 *
 * @param initial_state Initial four-bit pushbutton state.
 */
void button_event_init(uint32_t initial_state, uint64_t initial_time_ms);

/**
 * Detects debounced pushbutton press events.
 *
 * Compares the current button state with the previous
 * state to detect transitions from released (1)
 * to pressed (0).
 *
 * current_state -> Current four-bit button state.
 * current_time_ms -> time when the button state change, account for button debouncing, ensure
 * we only track button_state changes after a specified time duration
 *
 *  return Bit mask identifying newly pressed buttons.
 */
uint32_t button_detect_press(uint32_t current_state, uint64_t current_time_ms);

#endif /* PARKING_BUTTON_EVENT_H */
