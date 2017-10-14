# LAB 2 - Simple Blink
#### Joshua Gould
##### Created - 10-9-2017
##### Updated - 10-14-2017

## Library Used
msp430.h - default library

## Dependencies
* MSP430 Development board
* CCS coding software
* A button and LED

## Set Requirements
"Now that you have looked at blinking the LED from some built in delay, but what if we wanted to control the state of the LED by a button? You may think "Why would I need a Microcontroller to perform the job of a switch?". And that is where you come in. The bare minimum for this part of the lab is to essentially replicate a switch with your development board."

#### Tasks
* [x] Control the state of the LED by a button similar to a switch
* [x] Extra Work

## Compatibility
* MSP430F5529
* MSP430FR2311
* MSP430FR6989
* MSP430FR5594
* MSP430G2553

# Functionality Description
Change the state of an LED with a button on the board
### Detailed Description

* stop watchdog
* Use definitions to set output pins and button control
* Set pull-up resistor
* Set while and if conditions to set on and off statements

### Example Code
```C
#include <msp430.h>

/**
MSP430G2553
button blink

*/
#define BUTTON BIT3		//define easily identifiable characters as BITs
#define LED1 BIT0

unsigned int enabled = 0; 	// declare int to keep track of when the button was pressed
				// By default P1.0 will flash.

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
	
	P1OUT &= ~LED1;			//Clear P1.0 output latch for a defined power-on state
	P1DIR = LED1;			// Set P1.0 to output direction

	P1DIR &= ~BUTTON;		//sets button input direction   
	P1REN ^= BUTTON;  		//pull-resistor
	P1OUT ^= BUTTON;  		//sets pull-up resistor, writes "1" 

	while (1)						//while->always
	{

		if (!(BUTTON & P1IN))
			P1OUT |= LED1;			//turn on LED
		else
			P1OUT &= ~LED1;			//turn off LED
	}
}

```

# Extra Work Description

#### Color Change
Using the G2553, on a button press, the G2553 changes the LED pin from red to green and back, effectively changing color.

* declare integer for blink and state control
* define pins
* infinite while statement with if conditions to declare cycles of blink
* switch case statement to change between LED colors

#### Example Code
```C
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
```
