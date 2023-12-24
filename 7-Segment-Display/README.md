#7 Segment Display

A software to perform a decimal counter on a 7-segment display. System inputs are two push buttons. System output is 1 seven segment display.
Two interrupts to be configured on GPIO falling edge, one for each button. The first ISR increment the counter. The second ISR decrement the counter.
The main function perform the display actions. Race condition is taken into consideration to protect the counters from being corrupted.
