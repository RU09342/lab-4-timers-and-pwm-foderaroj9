# Software PWM
The code for this lab is used to blink an LED with a changing duty cycle. The timer is set to CCR0 and varies by CCR1 with every button press.

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
5529: P1.2 and P4.7
5994: P1.0 and P1.1
2311: P1.0 and P2.0
6989: P1.0 and P1.1

## Code Functionality
* The general code for every board is the same. The differences include pin numbers for the inputs and outputs, and for the FR boards, High impedance mode must be turned off.
