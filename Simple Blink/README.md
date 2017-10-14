# LAB 2 - Simple Blink
#### Joshua Gould
##### Created - 10-13-2017
##### Updated - 10-14-2017

## Library Used
msp430.h - default library

## Dependencies
* MSP430 Development board
* CCS coding software

## Set Requirements
For starters, you will need to blink one of the on-board LED's at a particular rate. It is up to you to determine what rate you want to blink it at, however it has to be symmetrical (50% Duty Cycle), meaning equal times on and off. You should attempt multiple different speeds before moving on to the next part of the lab.

## Compatibility
* MSP430F5529
* MSP430FR2311
* MSP430FR6989
* MSP430FR5594
* MSP430G2553
The simple blink procedure for this lab required little to no change across processors and luckily was easily configured with each board's LED1 port. 

# Functionality Description

Blinks a particular LED with 50% duty cycle (time off = time on)

## Detailed Description

* Watchdog timer stopped
* The LED was defined as an output and defaulted off.
* Toggle (XOR) P1.0 LED to turn on and off
* The blinking was done in a while loop toggling after a certain value (250000uS delay)

### Example Code
```C
#include <msp430.h>
/*MSP430G2553*/
/*
Simple Blink
50% duty cycle
*/

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= BIT0;				// configure P1.0 as output
	P1OUT &= ~BIT0;				// reset the LEDs (so they are off in the start)


	while (1)
	{
		P1OUT ^= 0x01;						// toggle (XOR) P1.0 LED
		for (count=0;count<20000;count++);  // a ~250000uS delay
	}
}
```

# Extra Work Description

#### UART Control: Single Character

#### SOS
On the G2553, the blink was set up to morse code to transmit SOS. UART morse code transfer is being investigated for future lab.
* Uses a defined interval for blink
* Delays are managed using interrupts (more interrupt description used in Lab3)
*

##Tasks
[x] Blink one of the on-board LED's at a particular rate (50% duty cycle)
[x] Extra Work



