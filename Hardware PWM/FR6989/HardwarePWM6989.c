#include <msp430.h>
/*
 *Joe Foderaro
 *Lab 4: Hardware PWM
 *6989
 */
unsigned int x = 500;
unsigned int y = 0;
unsigned int count = 0;
void initializeTimer();
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;           // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= BIT0;                      // P1.0 to output
    P1SEL0 |= BIT0;
    P1SEL1 &= ~BIT0;

    P9DIR |= BIT7;
    P9OUT&=~BIT7;

    P1DIR &=~(BIT2);                    //set P1.2 input
    P1REN|=BIT2;                        //enable pull-up resistor
    P1OUT|=BIT2;
    P1IE |=BIT2;                        //enable interrupt on P1.2
    P1IES |= BIT2;
    P1IFG &=~(BIT2);                    //clear flag

    initializeTimer();

    __enable_interrupt();
    __bis_SR_register(LPM0 + GIE);      //Enable interrupts
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void debounce_timer(void)
{
    if (y == 1)
    {
        if (count == 50)
        {
            y = 0;
            count = 0;
        }

        else
        {
            count++;
        }
    }
}

void initializeTimer(void)
{
    TA0CCR0 = 1000-1;                       //Set max value
    TA0CCTL1 = OUTMOD_7;                    //Set output on reset
    TA0CCR1 = 500-1;
    TA0CTL = TASSEL_2 + MC_1;               //SMCLK/up

    TA1CCR0 = 4000;
    TA1CCTL0 |= CCIE;                       //Set compare
    TA1CTL |= TASSEL_2 + MC_1;              //SMCLK/up

}

#pragma vector=PORT1_VECTOR
__interrupt void PORT_1(void)
{
    P9OUT ^= BIT7;                          //toggle LED
    if (!(P1IN & BIT2))
    {
        if (y == 0)
        {
            y = 1;
            if (x >= 1000)
            {
                x = 1;                      //reset
            }

            else
            {
                x += 100;
            }
            TA0CCR1 = x - 1;
        }
    }
    P1IES ^= BIT2;                          //Allow for redo
    P1IFG &= ~BIT2;                         // clear flag
}