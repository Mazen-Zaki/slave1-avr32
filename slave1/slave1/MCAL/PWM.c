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

	DDRD  = DDRD | (1<<PD7); // Configure PD7/OC2 as output pin --> pin where the PWM signal is generated from MC

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM21=1 & WGM20=1
	 * 3. Clear OC2 when match occurs (non inverted mode) COM20=0 & COM21=1
	 * 4. clock = F_CPU/8 CS20=0 CS21=1 CS22=0
	 */
	TCCR2 = (1<<WGM20) | (1<<WGM21) | (1<<COM21) | (1<<CS21);
}


void Timer2_PWM_SetDuty(u8 setDutyCycle)
{
	
	OCR2  = (setDutyCycle * 2.55); //Set Compare value
}


void Timer2_PWM_Stop()
{
	OCR2  = 0;
}


void Timer2_PWM_Dec()
{
	u8 temp = OCR2;
	
	temp -= 5;
	
	OCR2 = temp;
}


/************************************************************************/
/*									TIMER1A_PWM	                        */
/************************************************************************/


void Timer1A_PWM_init()
{
	TCNT1 = 0; // Set Timer Initial Value to 0

	OCR1A  = 0; //Set Compare value

	DDRD  = DDRD | (1<<PD5); // Configure PD5/OC1A as output pin --> pin where the PWM signal is generated from MC

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM21=1 & WGM20=1
	 * 3. Clear OC2 when match occurs (non inverted mode) COM20=0 & COM21=1
	 * 4. clock = F_CPU/8 CS20=0 CS21=1 CS22=0
	 */
	TCCR1A =(1<<WGM11) | (1<<COM1A1);
	
	TCCR1B = (1<<WGM12)| (1<<WGM13)| (1<<CS11);
}


void Timer1A_PWM_SetDuty(u8 setDutyCycle)
{
	OCR1A  = (setDutyCycle * 655.35); //Set Compare value
}

void Timer1A_PWM_Stop()
{
	OCR1A  = 0;
}

void Timer1A_PWM_Dec()
{
	u16 temp = OCR1A;
	
	temp -= 10;
	
	OCR1A = temp;
}