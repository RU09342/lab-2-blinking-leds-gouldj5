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
			for (count = 0; count<20000; count++);  // a ~250000uS delay
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