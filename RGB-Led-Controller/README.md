# RGB Led Controller

The system is consisted of 1 push button and 1 RGB LED. The Push button is connected to PORTB pin 3. The 3 LED pins are connected to port B pins 5, 6 and 7. 
The Push button is active low, without external pull up resistor. The code scans the button periodically. At each valid button press, the Software changes the RGB LED color.
A button press is considered valid only when a falling edge is detected on the button pin.
Button debouncing feature is added. The LED provides 8 colors controlled by the enabled colors mix (RED + GREEN + BLUE).
