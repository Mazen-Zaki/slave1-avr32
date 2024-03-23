/*
 * TIMER0.h
 *
 * Created: 3/23/2024 5:25:56 AM
 *  Author: hp
 */ 

#include "../INC/micro_config.h"
#include "../INC/std_types.h"
#include "../INC/common_macros.h"

#ifndef TIMER0_H_
#define TIMER0_H_

void TIMER0_init_CTC_mode();

void TIMER0_IncTick();

f64 TIMER0_GetTick();

#endif /* TIMER0_H_ */