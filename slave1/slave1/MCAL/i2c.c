 /******************************************************************************
 *
 * Module: I2C(TWI)
 *
 * File Name: i2c.c
 *
 * Description: Source file for the I2C(TWI) AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/
 
#include "i2c.h"

void TWI_init(void)
{
    /* Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
    TWBR = 0x02;
	TWSR = 0x00;
	
    /* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */
    TWAR = 0b00000010; // my address = 0x01 :) 
	
    TWCR = (1<<TWEN); /* enable TWI */
}

void TWI_start(void)
{
    /* 
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void)
{
    /* 
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_write(u8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /* 
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

u8 TWI_readWithACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

u8 TWI_readWithNACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

u8 TWI_getStatus(void)
{
    u8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}



u8 I2C_Mem_Write(u8 DeviceAdd, u8 MemAddress, u8 *pData)
{
	/* Generate Start */
	TWI_start();
	if (TWI_getStatus() != TW_START)
	return ERROR;
	
	// Send Slave Address
	TWI_write(DeviceAdd);
	if (TWI_getStatus() != TW_MT_SLA_W_ACK)
	return ERROR;
	
	// Send Memory Address
	TWI_write(MemAddress);
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	return ERROR;

	// Send Data
	TWI_write(*pData);
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	return ERROR;

	/* Send the Stop Bit */
	TWI_stop();
	
	return SUCCESS;
}



u8 I2C_Mem_Read(u8 DeviceAdd, u8 MemAddress, u8 *pData, u8 size)
{
	/* Generate Start */
	TWI_start();
	if (TWI_getStatus() != TW_START)
	return ERROR; // Error handling, or return an error code

	// Send Slave Address with Write Bit
	TWI_write(DeviceAdd);
	if (TWI_getStatus() != TW_MT_SLA_W_ACK)
	return ERROR; // Error handling, or return an error code

	// Send Memory Address
	TWI_write(MemAddress);
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	return ERROR; // Error handling, or return an error code

	// Generate Repeated Start
	TWI_start();
	if (TWI_getStatus() != TW_REP_START)
	return ERROR; // Error handling, or return an error code

	// Send Slave Address with Read Bit
	TWI_write(DeviceAdd | 0x01); // Read mode
	if (TWI_getStatus() != TW_MT_SLA_R_ACK)
	return ERROR; // Error handling, or return an error code

	// Read Data
	for (int i = 0; i < size - 1; ++i) {
		pData[i] = TWI_readWithACK();
	}
	pData[size - 1] = TWI_readWithNACK(); // Read last byte with NACK

	/* Send the Stop Bit */
	TWI_stop();
	
	return SUCCESS;
}
