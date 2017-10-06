Joshua Gould
# Simple Blink


## Compatible output
* MSP430G2553
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989

## Procedure
Blinks LED with 50% duty cycle
250000us

#Notes
The simple blink procedure for this lab required little to no change across processors and luckily was easily configured with each board's LED1 port.
### UART Control: Single Character
For starters, it would be interesting to tie in some of the UART code that was used before into this project. You might want to have the speed of the blinking controlled by a character sent over UART. For example, 's' could be a slow setting, 'm' could be medium speed, 'f' could be fast, and 'o' could be off.

### UART Control: Rate Number
Instead of depending on a character, what if we wanted to send a blinking period in milliseconds? So instead of 's', you could send something like '100' which corresponds to a 100 millisecond delay between the time the LED turns on again. Before you decide to tackle this, I would take a look at using a logic analyzer to see exactly what your computer is sending to your microprocessor. Also remember that the code previously provided will only service the UART Buffer one character at a time.