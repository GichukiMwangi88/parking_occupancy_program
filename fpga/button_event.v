/*
 * SWE-350
 * Parking Occupancy Management System
 *
 * Button Event Detector
 *
 * Description:
 * Synchronizes an active-low pushbutton input and
 * generates one clock-cycle pulse per button press.
 */

module button_event (
    input wire clk,
    input wire reset_n,
    input wire button_n,
    output wire event_pulse
);
// First flip-flop captures the asynchronous button signal.
reg button_sync1;

// Second flip-flop receives the synchronized signal.
reg button_sync2;

// Stores the previous synchronized button state.
// Used to detect a transition from released (1) to pressed (0).
reg button_previous;

// Indicates that the button has been observed released
// after reset and is ready to generate press events.
reg button_armed;

// Synchronize the pushbutton input and track its previous state.
always @(posedge clk)
begin
    if (!reset_n)
    begin
    // Start in a safe, disarmed state.
    // Require a genuine synchronized release before
    // permitting button press events.
		button_sync1    <= 1'b0;
		button_sync2    <= 1'b0;
		button_previous <= 1'b0;
		button_armed    <= 1'b0;
    end
    else
    begin
        // First stage samples the asynchronous button input.
        button_sync1 <= button_n;

        // Second stage samples the previous first-stage value.
        button_sync2 <= button_sync1;

        // Remember the previous synchronized button state.
        button_previous <= button_sync2;
		  
		  // Arm the detector only after the synchronized
		  // button has been observed in the released state.
		  if (button_sync2)
		  begin
			  button_armed <= 1'b1;
		  end
		end
end

// Generate one pulse on a synchronized button press.
// Only allow events after a valid release has armed the detector.
assign event_pulse = reset_n && button_armed && 
								button_previous && !button_sync2;

endmodule