#include <msp430.h>
/*MSP430FR5529*/
/*
Multiple Blink
50% duty cycle
*/

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= BIT0;			// configure LED P1.0 and 2.0 to output direction
	P1OUT &= ~BIT0;		// Set output latch for power-on state
	P4DIR |= BIT7;			// configure LED P2.0 to output direction
	P4OUT &= ~BIT7;

	int count = 0;                  //loops 2 LEDs to blink continuously
	int count1 = 0;

	while (1)						//while->always
	{

		if (count >= 15000) {
			P1OUT ^= BIT0;
			count = 0;
		}
		if (count1 >= 30000) {
			P4OUT ^= BIT7;
			count1 = 0;
		}
		count++;
		count1++;
	}
}