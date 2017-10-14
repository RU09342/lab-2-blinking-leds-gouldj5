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
"For starters, you will need to blink one of the on-board LED's at a particular rate. It is up to you to determine what rate you want to blink it at, however it has to be symmetrical (50% Duty Cycle), meaning equal times on and off. You should attempt multiple different speeds before moving on to the next part of the lab."

#### Tasks
* [x] Blink one of the on-board LED's at a particular rate (50% duty cycle)
* [x] Extra Work

## Compatibility
* MSP430F5529
* MSP430FR2311
* MSP430FR6989
* MSP430FR5594
* MSP430G2553

The simple blink procedure for this lab required little to no change across processors and luckily was easily configured with each board's LED1 port. 

# Functionality Description

Blinks a particular LED with 50% duty cycle (time off = time on)

### Detailed Description

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
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= BIT0;				// configure P1.0 as output
	P1OUT &= ~BIT0;				// reset the LEDs (so they are off in the start)


	while (1)
	{
		P1OUT ^= 0x01;			// toggle (XOR) P1.0 LED
		for (count=0;count<20000;count++);  // a ~250000uS delay
	}
}
```

# Extra Work Description
#### UART LED Control : Single Character
On the G2553, UART was integrated to control both LEDs on the board with a single letter

* Uses UART code from Lab1
* Interrupt takes data recieved and defined array to data string
* data string is handled in case switch statements
* simple blink code is integrated with 'q' 

##### Code
```C
#include <msp430.h>
//MSP430G2553
//UART LED Control

//Credit to Benn Thomsen
// Website: https://bennthomsen.wordpress.com/engineering-toolbox/ti-msp430-launchpad/msp430g2553-hardware-uart/
void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength);

static volatile char data;

void main(void)

{       //MAIN UART INIT
	WDTCTL = WDTPW + WDTHOLD;      // Stop WDT

	P1DIR |= BIT0 + BIT6;           // Set the LEDs on P1.0, P1.6 as outputs
	P1OUT = BIT0;                   // Set P1.0

	BCSCTL1 = CALBC1_1MHZ;          // Set DCO to 1MHz
	DCOCTL = CALDCO_1MHZ;          // Set DCO to 1MHz

								   /* Configure hardware UART */
	P1SEL = BIT1 + BIT2;          // P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2;         // P1.1 = RXD, P1.2=TXD
	UCA0CTL1 |= UCSSEL_2;          // Use SMCLK
	UCA0BR0 = 104;                 // Set baud rate to 9600 with 1MHz clock (Data Sheet 15.3.13)
	UCA0BR1 = 0;                   // Set baud rate to 9600 with 1MHz clock
	UCA0MCTL = UCBRS0;             // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;          // Initialize USCI state machine
	IE2 |= UCA0RXIE;               // Enable USCI_A0 RX interrupt

	__bis_SR_register(LPM0_bits + GIE); // Enter LPM0, interrupts enabled
}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	data = UCA0RXBUF;
	UARTSendArray("Received command: ", 18);
	UARTSendArray(&data, 1);
	UARTSendArray("\n\r", 2);

	switch (data) {
	case 'R':
	{
		P1OUT |= BIT0;              //turn on RED LED
	}
	break;
	//***********************************************************
	case 'r':
	{
		P1OUT &= ~BIT0;             //turn off RED LED
	}
	break;
	//************************************************************* 
	case 'G':
	{
		P1OUT |= BIT6;              //turn on Green LED
	}
	break;
	//**************************************************************    
	case 'g':
	{
		P1OUT &= ~BIT6;             //turn off Green LED
	}
	break;
	//**************************************************************
	case 's':
	{
		P1OUT &= ~BIT0;             //turn off RED LED
		P1OUT &= ~BIT6;             //AND turn off GREEN LED
	}
	break;
	//**************************************************************
	case 'q':                                       //simple blink procedure
    {
	    int count = 0;				//initialize count

    	while (1)       //WILL GO FOREVER, NEEDS RESET TO ENTER OTHER FUNCITONS
	    {
		        P1OUT ^= 0x01;						// toggle (XOR) P1.0 LED
		        for (count=0;count<20000;count++);  // a ~250000uS delay
	    }
	}
	break;
	//************************************************************
	
	default:
	{
		UARTSendArray("Unknown Command: ", 17);
		UARTSendArray(&data, 1);
		UARTSendArray("\n\r", 2);
	}
	break;
	}
}

