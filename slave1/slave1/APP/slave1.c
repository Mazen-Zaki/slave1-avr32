/*
 * slave1.c
 *
 * Created: 3/23/2024 3:25:31 AM
 *  Author: hp
 */ 

#include "../MCAL/TIMER0.h"
#include "../MCAL/uart.h"

#include "../HAL/ENCODER.h"
#include "../HAL/MOTORS.h"


#define NUMBER_OF_OVERFLOWS_PER_SECOND 4
#define BufferSize 8



void CheckForCommand();



u8 flag_harvestingProcess = 0;

/* TIMER0 Global Variables */
u8 g_tick = 0;

/* UART Global Variables */
u8 flag_startBuffer = 0;
u8 flag_newBufferComplete = 0;
u8 recivedBuffer[BufferSize];
u8 bufferCounter = 0;



/* Interrupt Service Routine for timer0 compare mode */
ISR(TIMER0_COMP_vect)
{
	g_tick++;
	if(g_tick == NUMBER_OF_OVERFLOWS_PER_SECOND)
	{
		TIMER0_IncTick();
	}
}


/* Interrupt Service Routine for uart */
ISR(USART_RXC_vect)
{
	u8 val = 0;
	 val = UART_recieveByte();
	 
	 if(val == '@')
	 {
		 flag_startBuffer = 1;
	 }
	 
	 if(flag_startBuffer == 1)
	 {
		 recivedBuffer[bufferCounter] = val;
		 bufferCounter++;
	 }
	 
	 if(val == ';')
	 {
		 flag_startBuffer = 0;
		 flag_newBufferComplete = 1;
		 bufferCounter = 0;
	 }
	
}


/* External INT0 Interrupt Service Routine */
ISR(INT0_vect)
{
	Encoder_IncPulse(Encoder_one);
}


/* External INT1 Interrupt Service Routine */
ISR(INT1_vect)
{
	Encoder_IncPulse(Encoder_two);
}


void CheckForCommand();

int main(void)
{
	TIMER0_init_CTC_mode();
	UART_init();
	MOTORS_Init();
	
	
    while(1)
    {
        if (flag_newBufferComplete == 1)
        {
			CheckForCommand();
			flag_newBufferComplete = 0;
        }
    }
}


void CheckForCommand()
{
	if (recivedBuffer[1] == 'C')
	{
		u8 temp[4];
		
		temp[0] = recivedBuffer[4];
		temp[1] = recivedBuffer[5];
		temp[2] = recivedBuffer[6];
		temp[3] = recivedBuffer[7];
		
		MOTORS_ControlCommand(temp);
	}
	else if (recivedBuffer[1] == 'N')
	{
		
	}
	else if (recivedBuffer[1] == 'E')
	{
		if (recivedBuffer[2] == 'B')
		{
			u16 val = 0;
			
			val = recivedBuffer[5] - 48;
			
			val += (recivedBuffer[4] - 48) * 10;
			
			val += (recivedBuffer[3] - 48) * 100;
			
			Encoder_ChangeBlockSize(val);
		}
	}
	else if (recivedBuffer[1] == 'A')
	{
		if (recivedBuffer[3] == 'H')
		{
			if (recivedBuffer[4] == 'S')
			{
				flag_harvestingProcess = 1;
			}
			else if (recivedBuffer[4] == 'E')
			{
				flag_harvestingProcess = 0;
			}
			else
			{
				/* Do Nothing */
			}
		}
	}
}