/*
 * PWM.h
 *
 * Created: 3/23/2024 8:17:03 AM
 *  Author: hp
 */ 

#include "../INC/micro_config.h"
#include "../INC/std_types.h"
#include "../INC/common_macros.h"


#ifndef PWM_H_
#define PWM_H_

/************************************************************************/
/*									TIMER2_PWM	                        */
/************************************************************************/

void Timer2_PWM_init();

void Timer2_PWM_SetDuty(u8 setDutyCycle);

void Timer2_PWM_Stop();

void Timer2_PWM_Dec();


/************************************************************************/
/*									TIMER1A_PWM	                        */
/************************************************************************/


void Timer1A_PWM_init();

void Timer1A_PWM_SetDuty(u8 setDutyCycle);

void Timer1A_PWM_Stop();

void Timer1A_PWM_Dec();







#endif /* PWM_H_ */