void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength) {
	// Send number of bytes Specified in ArrayLength in the array at using the hardware UART 0
	// Example usage: UARTSendArray("Hello", 5);
	// int data[2]={1023, 235};
	// UARTSendArray(data, 4); // Note because the UART transmits bytes it is necessary to send two bytes for each integer hence the data length is twice the array length

	while (ArrayLength--) { // Loop until StringLength == 0 and post decrement
		while (!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
		UCA0TXBUF = *TxArray; //Write the character at the location specified py the pointer
		TxArray++; //Increment the TxString pointer to point to the next character
	}
}
```
#### SOS
On the G2553, the blink was set up to morse code to transmit SOS. UART morse code transfer is being integrated
* Uses a defined interval for blink and patterns
* Delays are managed using interrupts (more interrupt description in lab 3)
* Blinks in Morse code SOS (short-short-short, long-long-long, short-short-short)

##### Code
```C
#include <msp430g2553.h>
/*
Repeatedly flases the morse code SOS (3 short, 3 long, 3 short flashes, then pause)
on the MSP430's built-in red LED.

Credit to:
Carlton Duffett
Boston University
*/

#define interrupt_time 30

volatile unsigned char state;
volatile unsigned int short_interval;
volatile unsigned int long_interval;
volatile unsigned int pause_interval;
volatile unsigned int interrupt_counter;
volatile unsigned int blink_counter;

int main(void) {
	WDTCTL = (WDTPW + WDTTMSEL + WDTCNTCL + 0 + 1);   // WATCHDOG TIMER
													  /* watchdog timer was configured to interval timer to set
													  * the WDTIFG flag in the special register IFG1 and give a certain delay between
													  * the letters of the morse code
													  */

	IE1 |= WDTIE;   // Delays are managed using interrupts. WDT is managed by watchdog

	P1DIR |= 0x01;  // P1.0 to output
	P1OUT = 0;      // light off

					// initialize state variables
	short_interval = interrupt_time;	    // 30, one unit
	long_interval = 3 * interrupt_time;	    // 3 * 30, interupts for 3 units
	pause_interval = 7 * interrupt_time;    // 7 * 30, pause between
	state = 1;                              // current state of the SOS signal
	interrupt_counter = short_interval;     // initialize the main counter (# of interrupts)
	blink_counter = 0;                      // initialize the blink counter (# of blinks)

	_bis_SR_register(GIE + LPM0_bits);      // enable interrupts and turn CPU off

	return 0;
}

// Watchdog Timer interrupt handler 
// occurs at regular intervals of about 8K/1.1MHz ~= 7.4ms
interrupt void WDT_interval_handler() {

	if (--interrupt_counter == 0) {

		switch (state) {

			// first set of short blinks
		case 1:
			P1OUT ^= 1;                             // XOR with 1 to toggle LED, done a total of 6 times for each series of blinks
			if (blink_counter > 4)
			{                                       // 5 intervals for each group of blinks (3 on, 2 off)
				blink_counter = 0;
				interrupt_counter = long_interval;  // 3-unit pause, same as a long_interval
				state = 2;
			}
			else {
				blink_counter++;
				interrupt_counter = short_interval;
			}
			break;

			// pause between first two chars
		case 2:
			// during pauses, no need to toggle P1.0
			state = 3;
			interrupt_counter = long_interval;
			break;

			// long blinks
		case 3:
			P1OUT ^= 1; // XOR with 1 to toggle LED
			if (blink_counter > 4) {
				blink_counter = 0;
				interrupt_counter = long_interval;
				state = 4;
			}
			else {
				blink_counter++;
				if (P1OUT & 1)
					interrupt_counter = long_interval;
				else
					interrupt_counter = short_interval; // short unit between long blinks
			}
			break;

			// pause between second two chars
		case 4:
			state = 5;
			interrupt_counter = short_interval;
			break;

			// second set of short blinks
		case 5:
			P1OUT ^= 1; // XOR with 1 to toggle LED
			if (blink_counter > 4) {
				blink_counter = 0;
				interrupt_counter = pause_interval;
				state = 6;
			}
			else {
				blink_counter++;
				interrupt_counter = short_interval;
			}
			break;

			// long pause between SOS signals
		case 6:
			interrupt_counter = short_interval;
			state = 1;
			break;
		} // switch
	} // if
} // interrupt

  //Function WDT_interval_handler as handler for
  // interrupt 10, using a macro defined in the include file
ISR_VECTOR(WDT_interval_handler, ".int10")
```



