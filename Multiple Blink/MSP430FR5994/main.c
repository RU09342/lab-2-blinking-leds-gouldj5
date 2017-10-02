#include <msp430.h>
/*MSP430FR5994*/
/*
Multiple Blink
50% duty cycle
*/

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= (BIT0 + BIT1);			// configure LED P1.0 and 2.0 to output direction
	P1OUT &= ~(BIT0 + BIT1);		// Set output latch for power-on state

									//BIT0 is LED1 - RED
									//BIT1 is LED2 - GREEN

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

	int count = 0;                  //loops 2 LEDs to blink continuously
	int count1 = 0;

	while (1)						//while->always
	{

		if (count >= 15000) {
			P1OUT ^= BIT0;
			count = 0;
		}
		if (count1 >= 30000) {
			P1OUT ^= BIT1;
			count1 = 0;
		}
		count++;
		count1++;
	}
}