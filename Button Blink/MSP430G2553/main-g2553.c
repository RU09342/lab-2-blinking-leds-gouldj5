#include <msp430.h>

/**
MSP430G2553
button blink

*/
#define BUTTON BIT3		//define easily identifiable characters as BITs
#define LED1 BIT0

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

	while (1)						//while->always
	{

		if (!(BUTTON & P1IN))
			P1OUT |= LED1;			//turn on LED
		else
			P1OUT &= ~LED1;			//turn off LED
	}
}
