/*
 * MOTORS.c
 *
 * Created: 3/23/2024 6:00:15 PM
 *  Author: hp
 */ 

#include "MOTORS.h"


void MOTORS_Init()
{
	Timer2_PWM_init();
	Timer1A_PWM_init();
	
	Encoder_Init();
	
	SET_BIT(MOTOR_ONE_DDR, MOTOR_ONE_PIN_ONE);
	SET_BIT(MOTOR_ONE_DDR, MOTOR_ONE_PIN_TWO);
	
	SET_BIT(MOTOR_TWO_DDR, MOTOR_TWO_PIN_ONE);
	SET_BIT(MOTOR_TWO_DDR, MOTOR_TWO_PIN_TWO);
}


void MOTORS_ControlCommand(u8 *command)
{
	u8 val = 0;
	
	val = command[0] - 48;
	val += (command[1] - 48) * 10;
	
	MOTORS_SetVal_SetDir(val, command[1], command[2]);
}

void MOTORS_SetVal_SetDir(u8 speed, u8 dirFirst, u8 dirSecond)
{
	if ((dirFirst == 'F') && (dirSecond == 'F'))
	{
		Timer1A_PWM_SetDuty(speed);
		Timer2_PWM_SetDuty(speed);
		
		SET_BIT(MOTOR_ONE_PORT, MOTOR_ONE_PIN_ONE);
		SET_BIT(MOTOR_TWO_PORT, MOTOR_TWO_PIN_ONE);
		
		CLEAR_BIT(MOTOR_ONE_PORT, MOTOR_ONE_PIN_TWO);
		CLEAR_BIT(MOTOR_ONE_PORT, MOTOR_TWO_PIN_TWO);
	}
	else if ((dirFirst == 'F') && (dirSecond == 'R'))
	{
		Timer1A_PWM_SetDuty(speed);
		Timer2_PWM_SetDuty((speed/2));
		
		SET_BIT(MOTOR_ONE_PORT, MOTOR_ONE_PIN_ONE);
		SET_BIT(MOTOR_TWO_PORT, MOTOR_TWO_PIN_ONE);
		
		CLEAR_BIT(MOTOR_ONE_PORT, MOTOR_ONE_PIN_TWO);
		CLEAR_BIT(MOTOR_ONE_PORT, MOTOR_TWO_PIN_TWO);
	}
	else if ((dirFirst == 'F') && (dirSecond == 'L'))
	{
		Timer1A_PWM_SetDuty((speed/2));
		Timer2_PWM_SetDuty(speed);
		
		SET_BIT(MOTOR_ONE_PORT, MOTOR_ONE_PIN_ONE);
		SET_BIT(MOTOR_TWO_PORT, MOTOR_TWO_PIN_ONE);
		
		CLEAR_BIT(MOTOR_ONE_PORT, MOTOR_ONE_PIN_TWO);
		CLEAR_BIT(MOTOR_ONE_PORT, MOTOR_TWO_PIN_TWO);
	}
	else if ((dirFirst == 'R') && (dirSecond == 'R'))
	{
		Timer1A_PWM_SetDuty(speed);
		Timer2_PWM_SetDuty((speed/4));
		
		SET_BIT(MOTOR_ONE_PORT, MOTOR_ONE_PIN_ONE);
		SET_BIT(MOTOR_TWO_PORT, MOTOR_TWO_PIN_ONE);
		
		CLEAR_BIT(MOTOR_ONE_PORT, MOTOR_ONE_PIN_TWO);
		CLEAR_BIT(MOTOR_ONE_PORT, MOTOR_TWO_PIN_TWO);
	}
	else if ((dirFirst == 'L') && (dirSecond == 'L'))
	{
		Timer1A_PWM_SetDuty((speed/4));
		Timer2_PWM_SetDuty(speed);
		
		SET_BIT(MOTOR_ONE_PORT, MOTOR_ONE_PIN_ONE);
		SET_BIT(MOTOR_TWO_PORT, MOTOR_TWO_PIN_ONE);
		
		CLEAR_BIT(MOTOR_ONE_PORT, MOTOR_ONE_PIN_TWO);
		CLEAR_BIT(MOTOR_ONE_PORT, MOTOR_TWO_PIN_TWO);
	}
	else if ((dirFirst == 'B') && (dirSecond == 'B'))
	{
		Timer1A_PWM_SetDuty(speed);
		Timer2_PWM_SetDuty(speed);
		
		CLEAR_BIT(MOTOR_ONE_PORT, MOTOR_ONE_PIN_ONE);
		CLEAR_BIT(MOTOR_TWO_PORT, MOTOR_TWO_PIN_ONE);
		
		SET_BIT(MOTOR_ONE_PORT, MOTOR_ONE_PIN_TWO);
		SET_BIT(MOTOR_ONE_PORT, MOTOR_TWO_PIN_TWO);
	}
	else if ((dirFirst == 'B') && (dirSecond == 'L'))
	{
		Timer1A_PWM_SetDuty((speed/2));
		Timer2_PWM_SetDuty(speed);
		
		CLEAR_BIT(MOTOR_ONE_PORT, MOTOR_ONE_PIN_ONE);
		CLEAR_BIT(MOTOR_TWO_PORT, MOTOR_TWO_PIN_ONE);
		
		SET_BIT(MOTOR_ONE_PORT, MOTOR_ONE_PIN_TWO);
		SET_BIT(MOTOR_ONE_PORT, MOTOR_TWO_PIN_TWO);
	}
	else if ((dirFirst == 'B') && (dirSecond == 'R'))
	{
		Timer1A_PWM_SetDuty(speed);
		Timer2_PWM_SetDuty((speed/2));
		
		CLEAR_BIT(MOTOR_ONE_PORT, MOTOR_ONE_PIN_ONE);
		CLEAR_BIT(MOTOR_TWO_PORT, MOTOR_TWO_PIN_ONE);
		
		SET_BIT(MOTOR_ONE_PORT, MOTOR_ONE_PIN_TWO);
		SET_BIT(MOTOR_ONE_PORT, MOTOR_TWO_PIN_TWO);
	}
	else if (dirFirst == 'S')
	{
		Timer2_PWM_Stop();
		Timer1A_PWM_Stop();
	}
	
	
}
