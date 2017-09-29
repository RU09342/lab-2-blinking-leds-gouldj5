#include <msp430.h>

/**
button blink
Switch between blinking two LEDs with 50% duty cycle when button is pressed.
This is an extension of blink.c. This code will allow you switch between which LED is blinking by pressing a button.
msp430FR5994
*/

unsigned int enabled = 0; // declare int to keep track of when the button was pressed
						  // By default P1.0 will flash.

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
	P1DIR |= 0x01;         // configure P1.0 and P1.1 as output
	P1REN |= 0x00;        // reset the LEDs
	P1OUT |= 0x09;

	volatile unsigned int i; 

	while (1)
	{
		while (P1IN & BIT3)
		{
			P1OUT &= ~BIT0;
		}
		P1OUT |= 0x01;	//toggle P1.0
	}
}
