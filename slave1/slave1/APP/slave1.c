/*
 * slave1.c
 *
 * Created: 3/23/2024 3:25:31 AM
 *  Author: hp
 */ 

#include "../MCAL/TIMER0.h"

#define NUMBER_OF_OVERFLOWS_PER_SECOND 4

/* global variable contain the ticks count of the timer */
u8 g_tick = 0;



/* Interrupt Service Routine for timer0 compare mode */
ISR(TIMER0_COMP_vect)
{
	g_tick++;
	if(g_tick == NUMBER_OF_OVERFLOWS_PER_SECOND)
	{
		TIMER0_IncTick();
	}
}




int main(void)
{
	TIMER0_init_CTC_mode();
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}