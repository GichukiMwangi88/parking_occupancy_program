/**
 * Robert Mwangi
 * SWE-350
 * November 19, 2026
 * Parking Occupancy Management System
 *
 * File: main.c
 *
 * Purpose:
 * Coordinate FPGA hardware initialization,
 * pushbutton events, parking occupancy,
 * and LED output.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <signal.h>

#include "config.h"
#include "hal_api.h"
#include "button.h"
#include "button_event.h"
#include "parking_controller.h"
#include "led.h"

/*
 * Controls whether the main application loop continues running.
 *
 * volatile ensures the compiler does not assume the value
 * remains unchanged during program execution.
 * sig_atomic_t allows safe access from a signal handler.
 */
static volatile sig_atomic_t application_running = 1;

/*
 * Handle an interrupt signal such as Ctrl+C.
 *
 * Request shutdown without performing resource
 * cleanup inside the signal handler.
 */
static void handle_shutdown_signal(int signal_number)
{
    (void)signal_number;

    application_running = 0;
}

/*
 * Retrieve the current monotonic time in milliseconds.
 *
 * Used to measure button debounce intervals.
 */
static uint64_t get_time_ms(void)
{
    struct timespec current_time;

    // Read the current monotonic clock.
    if (clock_gettime(CLOCK_MONOTONIC, &current_time) != 0)
    {
        perror("Failed to read monotonic clock");
        return UINT64_MAX;
    }

    // Convert seconds and nanoseconds into milliseconds.
    return ((uint64_t)current_time.tv_sec * 1000ULL) +
           ((uint64_t)current_time.tv_nsec / 1000000ULL);
}

//-------------Entry Point to the Application----------------------

int main(void)
{

    // Register the handler for Ctrl+C.
    if (signal(SIGINT, handle_shutdown_signal) == SIG_ERR)
    {
        perror("Failed to register signal handler");
        return 1;
    }


    // Initialize access to FPGA memory-mapped registers.
    if (hal_init() != 0)
    {
        fprintf(stderr, "ERROR: HAL initialization failed.\n");
        return 1;
    }

    // Initialize access to the FPGA pushbuttons.
    if (button_init() != 0)
    {
        fprintf(stderr, "ERROR: Button initialization failed.\n");
        hal_cleanup();
        return 1;
    }

    // Initialize access to the FPGA LEDs.
    if (led_init() != 0)
    {
        fprintf(stderr, "ERROR: LED initialization failed.\n");
        hal_cleanup();
        return 1;
    }

    printf("FPGA hardware initialized successfully.\n");


    // Initialize the parking lot with zero occupied spaces.
    parking_init();

    // Display the initial occupancy on the FPGA LEDs.
    led_display_occupancy(parking_get_occupancy());

    // Read the initial state of the FPGA pushbuttons.
    uint32_t initial_buttons = button_read();

    // Check whether the button reading failed.
    if (initial_buttons == UINT32_MAX)
    {
        fprintf(stderr, "ERROR: Initial button read failed.\n");
        hal_cleanup();
        return 1;
    }

    // Get the initial timestamp for debouncing.
    uint64_t initial_time_ms = get_time_ms();

    // Check whether the monotonic clock failed.
    if (initial_time_ms == UINT64_MAX)
    {
        fprintf(stderr, "ERROR: Failed to initialize debounce timer.\n");
        hal_cleanup();
        return 1;
    }

    // Initialize the button event detector.
    button_event_init(initial_buttons, initial_time_ms);

    // Track the application's exit status.
    // 0 = Success, 1 = Error
    int exit_status = 0;

     // Pause for 5 milliseconds between button readings.
    struct timespec delay = {
        .tv_sec = 0,
        .tv_nsec = 5000000L
    };


    // Continuously monitor the FPGA pushbuttons.
    while (application_running)
    {
        // Read the current pushbutton state.
        uint32_t current_buttons = button_read();

        // Check whether the button reading failed.
        if (current_buttons == UINT32_MAX)
        {
            fprintf(stderr, "ERROR: Failed to read pushbuttons.\n");
            exit_status = 1;
            break;
        }

        // Obtain the current monotonic timestamp.
        uint64_t current_time_ms = get_time_ms();

        // Check whether reading the clock failed.
        if (current_time_ms == UINT64_MAX)
        {
            fprintf(stderr, "ERROR: Failed to read system clock.\n");
            exit_status = 1;
            break;
        }

        // Detect newly confirmed button presses after debouncing.
        uint32_t pressed_events =
            button_detect_press(current_buttons, current_time_ms);

        
        // Prioritize reset 
        if (pressed_events & KEY_RESET)
        {
            parking_reset();

            printf("Parking occupancy reset to %u.\n",
                (unsigned int)parking_get_occupancy());
        }
        else if (pressed_events & KEY_ENTRY)
        {
            if (parking_vehicle_entry() == 0)
            {
                printf("Vehicle entered. Occupancy: %u\n",
                    (unsigned int)parking_get_occupancy());
            }
            else
            {
                printf("Entry rejected: Parking lot is full.\n");
            }
        }
        else if (pressed_events & KEY_EXIT)
        {
            if (parking_vehicle_exit() == 0)
            {
                printf("Vehicle exited. Occupancy: %u\n",
                    (unsigned int)parking_get_occupancy());
            }
            else
            {
                printf("Exit rejected: Parking lot is empty.\n");
            }
        }

        // Update the LED display to reflect the current parking occupancy.
        if (pressed_events != 0)
        {
            led_display_occupancy(parking_get_occupancy());
        }
                
       
        // Suspend execution until the delay expires.
        nanosleep(&delay, NULL);

    }


    // Release FPGA memory mappings and associated resources.
    hal_cleanup();

    return exit_status;
}