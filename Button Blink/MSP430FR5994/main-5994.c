#include <msp430.h>
/*MSP430FR5994*/
/*
Button Blink
*/

#define BUTTON BIT6
#define LED1 BIT0

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR = LED1;					// configure LED P1.0 to output direction
	P1OUT &= ~LED1;					// Set output latch for power-on state


	P5DIR &= ~BUTTON;				// set button at P5.6 for input
	P5REN ^= BUTTON;				// pull resistor
	P5OUT ^= BUTTON;				// pull-up resistor

	PM5CTL0 &= ~LOCKLPM5;           //enable high impedence


	while (1)						//while->always
	{

		if (!(BUTTON & P5IN))
			P1OUT |= LED1;			//Blink LED
		else
			P1OUT &= ~LED1;			//turn off LED
	}
}