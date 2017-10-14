#include <msp430.h>
//MSP430G2553
/*
//Multiple Blink
*/
int main(void) {


	WDTCTL = WDTPW + WDTHOLD;			// Stops the watchdog timer

	P1DIR |= (BIT0 + BIT6);			// configure LED P1.0 and 1.6 to output direction
	P1OUT &= ~(BIT0 + BIT6);		//// reset the LEDs (so they are off in the start)

	while (1)
	{

		P1OUT ^= BIT0;			// Toggle Red LED
		__delay_cycles(150000); // set blink rate

		P1OUT ^= BIT6;			// Toggle Green LED 
		__delay_cycles(90000);  // different rate of blink
	}




}