#include <msp430.h>
/*MSP430F5529*/
/*
Simple Blink
50% duty cycle
*/

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= BIT0;				// configure P1.0 and P1.6 as output
	P1OUT &= ~BIT0;				// reset the LEDs (so they are off in the start)

	int count = 0;				//initalize count

	while (1)
	{
		P1OUT ^= 0x01;		// toggle (XOR) P1.0 and P1.6 LEDs
		for (count=0;count<20000;count++);     // a ~250000uS delay
	}
}