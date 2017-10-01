#include <msp430.h>
/*MSP430G2553*/
/*
Multiple Blink
50% duty cycle
*/

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= (BIT0 + BIT6);			// configure P1.0 and P1.6 as output
	P1OUT &= ~(BIT0 + BIT6);		// reset the LEDs (so they are off in the start)

	while (1)
	{
		P1OUT ^= (BIT0 + BIT6);		// toggle (XOR) P1.0 and P1.6 LEDs
		__delay_cycles(250000);     // a ~250000uS delay
	}
}