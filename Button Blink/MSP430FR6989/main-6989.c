#include <msp430.h>
/*MSP430FR6989*/
/*
Button Blink
*/

#define BUTTON BIT1
#define LED1 BIT0

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR = LED1;					// configure LED P1.0 to output direction
	P1OUT &= ~LED1;					// Set output latch for power-on state

	P1DIR &= ~BUTTON;
	P1REN ^= BUTTON;				//enable pull-resistor
	P1OUT ^= BUTTON;				//sets pull-up resistor

	PM5CTL0 &= ~LOCKLPM5;          //enable high impedence


	while (1)						//while->always
	{

		if (!(BUTTON & P1IN))
			P1OUT |= LED1;			//turn on LED
		else
			P1OUT &= ~LED1;			//turn off LED
	}
}