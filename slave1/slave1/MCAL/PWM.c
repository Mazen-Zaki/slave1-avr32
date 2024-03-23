/*
 * PWM.c
 *
 * Created: 3/23/2024 8:16:53 AM
 *  Author: hp
 */ 

#include "PWM.h"


/************************************************************************/
/*									TIMER2_PWM	                        */
/************************************************************************/

void Timer2_PWM_init()
{
	TCNT2 = 0; // Set Timer Initial Value to 0

	OCR2  = 0; //Set Compare value

	DDRB  = DDRB | (1<<PB3); // Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}


void Timer2_PWM_SetDuty(u8 setDutyCycle)
{
	
}


void Timer2_PWM_Stop()
{
	
}


void Timer2_PWM_Dec()
{
	
}


/************************************************************************/
/*									TIMER1A_PWM	                        */
/************************************************************************/


void Timer1A_PWM_init();

void Timer1A_PWM_SetDuty(u8 setDutyCycle);

void Timer1A_PWM_Stop();

void Timer1A_PWM_Dec();