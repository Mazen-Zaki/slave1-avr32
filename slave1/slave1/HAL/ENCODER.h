/*
 * ENCODER.h
 *
 * Created: 3/23/2024 6:15:48 AM
 *  Author: hp
 */ 

#include "../INC/micro_config.h"
#include "../INC/std_types.h"
#include "../INC/common_macros.h"



#ifndef ENCODER_H_
#define ENCODER_H_


typedef enum
{
	Encoder_one = 0,
	Encoder_two
}Encoder_Numb;


void Encoder_Init();

void Encoder_IncPulse(Encoder_Numb encoderNumb);

void Encoder_AddBlocks(u8 blocksNumb);

void Encoder_DeleteBlocks();

void Encoder_ChangeBlockSize(u16 pulsesNumb);

u8 Encoder_IsEncodersEqual();

u8 Encoder_IsBlocksFinished();

void Encoder_Rebalance();



#endif /* ENCODER_H_ */