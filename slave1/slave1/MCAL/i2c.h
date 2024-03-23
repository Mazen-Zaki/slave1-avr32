 /******************************************************************************
 *
 * Module: I2C(TWI)
 *
 * File Name: i2c.h
 *
 * Description: Header file for the I2C(TWI) AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/ 


#ifndef I2C_H_
#define I2C_H_

#include "../INC/micro_config.h"
#include "../INC/std_types.h"
#include "../INC/common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start 
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave

#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave

#define I2C_MEM_ADD_LSB(__ADDRESS__)                       ((u8)((u16)((__ADDRESS__) & (u16)0x00FF)))
#define I2C_MEM_ADD_MSB(__ADDRESS__)                       ((u8)((u16)(((u16)((__ADDRESS__) & (u16)0xFF00)) >> 8)))

#define I2C_SLA_W(SLA)   ()

typedef enum
{
	I2C_MEMADD_SIZE_8BIT = 8 ,
	I2C_MEMADD_SIZE_16BIT = 16
}I2C_MemAddSize;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init(void);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(u8 data);
u8 TWI_readWithACK(void); //read with send Ack
u8 TWI_readWithNACK(void); //read without send Ack
u8 TWI_getStatus(void);


u8 I2C_Mem_Write(u8 DeviceAdd, u8 MemAddress, u8 *pData);
u8 I2C_Mem_Read(u8 DeviceAdd, u8 MemAddress, u8 *pData, u8 size);


#endif /* I2C_H_ */
