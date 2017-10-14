#include <msp430.h>
/*MSP430FR2311*/
/*
Button Blink
*/

#define BUTTON BIT1
#define LED1 BIT0

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR = LED1;					// configure LED P1.0 to output direction
	P1OUT &= ~LED1;		// Set output latch for power-on state

						//BIT0 is LED1 - RED

	P1DIR &= ~BUTTON;				// set button at P2.1 for input
	P1REN ^= BUTTON;				// pull-resistor
	P1OUT ^= BUTTON;				//set as pull-up

	PM5CTL0 &= ~LOCKLPM5;           //enable high impendence


	while (1)						//while->always
	{

		if (!(BUTTON & P1IN))
			P1OUT |= LED1;			//Blink LED
		else
			P1OUT &= ~LED1;			//turn off LED
	}
}