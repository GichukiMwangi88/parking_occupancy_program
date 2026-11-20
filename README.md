# Parking Occupancy Management System

## Project Overview

The Parking Occupancy Management System is an embedded systems project developed for the **Terasic DE10-Standard FPGA Development Board**.

The system monitors parking lot occupancy by tracking vehicle entry and exit events through the board's push-button inputs. It maintains a running count of occupied parking spaces and prevents the occupancy count from exceeding the parking lot's maximum capacity or dropping below zero.

The project integrates **Verilog HDL for FPGA-based occupancy logic** with a **modular C application running on the ARM-based Hard Processor System (HPS)**.

Communication between the HPS and FPGA peripherals is implemented through memory-mapped I/O using the lightweight HPS-to-FPGA bridge.

## Project Objectives

- Track vehicle entry and exit events using push-button inputs.
- Maintain an accurate occupancy count for a parking lot with a maximum capacity of 10 vehicles.
- Prevent occupancy overflow and underflow.
- Use onboard LEDs to provide visual occupancy information.
- Implement structured and maintainable C code using hardware abstraction.
- Integrate FPGA hardware peripherals with an HPS application.
- Validate occupancy logic through simulation and hardware testing.

## System Architecture

The project consists of two primary components.

### 1. FPGA Occupancy Controller (Verilog HDL)

The FPGA component implements the occupancy tracking logic.

Key functionality includes:

- Incrementing the occupancy count when a valid entry event occurs.
- Decrementing the occupancy count when a valid exit event occurs.
- Enforcing a maximum occupancy of 10 vehicles.
- Preventing the occupancy count from becoming negative.
- Supporting reset functionality.
- Handling entry and exit events through sequential logic.

A Verilog testbench has been developed to verify the controller's behavior under different occupancy conditions.

### 2. HPS Application (C)

The HPS application runs under embedded Linux on the DE10-Standard board.

It uses a modular architecture that separates hardware access, input processing, occupancy management, and output control.

**Main software components:**

- `main.c` — Application initialization, execution, and shutdown.
- `hal_api.c` — Hardware abstraction and memory-mapped peripheral access.
- `button.c` — Reading the onboard push-button inputs.
- `button_event.c` — Processing push-button states into application events.
- `parking_controller.c` — Managing occupancy and enforcing parking capacity limits.
- `led.c` — Controlling the onboard LEDs to represent parking occupancy.

The application uses the lightweight HPS-to-FPGA bridge to access hardware peripheral registers.

## Hardware Platform

**Development Board:** Terasic DE10-Standard

**Processor:** ARM Cortex-A9 Hard Processor System

**FPGA:** Intel Cyclone V SoC FPGA

**Operating Environment:** Embedded Linux

**Programming Languages:** C and Verilog HDL

**Hardware Interfaces:**
- Push buttons for vehicle entry and exit simulation.
- LEDs for occupancy indication.
- Lightweight HPS-to-FPGA bridge for memory-mapped hardware access.

## Key Technical Concepts

The project demonstrates several embedded systems and software engineering concepts:

- Memory-mapped I/O
- Hardware abstraction layers (HAL)
- Bitwise operations and register manipulation
- Digital input processing
- Edge-based button event detection
- Sequential digital logic
- Verilog simulation and testbenches
- Modular C programming
- Capacity validation and boundary conditions
- Git version control and feature-branch development

## Testing and Validation

### FPGA Logic Verification

A Verilog testbench has been developed and executed to verify the parking occupancy controller.

The following test scenarios have produced passing simulation results:

- Vehicle entry increments occupancy.
- Vehicle exit decrements occupancy.
- Attempting to exit an empty parking lot does not cause underflow.
- Occupancy can reach the maximum capacity of 10 vehicles.
- Additional entry events are rejected when the parking lot is full.
- Vehicle exit from a full parking lot decreases occupancy correctly.

### HPS Application Testing

Development has progressed to the integration of the C application with the DE10-Standard hardware peripherals.

Testing activities include verifying memory-mapped register access, button input handling, LED control, and occupancy state transitions.

Full end-to-end hardware validation remains an ongoing activity.

## Current Development Status

**As of November 2026**

**Completed:**
- Implemented the Verilog occupancy controller.
- Developed and executed the initial Verilog testbench.
- Verified occupancy boundary conditions through simulation.
- Established the modular HPS application structure.
- Implemented the hardware abstraction layer.
- Developed push-button input and event-processing modules.
- Implemented occupancy management logic in C.
- Integrated LED output control into the HPS application.
- Integrated the main application with the hardware-control modules.
- Used GitHub issues, feature branches, and pull requests to manage development.

**In Progress / Planned:**
- Complete hardware integration testing on the DE10-Standard board.
- Validate button event handling and LED behavior under different occupancy conditions.
- Perform additional application-level and system-level testing.
- Improve error handling and documentation as needed.
- Evaluate future enhancements to occupancy visualization.

## Development Workflow

The project follows a feature-based development workflow using Git and GitHub.

Development tasks are organized using GitHub issues, with implementation changes developed in separate feature branches and integrated through pull requests.

This workflow supports incremental development, traceability, and maintainability.

## References

The following technical resources were consulted during development:

1. **Intel — Cyclone V Hard Processor System Technical Reference Manual**  
   Reference for the HPS architecture and HPS-to-FPGA bridge.

   https://www.intel.com/content/www/us/en/docs/programmable/683126/

2. **Linux Manual Pages — mmap(2)**  
   Reference for memory-mapped I/O and virtual memory mapping.

   https://man7.org/linux/man-pages/man2/mmap.2.html

3. **Linux Manual Pages — munmap(2)**  
   Reference for releasing mapped memory regions.

   https://man7.org/linux/man-pages/man2/munmap.2.html

4. **Linux Manual Pages — sigaction(2)**  
   Reference for signal handling and application shutdown.

   https://man7.org/linux/man-pages/man2/sigaction.2.html

5. **Linux Manual Pages — nanosleep(2)**  
   Reference for implementing timed delays.

   https://man7.org/linux/man-pages/man2/nanosleep.2.html

6. **Terasic — DE10-Standard Development Board Documentation**  
   Reference for hardware interfaces, push buttons, LEDs, and FPGA peripheral configuration.

   https://www.terasic.com.tw/

## Future Improvements

Potential future enhancements include:

- Seven-segment display integration for displaying occupancy counts.
- More comprehensive automated testing.
- Additional diagnostic output for hardware troubleshooting.
- Improved user feedback when the parking lot reaches maximum capacity.

---

**Project Status:** Active Development — HPS/FPGA Integration and Hardware Validation

