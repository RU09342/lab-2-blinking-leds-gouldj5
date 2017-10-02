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
	P1DIR = LED1;			// configure LED P1.0 to output direction
	P1OUT &= ~LED1;		// Set output latch for power-on state

						//BIT0 is LED1 - RED

	P1DIR &= ~BUTTON;
	P1REN ^= BUTTON;	//enable pull-resistor
	P1OUT ^= BUTTON;	//sets pull-up resistor

	PM5CTL0 &= ~LOCKLPM5;           /*On FR5x family devices, and F5x devices,
									after entering LPMx.5, the port control registers
									and the port pin logic are sewered.
									This prevents the CPU’s internal boot code to
									reprogram the port pins after wakeup from low
									power mode with disabled CPU core.
									Your application can then configure the
									port controls as they are expected to be,
									and then re-establish the link between controls
									and pin logic without any glitches on pins that
									have been output pins during LPM.*/


	while (1)						//while->always
	{

		if (!(BUTTON & P1IN))
			P1OUT |= LED1; //Blink LED
		else
			P1OUT &= ~LED1; //turn off LED
	}
}