# Timer A Blink
The code for this lab is not much different than the Button interupt where we used the main counter to blink an LED with a 50% duty cycle. The only difference with this is that the code checks if the button is pressed and if it is, it debounces the signal by delaying it just a tad so that physical contact bouncing does not undesirably trigger any LEDs.
# The following boards are used in this lab:
* MSP430G2553
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989

## Dependencies
The dependencies for this lab is the MSP430.h library that is included when you build a new project in code composer

## Outputs:
The LEDs used for this are the following pins. 
G2553: P1.0 and P1.6
5529: P1.0 and P4.7
5594: P1.0 and P1.1
2311: P1.0 and P2.0
6989: P1.0 and P9.7

## Code Functionality
* The general code for every board is the same. The differences include pin numbers for the inputs and outputs, and for the FR boards, High impedance mode must be turned off.
