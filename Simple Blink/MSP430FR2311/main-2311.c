#include <msp430.h>
/*MSP430FR2311*/
/*
Simple Blink
50% duty cycle
*/

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer

	P1DIR |= BIT0;			// configure P1.0 and P1.6 as output
	P1OUT &= BIT0;			// reset the LEDs (so they are off in the start)

	PM5CTL0 &= ~LOCKLPM5;			//Disable GPIO power-on default high-impedence

	int count = 0;                  //loops 2 LEDs to blink continuously


	while (1)						//while->always
	{

		if (count >= 15000) {
			P1OUT ^= BIT0;
			count = 0;
		}
		count++;
	}
}