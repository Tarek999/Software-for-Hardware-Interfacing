# LED light controller:
* The system is consisted of 1 LED connected to PORTB pin number 2 (OC0) and 1 push button connected to PORTB pin number 0 with a pull 
down resistor.
* The switch is active low.
* The Software checks the state of the push button periodically.
* Button is considered pressed, if the pin value is held low for at least 50ms.
