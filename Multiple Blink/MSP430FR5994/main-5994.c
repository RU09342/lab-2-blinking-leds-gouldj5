#include <msp430.h>
/*MSP430FR5994*/
/*
Multiple Blink
*/

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= (BIT0 + BIT1);			// configure LED P1.0 and 2.0 to output direction
	P1OUT &= ~(BIT0 + BIT1);		// Set output latch for power-on state

									//BIT0 is LED1 - RED
									//BIT1 is LED2 - GREEN

	PM5CTL0 &= ~LOCKLPM5;           //enable high impedence

	int count = 0;                  //loops 2 LEDs to blink continuously
	int count1 = 0;

	while (1)						//while->always
	{

		if (count >= 15000) {		//set limit
			P1OUT ^= BIT0;
			count = 0;				//initialize to zero
		}
		if (count1 >= 30000) {		//set limit 
			P1OUT ^= BIT1;			
			count1 = 0;
		}
		count++;					//increment count
		count1++;
	}
}