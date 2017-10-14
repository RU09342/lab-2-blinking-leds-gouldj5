#include <msp430.h>
/*MSP430FR5994*/
/*
Simple Blink
50% duty cycle
*/

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR |= BIT0;				// configure P1.0 and P1.6 as output
	P1OUT &= ~BIT0;				// reset the LEDs (so they are off in the start)

	PM5CTL0 &= ~LOCKLPM5;		//prevents the CPU’s internal boot code to reprogram the port pins after wakeup from low power mode with disabled CPU core.

	int count = 0;

	while (1)
	{
		P1OUT ^= 0x01;			// toggle LEDs on and off
		for (count = 0; count<15000; count++); 
								//from 0-15000 cycles count +1 for delay
	}
}