# Parking Occupancy Management System
# SWE-350
#
# Define the DE10-Standard's 50 MHz onboard clock.
# Clock period = 20 nanoseconds.

create_clock -name CLOCK_50 -period 20.000 [get_ports {CLOCK_50}]

# Calculate clock uncertainty for setup and hold timing analysis.
derive_clock_uncertainty