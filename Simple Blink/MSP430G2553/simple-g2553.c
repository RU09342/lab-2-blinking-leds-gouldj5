#include <msp430.h>
/*MSP430G2553*/

/*
simple blink
50% duty cycle
*/
void main(void)
{
	WDCTL = WDTPW | WDTHOLD;	//stop watchdog timer
	P1DIR |= 0x01;				//conf P1.0 as output with DIR reg

	while (1)
	{
		P1OUT ^= 0X01;			//toggle LED
		_delay_cycles(250000);	// a ~250000us delay

	}
}