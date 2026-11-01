# parking_occupancy_program
A C-based parking occupancy monitoring system for the DE10-Standard FPGA board that tracks vehicle entry and exit.
## Parking Occupancy Monitoring System

The Parking Occupancy Monitoring System is an embedded systems project developed in C for the **Terasic DE10-Standard FPGA development board**. The application is designed to monitor parking lot occupancy by tracking vehicles entering and exiting through push-button inputs.

The system maintains a running count of occupied and available parking spaces, displays occupancy information on the board's seven-segment displays, and uses LEDs to provide visual status indicators.

The project integrates the FPGA hardware with the ARM-based Hard Processor System (HPS) and uses a modular C architecture to organize hardware access and application logic.

**Key technical concepts** include memory-mapped I/O, hardware abstraction, digital input processing, occupancy tracking, and real-time display updates.
