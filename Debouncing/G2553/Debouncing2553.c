#include <msp430.h> 
/*
 *Joe Foderaro
 *Lab 4: Debouncing
 *2553
 */
 
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                   // stop watchdog timer

    P1REN|=BIT3;                                //Enable resistor at P1.3
    P1OUT|=BIT3;                                //Set pullup resistor
    P1DIR|=BIT0;                                //Set P1.0 to output
    P1IES|=BIT3;                                //Set edge detect to falling edge
    P1IE|=BIT3;                                 //Enable interrupt
    TA0CCTL0 = CCIE;                           
    TA0CCR0 = 60000;                            //Set CCR0 of TA
    TA0CTL = TASSEL_2 + MC_0 + TACLR;           // SMCLK, stopped
    TA0CTL|=(BIT6+BIT7);                        //Divide clock by 8

    __bis_SR_register(LPM0_bits + GIE);         // Enter LPM0
    return 0;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
   P1IE|=BIT3;                                  //enable P1.3 interrupts
   TA0CTL&=~BIT4;                               //Stop timer
   TA0CTL|=BIT2;                                //Clear timer
   P1IFG&=~BIT3;                                
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT^=BIT0;                                //Toggle LED at P1.0
    P1IE&=~BIT3;                                //Disable P1.3 interrupt
    P1IFG&=~BIT3;                               
    TA0CTL|=BIT4;                               //Turn timer to up mode
}