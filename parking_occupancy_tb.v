/*
 * SWE-350
 * Parking Occupancy Management System
 *
 * Testbench:
 * Simulates input signals to verify that the
 * parking occupancy counter behaves correctly.
 */

 `timescale 1ns / 1ps
 
 
 
// Testbench module for the parking occupancy controller.
module parking_occupancy_tb;
	 // Testbench clock signal.
    // This variable will be controlled by the testbench to
    // simulate the rising and falling edges of a hardware clock.
   reg clk;
	 
	 // Active-low reset signal for testing.
	// reset_n = 0: Reset is active.
	// reset_n = 1: Normal operation.
	// The testbench will change this value to verify reset behavior.
	reg reset_n;
	
	// Simulated vehicle entry event.
	// entry_event = 1: A vehicle entry has been detected.
	// entry_event = 0: No entry event.
	// The testbench will control this signal to test counter increments.
	reg entry_event;
	
	// Simulated vehicle exit event.
	// exit_event = 1: A vehicle exit has been detected.
	// exit_event = 0: No exit event.
	// The testbench controls this signal to verify that
	// the occupancy counter decreases correctly.
	reg exit_event;
	
	// Occupancy counter output from the controller.
	// Receives the current number of parked vehicles.
	// The testbench will monitor this value to verify
	// that entry, exit, and reset operations work correctly.
	wire [3:0] occupancy_count;
	
	// Instance of parking_occupancy used to test
	// uut - unit under test
	parking_occupancy uut (
    // Port connections
	 
	 // Connect the controller's clk input to the testbench clock
	 // .clk refers to the clock input in parking_occupancy.v
	 // (clk) refers to the reg clk signal declare here in testbench
	 .clk(clk),
	 
	 // Connect the testbench reset signal to the controller's reset input.
    .reset_n(reset_n),
	 
	 // Connect the simulated vehicle entry event
	// to the occupancy controller's entry input.
	.entry_event(entry_event),
	
	// Connect the simulated vehicle exit event
	// to the occupancy controller's exit input.
	.exit_event(exit_event),
	
	// Connect the controller's occupancy count output
	// to the testbench signal for verification.
	.occupancy_count(occupancy_count)
 
	 
	);
	
	// Initialize the simulation clock.
	// The clock starts at logic 0.
	initial
	begin
		clk = 1'b0;
	end
	// Generate repeated clock transitions.
	// Wait 5 simulation time units, then invert the clock.
	// This repeats throughout the simulation.
	always
	begin
		#5; // means wait 5 nanoseconds before changing the clock
		clk = ~clk;
	end
	
	
	// Initialize the testbench input signals.
	// This block executes once when simulation begins.
	initial
	begin
		// Start with reset active so the occupancy
		// counter initializes to zero at a rising clock edge.
		reset_n = 1'b0;
		
		// No vehicle entry event at the start of simulation.
		entry_event = 1'b0;
		
		// No vehicle exiting at the start of simulation.
		exit_event = 1'b0;
		
		// Keep reset active for 20 ns.
		// This allows the counter to reset on the rising clock
		// edges at 5 ns and 15 ns.
		#20;

		// Release the active-low reset.
		// The controller can now process entry and exit events.
		reset_n = 1'b1;
		
		// Wait another 10 ns after releasing reset.
		// Simulation time will now be 30 ns.
		#10;

		// Simulate a vehicle entering the parking lot.
		// Set entry_event to 1 to indicate a valid entry.
		entry_event = 1'b1;
		
		// Keep entry_event active for one complete clock cycle.
		#10;

		// Clear the entry event so the same vehicle
		// is not counted again at the next rising clock edge.
		entry_event = 1'b0;
		
		// Wait for the next rising clock edge at 45 ns
		// and allow the counter's nonblocking update to complete.
		#6;

		// Verify that exactly one vehicle was counted.
		if (occupancy_count === 4'd1)
		begin
			// Display a test-passed message here.
			// Print a confirmation when the expected count is observed.
			$display("PASS: First vehicle entry counted correctly.");
			$display("PASS: Occupancy count = %0d", occupancy_count);	
		end
		else
		begin
			// Report failure if the actual occupancy 
			// does not match the expected count of 1.
			$display("FAIL: Expected 1 vehicle, got %0d", occupancy_count);
		end
		// End the simulation after completing the first test.
		// Prevents the clock generator from running indefinitely.
		$finish;
		

		
	end
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

endmodule