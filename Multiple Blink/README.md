# LAB 2 - Multiple Blink
#### Joshua Gould
##### Created - 10-13-2017
##### Updated - 10-14-2017

## Library Used
msp430.h - default library

## Dependencies
* MSP430 Development board
* CCS coding software
* Two LEDs

## Set Requirements
"Now that we have blinked at least 1 LED, what about blinking multiple LEDS at the same time? The minimum that you need to develop is blinking at least two LEDs at two different rates. Although I am not going to give you a speed, you should probably pick a rate which is visible to a standard human. I really hope that you take this further and perform some of the extra work for this part of the lab exercise."

#### Tasks
* [x] Blink multiple LEDs at the same time
* [x] Blink LEDs at different rate
* [x] Extra Work

## Compatibility
* MSP430F5529
* MSP430FR2311
* MSP430FR6989
* MSP430FR5594
* MSP430G2553

# Functionality Description

Blinks LEDs at the same time at different rates

### Detailed Description

* Stops watchdog timer
* Defines output pins for both LEDs and defaults off
* sets eternal while loop and toggles LED pins with different delay cycles

### Example Code
```C
#include <msp430.h>
//MSP430G2553
/*
//Multiple Blink
*/
int main(void) {


	WDTCTL = WDTPW + WDTHOLD;		// Stops the watchdog timer

	P1DIR |= (BIT0 + BIT6);			// configure LED P1.0 and 1.6 to output direction
	P1OUT &= ~(BIT0 + BIT6);		// reset the LEDs (so they are off in the start)

	while (1)
	{

		P1OUT ^= BIT0;			// Toggle Red LED
		__delay_cycles(150000); // set blink rate

		P1OUT ^= BIT6;			// Toggle Green LED 
		__delay_cycles(90000);  // different rate of blink
	}
}
```

# Extra Work Description

#### Alternate Speed Control Blink
Both alternating blinks go at different rates for blinking when a button is pressed

#### Example Code
```C
#include <msp430.h>
//MSP430G2553
//multiple blink + extra work 
//button design with alternating, speed change, blinking

int main(void) {

	WDTCTL = WDTPW + WDTHOLD;		// Stops the watchdog timer

	P1DIR |= (BIT0 + BIT6);			// configure LED P1.0 and 1.6 to output direction
	P1OUT &= ~(BIT0 + BIT6);

	P1REN |= BIT3;	// Turn on on-board resistor to P1.3
	P1OUT |= BIT3;

	volatile unsigned int i = 0; // loop variable is volatile and initialize

	while (1) {
		if ((P1IN & BIT3) == 0)		//runs at port input
		{
			if (i == 1) {
				i = 0;
			}
			else if (i == 0) {
				i = 1;
			}
		}

		switch (i) {
		case 0:
			P1OUT ^= BIT0; // Toggle Red LED
			__delay_cycles(150000); // set blink rate
			break;
		case 1:
			P1OUT ^= BIT6; // Toggle Green LED 
			__delay_cycles(90000);  // different rate of blink
			break;
		}
	}
}
```
