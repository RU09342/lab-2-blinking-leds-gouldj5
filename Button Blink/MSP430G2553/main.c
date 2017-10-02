#include <msp430.h>

/**
button blink
Switch between blinking two LEDs with 50% duty cycle when button is pressed.
This is an extension of blink.c. This code will allow you switch between which LED is blinking by pressing a button.
msp430FR5994
*/
#define BUTTON BIT3		//define easily identifiable characters as BITs
#define LED1 BIT0
#define LED2 BIT6

unsigned int enabled = 0; // declare int to keep track of when the button was pressed
						  // By default P1.0 will flash.

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
	
	P1OUT &= ~LED1;			//Clear P1.0 output latch for a defined power-on state
	P1DIR = LED1;			// Set P1.0 to output direction

	P1DIR &= ~BUTTON;		//sets button input direction   
	P1REN ^= BUTTON;  //pull-resistor
	P1OUT ^= BUTTON;  //sets pull-up resistor, writes "1" 

	while (1)
	{
		if (!(P1IN & BUTTON))
			P1OUT |= LED1;
			P1OUT &= ~LED2;
		else
			P1OUT &= ~LED1; //LED off when button not pressed
			P1OUT |= LED2;
	}
}
