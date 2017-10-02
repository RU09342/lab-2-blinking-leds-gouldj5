#include <msp430.h>
/*MSP430FR5529*/
/*
Button Blink
*/

#define BUTTON BIT1
#define LED1 BIT0

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR = LED1;			// configure LED P1.0 to output direction
	P1OUT &= ~LED1;		// Set output latch for power-on state

	P2DIR &= ~BUTTON;
	P2REN ^= BUTTON;
	P2OUT ^= BUTTON;

	while (1)						//while->always
	{

		if (!(BUTTON & P2IN))
			P1OUT |= LED1; //Blink LED
		else
			P1OUT &= ~LED1; //turn off LED
	}
}