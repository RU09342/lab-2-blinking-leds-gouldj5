#include <msp430.h>
/*MSP430F5529*/
/*
Button Blink
*/

#define BUTTON BIT1
#define LED1 BIT0

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= LED1;					// configure LED P1.0 to output direction
	P1OUT &= ~LED1;					// Set output latch for power-on state

	P2DIR &= ~BUTTON;				// set button at P2.1 for input
	P2REN ^= BUTTON;				// pull-resistor
	P2OUT ^= BUTTON;				//set as pull-up

	while (1)						//while->always
	{

		if (!(BUTTON & P2IN))
			P1OUT |= LED1;			//Blink LED
		else
			P1OUT &= ~LED1;			//turn off LED
	}
}