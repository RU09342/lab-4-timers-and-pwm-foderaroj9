#include <msp430.h> 
/*
 *Joe Foderaro
 *Lab 4: Debouncing
 *5994
 */
 
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                       //Disable the GPIO power-on default high-z mode
    P5REN|=BIT6;                                //Enable resistor at P5.6
    P5OUT|=BIT6;                                //Set pullup resistor
    P1DIR|=BIT0;                                //Set P1.0 to output
    P5IES|=BIT6;                                //Set edge detect to falling edge
    P5IE|=BIT6;                                 //Enable interrupt
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
   P5IE|=BIT6;                                  //enable P1.3 interrupts
   TA0CTL&=~BIT4;                               //Stop timer
   TA0CTL|=BIT2;                                //Clear timer
   P5IFG&=~BIT6;                                
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT^=BIT0;                                //Toggle LED at P1.0
    P5IE&=~BIT6;                                //Disable P5.6 interrupt
    P5IFG&=~BIT6;                               
    TA0CTL|=BIT4;                               //Turn timer to up mode
}