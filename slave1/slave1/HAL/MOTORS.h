/*
 * MOTORS.h
 *
 * Created: 3/23/2024 6:00:32 PM
 *  Author: hp
 */ 

#include "../INC/micro_config.h"
#include "../INC/std_types.h"
#include "../INC/common_macros.h"

#include "../MCAL/EXTI0.h"
#include "../MCAL/EXTI1.h"

#include "ENCODER.h"


#ifndef MOTORS_H_
#define MOTORS_H_


#define MOTOR_ONE_PORT			PORTA
#define MOTOR_ONE_DDR			DDRA
#define MOTOR_ONE_PIN_ONE		PA0
#define MOTOR_ONE_PIN_TWO		PA1


#define MOTOR_TWO_PORT			PORTB
#define MOTOR_TWO_DDR			DDRB
#define MOTOR_TWO_PIN_ONE		PB0
#define MOTOR_TWO_PIN_TWO		PB1


void MOTORS_Init();

void MOTORS_ControlCommand(u8 *command);





#endif /* MOTORS_H_ */