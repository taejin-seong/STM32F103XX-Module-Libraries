/*
 * clcd.h
 *
 *  Created on: 2022. 3. 22.
 *      Author: sungt
 *
 *
 ******************************************************************************
 * @attention
 *
 *
 *   ============= 4 - Bit operation ================
 *     ---- ---- ---- ---- ---- ---- ----- -----
 *    | D7 | D6 | D5 | D4 | BL | EN | R/W | D/C |
 *    |---- ---- ---- ----|---- ---- ----- -----|
 *    |  	  DATA		  |		  Control	    |
 *    |-------------------|---------------------|
 *
 *
 * D[4-7] = Data and command bits
 * BL  = Backlight
 * EN  = Enaable bit (update LCD controller during High -> Low transistion)
 * R/W = Read or Write
 * D/C = Data or Command
 *
 * For bit defenition, please refer datasheet for HD44780
 *
 *
 */

#ifndef SRC_COMMON_HW_INCLUDE_CLCD_H_
#define SRC_COMMON_HW_INCLUDE_CLCD_H_

#include "hw_def.h"


#ifdef _USE_HW_CLCD





/* Select the SPIx port, you used */
#define CLCD_I2C_PORT                         hi2c1
//#define CLCD_I2C_PORT                         hi2c2


#define EN 0x04   // Enable bit
#define RW 0x01   // Read/Write bit
#define RS 0x02   // Register bit

#define CLCD_ADDRESS	0x27<<1 // I2C slave address

#define sbi(reg,bit)    reg |= (1<<(bit))	  // Set "bit"th bit of Register "reg"
#define cbi(reg,bit)    reg &= ~(1<<(bit))


#define CMD_CLEAR_DISPLAY                    0x01 // Clear All Display
#define CMD_RETURN_HOME                      0x02 // Cursor Position -> Return Home

#define CMD_ENTRY_MODE_SET_OPTION1           0x04 //   커서 좌측 이동, 화면이동 없음
#define CMD_ENTRY_MODE_SET_OPTION2           0x05 //   커서 좌측 이동, 화면 이동
#define CMD_ENTRY_MODE_SET_OPTION3           0x06 // * 커서 우측 이동, 화면이동 없음
#define CMD_ENTRY_MODE_SET_OPTION4           0x07 //   커서 우측 이동, 화면이동

#define CMD_DISPLAY_OPTION1                  0x08 //   화면 OFF,  커서 OFF,  커서 점멸 OFF
#define CMD_DISPLAY_OPTION2                  0x09 //   화면 OFF,  커서 OFF,  커서 점멸 ON
#define CMD_DISPLAY_OPTION3                  0x0A //   화면 OFF,  커서 ON ,  커서 점멸 OFF
#define CMD_DISPLAY_OPTION4                  0x0B //   화면 OFF,  커서 ON ,  커서 점멸 ON
#define CMD_DISPLAY_OPTION5                  0x0C //   화면 ON ,  커서 OFF,  커서 점멸 OFF
#define CMD_DISPLAY_OPTION6                  0x0D //   화면 ON ,  커서 OFF,  커서 점멸 ON
#define CMD_DISPLAY_OPTION7                  0x0E //   화면 ON ,  커서 ON ,  커서 점멸 OFF
#define CMD_DISPLAY_OPTION8                  0x0F // * 화면 ON ,  커서 ON ,  커서 점멸 ON

#define CMD_CURSOR_DISPLAY_SHIFT_OPTION1     0x10 //   커서 선택,   커서 좌측 이동
#define CMD_CURSOR_DISPLAY_SHIFT_OPTION2     0x14 //   커서 선택,   커서 우측 이동
#define CMD_CURSOR_DISPLAY_SHIFT_OPTION3     0x18 //   화면 선택,   커서 좌측 이동
#define CMD_CURSOR_DISPLAY_SHIFT_OPTION4     0x1C //   화면 선택,   커서 우측 이동

#define CMD_FUNCTION_SET_OPTION1              0x20 //   4비트,   화면1행,    5x8  Font
#define CMD_FUNCTION_SET_OPTION2              0x24 // * 4비트,   화면1행,    5x11 Font
#define CMD_FUNCTION_SET_OPTION3              0x28 // * 4비트,   화면2행,    5x8  Font
#define CMD_FUNCTION_SET_OPTION4              0x2C //   4비트,   화면2행,    5x11 Font
#define CMD_FUNCTION_SET_OPTION5              0x30 //   8비트,   화면1행,    5x8  Font
#define CMD_FUNCTION_SET_OPTION6              0x34 // * 8비트,   화면1행,    5x11 Font
#define CMD_FUNCTION_SET_OPTION7              0x38 // * 8비트,   화면2행,    5x8  Font
#define CMD_FUNCTION_SET_OPTION8              0x3C //   8비트,   화면2행,    5x11 Font







void clcd_Init(void);

void clcd_Command(uint8_t cmd);
void clcd_Data(uint8_t data);
void clcd_Str(char *string);
void clcd_Position(uint8_t col, uint8_t row);
void clcd_Clear(void);

#endif /* _USE_HW_CLCD */

#endif /* SRC_COMMON_HW_INCLUDE_CLCD_H_ */
