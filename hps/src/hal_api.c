/*
 * Robert Mwangi
 * SWE-350
 * November 19, 2026
 * Parking Occupancy Management System
 * 
 * References:
 * [1] Intel, Cyclone V HPS Technical Reference Manual.
 * [2] Linux man-pages, mmap(2).
 * 
 * File: hapl_api.c
 * 
 * Purpose: Implementation file to initialize hardware access to HPS 
 * hardware registers.
*/



#include "hal_api.h" // Provides our HAL function declarations
#include <stdio.h> // Provides perror() for error reporting
#include <stdint.h> // Provides types such as uint8_t and uint32_t
#include <fcntl.h>  // Provides open() flags such as O_RDWR and O_SYNC
#include <unistd.h> // Provides close()
#include <sys/mman.h> // Provides mmap(), munmap() and memory protection flags
#include "config.h"


// Function Prototypes
// Internal helper for mapping physical FPGA memory.
static void *map_physical(int memory_fd, unsigned int base, unsigned int span);

// File descriptor used to access physical memory.
// -1 indicates that /dev/mem is not currently open.
static int memory_fd = -1;

// Pointer to the beginning of the mapped FPGA memory region.
// NULL indicates that no valid memory mapping exists.
static uint8_t *virtual_base = NULL;

// Initialize access to FPGA hardware.
int hal_init(void)
{
   // Prevent repeated initialization if FPGA memory is already mapped.
    if (virtual_base != NULL)
    {
        return 0;
    }
    // Linux OS attempts to open the device
    // and request read/write access to the physical memory
    // and input/output operations
    memory_fd = open("/dev/mem", O_RDWR | O_SYNC);

    // If Linux fails to open memory location
    // Handle the error
    if (memory_fd == -1) 
    {
        // Handle the error
        perror("Failed to open /dev/mem");


        // Immediately exit hal_init()
        return -1;

    }

    // Map physical memory to virtual memory by calling the map_physical function
    virtual_base = map_physical(memory_fd, LW_BRIDGE_BASE, LW_BRIDGE_SPAN);

    // Check whether the memory mapping failed
    if(virtual_base == NULL)
    {
        // Close the file descriptor
        close(memory_fd);

        // Reset memory_fd to -1
        memory_fd = -1;

        // Return the failure status
        return -1;

    }

    return 0;

}

// Function that provides access to the LED, switch and seven segment display registers
volatile uint32_t *hal_get_register(uint32_t offset)
{
    // Check whether FPGA memory has been initialized.
    if(virtual_base == NULL)
    {
        // Hardware memory isn't initialized
        return NULL;

    }

    // Validate the requested register offset
    // Check whether the offset is not aligned to 4 bytes
    if((offset % 4) != 0)
    {
        return NULL;
    }

    // Check whether the requested register fits within the mapping region
    // If the requested register starts beyond the last position where a complete
    // 4-byte register can fit, reject the request
    if(offset > LW_BRIDGE_SPAN - sizeof(uint32_t))
    {
        return NULL;
    }

    // Returns a 32 bit pointer to the requested FPGA register
    return (volatile uint32_t *)(virtual_base + offset);

    
}

/**
 * Maps a physical memory region into the program's virtual address space.
 *
 * This allows the HPS application to access FPGA peripheral registers
 * (LEDs, switches, and HEX displays) using C pointers.
 *
 * Parameters:
 *   memory_fd - File descriptor for /dev/mem, opened previously.
 *   base      - Starting physical address of the FPGA memory region.
 *   span      - Number of bytes to map into virtual memory.
 *
 * Returns:
 *   Pointer to the mapped virtual memory region on success.
 *   NULL if memory mapping fails.
 */
static void *map_physical(int memory_fd, unsigned int base, unsigned int span)
{
    
    // Request a virtual memory mapping of the physical address region.
    void *mapped_address = mmap(
        NULL, // Let the OS choose the starting virtual address.
        span, // Number of bytes to map.
        PROT_READ | PROT_WRITE,  // Allow the program to both read and write mapped registers.
        MAP_SHARED,  // Use a shared mapping so writes access the underlying
                    // memory-mapped hardware region rather than a private copy.
        memory_fd, // File descriptor identifying /dev/mem.
        base  // Physical address where the mapping begins.
    );

    // mmap() returns MAP_FAILED if the mapping was unsuccessful.
    if (mapped_address == MAP_FAILED)
    {
        // Print the system error explaining why mmap() failed.
        perror("Unable to map physical memory");
        return NULL;
    }

    // Return the virtual address of the mapped region.
    // Other HAL functions can use this address with register
    // offsets to access specific FPGA peripheral registers.
    return mapped_address;
}

// Release hardware resources allocated during initialization.
void hal_cleanup(void)
{
    // Check whether virtual base contains a valid memory address
    if(virtual_base != NULL)
    {
        if((munmap(virtual_base,LW_BRIDGE_SPAN)) == -1)
        {
            perror("Failed to unmap the memory region");
        }
        else
        {
            /// Reset the pointer to NULL after successfully unmapping memory.
            virtual_base = NULL;

        }

    }

    // Check whether the file descriptor is valid.
    if (memory_fd >= 0)
    {
        //
        if(close(memory_fd) != 0)
        {
            perror("Failed to close the memory file descriptor");

        }

        // Mark the file descriptor as no longer owned by the HAL.
        memory_fd = -1;
        

    }

}