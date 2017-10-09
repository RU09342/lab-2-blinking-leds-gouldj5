#include <msp430g2553.h>
/*
Repeatedly flases the morse code SOS (3 short, 3 long, 3 short flashes, then pause)
on the MSP430's built-in red LED.

Credit to:
Carlton Duffett
Boston University
*/

#define interrupt_time 30

volatile unsigned char state;
volatile unsigned int short_interval;
volatile unsigned int long_interval;
volatile unsigned int pause_interval;
volatile unsigned int interrupt_counter;
volatile unsigned int blink_counter;

int main(void) {
	WDTCTL = (WDTPW + WDTTMSEL + WDTCNTCL + 0 + 1);   // WATCHDOG TIMER
													  /* watchdog timer was configured to interval timer to set
													  * the WDTIFG flag in the special register IFG1 and give a certain delay between
													  * the letters of the morse code
													  */

	IE1 |= WDTIE;   // Delays are managed using interrupts. WDT is managed by watchdog

	P1DIR |= 0x01;  // P1.0 to output
	P1OUT = 0;      // light off

					// initialize state variables
	short_interval = interrupt_time;	    // 30, one unit
	long_interval = 3 * interrupt_time;	    // 3 * 30, interupts for 3 units
	pause_interval = 7 * interrupt_time;    // 7 * 30, pause between
	state = 1;                              // current state of the SOS signal
	interrupt_counter = short_interval;     // initialize the main counter (# of interrupts)
	blink_counter = 0;                      // initialize the blink counter (# of blinks)

	_bis_SR_register(GIE + LPM0_bits);      // enable interrupts and turn CPU off

	return 0;
}

// Watchdog Timer interrupt handler 
// occurs at regular intervals of about 8K/1.1MHz ~= 7.4ms
interrupt void WDT_interval_handler() {

	if (--interrupt_counter == 0) {

		switch (state) {

			// first set of short blinks
		case 1:
			P1OUT ^= 1;                             // XOR with 1 to toggle LED, done a total of 6 times for each series of blinks
			if (blink_counter > 4)
			{                                       // 5 intervals for each group of blinks (3 on, 2 off)
				blink_counter = 0;
				interrupt_counter = long_interval;  // 3-unit pause, same as a long_interval
				state = 2;
			}
			else {
				blink_counter++;
				interrupt_counter = short_interval;
			}
			break;

			// pause between first two chars
		case 2:
			// during pauses, no need to toggle P1.0
			state = 3;
			interrupt_counter = long_interval;
			break;

			// long blinks
		case 3:
			P1OUT ^= 1; // XOR with 1 to toggle LED
			if (blink_counter > 4) {
				blink_counter = 0;
				interrupt_counter = long_interval;
				state = 4;
			}
			else {
				blink_counter++;
				if (P1OUT & 1)
					interrupt_counter = long_interval;
				else
					interrupt_counter = short_interval; // short unit between long blinks
			}
			break;

			// pause between second two chars
		case 4:
			state = 5;
			interrupt_counter = short_interval;
			break;

			// second set of short blinks
		case 5:
			P1OUT ^= 1; // XOR with 1 to toggle LED
			if (blink_counter > 4) {
				blink_counter = 0;
				interrupt_counter = pause_interval;
				state = 6;
			}
			else {
				blink_counter++;
				interrupt_counter = short_interval;
			}
			break;

			// long pause between SOS signals
		case 6:
			interrupt_counter = short_interval;
			state = 1;
			break;
		} // switch
	} // if
} // interrupt

  //Function WDT_interval_handler as handler for
  // interrupt 10, using a macro defined in the include file
ISR_VECTOR(WDT_interval_handler, ".int10")