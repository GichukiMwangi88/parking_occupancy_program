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

		// Test 1: Simulate a vehicle entering the parking lot.
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

		//Test 2: Simulate one vehicle exiting the parking lot.
		exit_event = 1'b1;

		// Keep the exit event active for one clock cycle.
		#10;

		// Clear the exit event to avoid counting it again.
		exit_event = 1'b0;

		// Allow the counter update to settle before checking.
		#1;

		// Verify that the vehicle exit decremented occupancy.
		if (occupancy_count === 4'd0)
		begin
			$display("PASS: Vehicle exit counted correctly.");
			$display("PASS: Occupancy count = %0d", occupancy_count);
		end
		else
		begin
			$display("FAIL: Expected 0 vehicles after exit, got %0d",
					occupancy_count);
		end
		
		// Test 3: Verify that an exit at zero occupancy
		// does not cause the counter to underflow.

		// Simulate an exit while the parking lot is empty.
		exit_event = 1'b1;

		// Hold the exit event for one clock cycle.
		#10;

		// Clear the exit event.
		exit_event = 1'b0;

		// Allow the counter update to settle.
		#1;

		// Verify occupancy remains zero.
		if (occupancy_count === 4'd0)
		begin
			$display("PASS: Exit at zero occupancy prevented underflow.");
			$display("PASS: Occupancy count = %0d", occupancy_count);
		end
		else
		begin
			$display("FAIL: Occupancy underflow detected. Expected 0, got %0d",
             occupancy_count);
		end
		
		// Test 4: Simulate 10 vehicles entering the parking lot.
		repeat (10)
		begin
			// Assert vehicle entry.
			entry_event = 1'b1;

			// Hold entry_event for one clock cycle.
			#10;

			// Clear the entry event.
			entry_event = 1'b0;

			// Wait one clock cycle before the next entry.
			#10;
		end
		// Test 4: Verify occupancy reaches maximum capacity.
		#1;

		// Check that exactly 10 vehicles were counted.
		// 4 - represents 4 bits
		// 'd - decimal representation
		// 10 - expected value
		if (occupancy_count === 4'd10)
		begin
			$display("PASS: Parking lot reached maximum capacity.");
			$display("PASS: Occupancy count = %0d", occupancy_count);
		end
		else
		begin
			$display("FAIL: Expected 10 vehicles, got %0d",
             occupancy_count);
		end
		
		// Test 5: Attempt vehicle entry when parking is full.

		// Simulate an additional vehicle attempting to enter.
		entry_event = 1'b1;

		// Hold the entry signal for one clock cycle.
		#10;

		// Clear the entry event.
		entry_event = 1'b0;

		// Allow the counter update to settle.
		#1;
		// Verify that the 11th vehicle entry is rejected.
		// Occupancy must remain at the maximum capacity of 10.
		if (occupancy_count === 4'd10)
		begin
			$display("PASS: Entry rejected at maximum capacity.");
			$display("PASS: Occupancy count = %0d", occupancy_count);
		end
		else
		begin
			$display("FAIL: Capacity limit violated. Expected 10, got %0d",
             occupancy_count);
		end
		
		// Test 6: Verify that a vehicle can exit a full parking lot.

		// Simulate one vehicle exiting.
		exit_event = 1'b1;

		// Hold the exit event for one clock cycle.
		#10;

		// Clear the exit event.
		exit_event = 1'b0;

		// Allow the counter update to settle.
		#1;
		
		// Verify that one vehicle exited the full parking lot.
		// Expected occupancy: 10 - 1 = 9.
		if (occupancy_count === 4'd9)
		begin
			$display("PASS: Vehicle exited full parking lot.");
			$display("PASS: Occupancy count = %0d", occupancy_count);
		end
		else
		begin
			$display("FAIL: Expected 9 vehicles after exit, got %0d",
             occupancy_count);
		end
		
		// Test 7: Verify a vehicle can enter after a space becomes available.

		// Simulate one new vehicle entering the parking lot.
		entry_event = 1'b1;

		// Keep the entry event active for one clock cycle.
		#10;

		// Clear the entry event.
		entry_event = 1'b0;

		// Allow the counter update to settle.
		#1;
		
		// Verify that a new vehicle can enter after a space is freed.
		// Expected occupancy: 9 + 1 = 10.
		if (occupancy_count === 4'd10)
		begin
			$display("PASS: Vehicle re-entry after exit successful.");
			$display("PASS: Occupancy count = %0d", occupancy_count);
		end
		else
		begin
			$display("FAIL: Expected 10 vehicles after re-entry, got %0d",
             occupancy_count);
		end
		
		// Test 8: Verify synchronous active-low reset.

		// Assert reset while occupancy is 10.
		reset_n = 1'b0;

		// Wait for the next rising clock edge.
		@(posedge clk);

		// Allow the nonblocking assignment to complete.
		#1;
		
		// Verify that the synchronous reset cleared occupancy.
		// Expected occupancy: 0.
		if (occupancy_count === 4'd0)
		begin
			$display("PASS: Synchronous active-low reset successful.");
			$display("PASS: Occupancy count = %0d", occupancy_count);
		end
		else
		begin
			$display("FAIL: Reset failed. Expected 0, got %0d",
             occupancy_count);
		end
		
		// Test 9: Verify reset takes priority over vehicle entry.

		// Keep reset asserted.
		reset_n = 1'b0;

		// Simulate a vehicle entering while reset is active.
		entry_event = 1'b1;

		// Wait for the controller to process the inputs.
		@(posedge clk);

		// Allow the nonblocking assignment to complete.
		#1;

		// Clear the entry event.
		entry_event = 1'b0;
		
		// Verify that reset takes priority over vehicle entry.
		// Expected occupancy: 0.
		if (occupancy_count === 4'd0)
		begin
			$display("PASS: Reset takes priority over vehicle entry.");
			$display("PASS: Occupancy count = %0d", occupancy_count);
		end
		else
		begin
			$display("FAIL: Reset priority violated. Expected 0, got %0d",
             occupancy_count);
		end
		
		// Test 10: Verify reset takes priority over vehicle exit.

		// Keep reset active.
		reset_n = 1'b0;

		// Simulate a vehicle exit while reset is asserted.
		exit_event = 1'b1;

		// Wait for the next rising clock edge.
		@(posedge clk);

		// Allow the nonblocking assignment to complete.
		#1;

		// Clear the exit event.
		exit_event = 1'b0;
		
		// Verify that reset takes priority over vehicle exit.
		// Expected occupancy: 0.
		if (occupancy_count === 4'd0)
		begin
			$display("PASS: Reset active during vehicle exit.");
			$display("PASS: Occupancy count = %0d", occupancy_count);
		end
		else
		begin
			$display("FAIL: Expected 0 during reset and exit, got %0d",
             occupancy_count);
		end
		
		// Test 11: Prepare for simultaneous entry and exit testing.

		// Release the active-low reset.
		reset_n = 1'b1;

		// Allow one rising clock edge with reset inactive.
		@(posedge clk);
		
		// Allow the nonblocking assignment to complete.
		#1;
		
		// Establish a known occupancy before
		// testing simultaneous entry and exit events.

		// Simulate one vehicle entering.
		entry_event = 1'b1;

		// Wait for the rising clock edge.
		@(posedge clk);

		// Allow the nonblocking assignment to complete.
		#1;

		// Clear the entry event.
		entry_event = 1'b0;
		
		// Verify that normal counting resumes after reset.
		// Expected occupancy: 1.
		if (occupancy_count === 4'd1)
		begin
			$display("PASS: Vehicle entry successful after reset.");
			$display("PASS: Occupancy count = %0d", occupancy_count);
		end
		else
		begin
			$display("FAIL: Expected 1 vehicle after reset, got %0d",
             occupancy_count);
		end
		
		// Test 12: Verify simultaneous entry and exit events.

		// Assert both vehicle events.
		entry_event = 1'b1;
		exit_event  = 1'b1;

		// Wait for the next rising clock edge.
		@(posedge clk);

		// Allow the nonblocking assignment to complete.
		#1;

		// Clear both events.
		entry_event = 1'b0;
		exit_event  = 1'b0;
		
		// Verify simultaneous entry and exit do not change occupancy.
		// Expected occupancy: 1.
		if (occupancy_count === 4'd1)
		begin
			$display("PASS: Simultaneous entry and exit handled correctly.");
			$display("PASS: Occupancy count = %0d", occupancy_count);
		end
		else
		begin
			$display("FAIL: Simultaneous events changed occupancy. Expected 1, got %0d",
             occupancy_count);
		end
		
		// Test 13: Prepare to verify reset priority over exit.
		// Current occupancy is 1.

		// Simulate another vehicle entering.
		entry_event = 1'b1;

		// Wait for the next rising clock edge.
		@(posedge clk);

		// Allow the nonblocking assignment to complete.
		#1;

		// Clear the entry event.
		entry_event = 1'b0;
		
		// Verify that occupancy reached 2 before testing reset priority.
		// Expected occupancy: 2.
		if (occupancy_count === 4'd2)
		begin
			$display("PASS: Occupancy initialized to 2 for reset priority test.");
			$display("PASS: Occupancy count = %0d", occupancy_count);
		end
		else
		begin
			$display("FAIL: Expected occupancy of 2, got %0d",
             occupancy_count);
		end
		
		// Test 14: Verify reset takes priority over vehicle exit.
		// Starting occupancy is 2.

		// Assert reset and exit simultaneously.
		reset_n = 1'b0;
		exit_event = 1'b1;

		// Wait for the next rising clock edge.
		@(posedge clk);

		// Allow the nonblocking assignment to complete.
		#1;

		// Clear the exit event.
		exit_event = 1'b0;
		
		// Verify that reset takes priority over vehicle exit.
		// Starting occupancy: 2.
		// Expected occupancy after reset: 0.
		if (occupancy_count === 4'd0)
		begin
			$display("PASS: Reset correctly overrides vehicle exit.");
			$display("PASS: Occupancy count = %0d", occupancy_count);
		end
		else
		begin
			$display("FAIL: Reset priority violated. Expected 0, got %0d",
             occupancy_count);
		end
		

		// End the simulation after completing all test scenarios.
		// Prevents the clock generator from running indefinitely.
		$finish;
		
	end
	
endmodule