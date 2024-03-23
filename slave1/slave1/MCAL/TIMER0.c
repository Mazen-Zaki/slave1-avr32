/*
 * TIMER0.c
 *
 * Created: 3/23/2024 5:25:42 AM
 *  Author: hp
 */ 

#include "TIMER0.h"

f64 Tick = 0;

void TIMER0_init_CTC_mode()
{
	TCNT0 = 0;    // Set Timer initial value to 0
	OCR0  = 250; // Set Compare Value
	TIMSK |= (1<<OCIE0); // Enable Timer0 Compare Interrupt
	/* Configure timer0 control register 
	 * 1. Non PWM mode FOC0=1
	 * 2. CTC Mode WGM01=1 & WGM00=0
	 * 3. No need for OC0 in this example so COM00=0 & COM01=0 
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<FOC0) | (1<<WGM01) | (1<<CS02) | (1<<CS00);
}



void TIMER0_IncTick()
{
	Tick++;
}



f64 TIMER0_GetTick()
{
	return Tick;
}