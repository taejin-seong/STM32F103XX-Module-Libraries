/*
 * clcd.c
 *
 *  Created on: 2022. 3. 22.
 *      Author: sungt
 */


#include "clcd.h"
#include "i2c.h"


void clcd_Init(void)
{
	delay_ms(20);

	clcd_Command(0x30);
	delay_ms(5);
	clcd_Command(0x30);
	delay_us(100);
	clcd_Command(0x30);
	clcd_Command(0x20);

	clcd_Command(CMD_FUNCTION_SET_OPTION3);
	clcd_Command(CMD_DISPLAY_OPTION1);
	clcd_Command(CMD_CLEAR_DISPLAY);
	clcd_Command(CMD_ENTRY_MODE_SET_OPTION3);
	clcd_Command(CMD_DISPLAY_OPTION5);

}


void clcd_Command(uint8_t cmd)
{
	uint8_t i2cBuff[4];
	uint8_t data_H, data_L;

	data_H = cmd & 0xF0;
	data_L = (cmd & 0x0F) << 4;

	i2cBuff[0] = data_H | EN; //load new command byte with En high
	i2cBuff[1] = data_H | 0x08; //update command while keeping backlight on
	i2cBuff[2] = data_L | EN; //load new command byte with En high
	i2cBuff[3] = data_L | 0x08; //update command while keeping backlight on

	HAL_I2C_Master_Transmit (&CLCD_I2C_PORT, CLCD_ADDRESS, i2cBuff, 4, 100);
}


void clcd_Data(uint8_t data)
{
	uint8_t data_t[4];
	uint8_t data_u, data_l;

	data_u = (data & 0xF0);
	data_l = ((data<<4) & 0xF0);

	data_t[0] = data_u | 0x0D;  //EN=1, RS=1
	data_t[1] = data_u | 0x09;  //EN=0, RS=1
	data_t[2] = data_l | 0x0D;  //EN=1, RS=1
	data_t[3] = data_l | 0x09;  //EN=0, RS=1

	HAL_I2C_Master_Transmit (&CLCD_I2C_PORT, CLCD_ADDRESS, data_t, 4, 100);
}


void clcd_Str(char *string)
{
	while(*string != '\0')
	{
		clcd_Data(*string);
		string++;
	}
}


void clcd_Position(uint8_t col, uint8_t row)
{
	clcd_Command(0x80 | (col * 0x40 + row));
}


void clcd_Clear(void)
{
	clcd_Command(CMD_CLEAR_DISPLAY);
}
