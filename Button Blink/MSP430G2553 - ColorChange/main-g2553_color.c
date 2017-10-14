#include <msp430.h>

/**
MSP430G2553
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

	int LEDcl = 1;			// int LED
	P1DIR |= LED1;			// Set P1.0 to output direction
	P1DIR |= LED2;			// Set P1.6 to output direction

	P1REN = BUTTON;						//pull-resistor
	P1OUT = BUTTON;						//sets pull-up resistor, writes "1" 

	while (1)
	{
		if (!(P1IN & BUTTON)) {			//if Button not pressed
			_delay_cycles(5000);		//Delay for blink cycle
			LEDcl = !LEDcl;				//alternate 1 and 0 for switch statement control
		}
		switch (LEDcl)
		{
		case 0:
			P1OUT ^= LED1;	//Blink red
			P1OUT &= ~LED2;  //green off
			_delay_cycles(175000);	//delay
			break;

		case 1:
			P1OUT ^= LED2; //green on
			P1OUT &= ~LED1; //red off
			_delay_cycles(175000);	//delay
			break;

		}
	}

}