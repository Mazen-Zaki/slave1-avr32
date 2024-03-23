/*
 * ENCODER.c
 *
 * Created: 3/23/2024 6:15:27 AM
 *  Author: hp
 */ 

#include "ENCODER.h"

#include "../MCAL/EXTI0.h"
#include "../MCAL/EXTI1.h"


u16 BlockToPulse = 22;

u8 EncoderOnePulse = 0;
u8 EncoderTwoPulse = 0;

u8 EncoderOneBlock = 0;
u8 EncoderTwoBlock = 0;

u8 g_blocksNumbers = 0;



void Encoder_Init()
{
	INT1_Init();
	INT0_Init();
}


void Encoder_IncPulse(Encoder_Numb encoderNumb)
{
	if(encoderNumb == Encoder_one)
	{
		EncoderOnePulse++;
		
		if (EncoderOnePulse == BlockToPulse)
		{
			EncoderOneBlock++;
			EncoderOnePulse = 0;
		}
	}
	else if(encoderNumb == Encoder_two)
	{
		EncoderTwoPulse++;
		
		if (EncoderTwoPulse == BlockToPulse)
		{
			EncoderTwoBlock++;
			EncoderTwoPulse = 0;
		}
	}
	else
	{
		/*Do Nothing*/
	}
}


void Encoder_AddBlocks(u8 blocksNumb)
{
	g_blocksNumbers = blocksNumb;
}


void Encoder_DeleteBlocks()
{
	g_blocksNumbers = 0;
}


void Encoder_ChangeBlockSize(u16 pulsesNumb)
{
	BlockToPulse = pulsesNumb;
}


u8 Encoder_IsEncodersEqual()
{
	if (EncoderTwoPulse == g_blocksNumbers)
	{
		return SUCCESS;
	} 
	else
	{
		return ERROR;
	}
	
}


u8 Encoder_IsBlocksFinished()
{
	if ((EncoderOneBlock == EncoderOnePulse) && (EncoderTwoBlock == EncoderOnePulse))
	{
		return SUCCESS;
	}
	else
	{
		return ERROR;
	}
	
}


void Encoder_Rebalance()
{
	
	
}