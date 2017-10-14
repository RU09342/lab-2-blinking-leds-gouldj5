
#include <msp430.h>
//MSP430G2553
//multiple blink extra work 
//button design with alternating, speed change, blinking

int main(void) {

	// Stops the watchdog timer
	WDTCTL = WDTPW + WDTHOLD;

	P1DIR |= (BIT0 + BIT6);			// configure LED P1.0 and 1.6 to output direction
	P1OUT &= ~(BIT0 + BIT6);

	P1REN |= BIT3;	// Turn on on-board resistor to P1.3
	P1OUT |= BIT3;

	volatile unsigned int i = 0; // loop variable is volatile and initialize

	while (1) {
		if ((P1IN & BIT3) == 0)		//runs at port input
		{
			if (i == 1) {
				i = 0;
			}
			else if (i == 0) {
				i = 1;
			}
		}

		switch (i) {
		case 0:
			P1OUT ^= BIT0; // Toggle Red LED
			__delay_cycles(150000); // set blink rate
			break;
		case 1:
			P1OUT ^= BIT6; // Toggle Green LED 
			__delay_cycles(90000);  // different rate of blink
			break;
		}



	}
}