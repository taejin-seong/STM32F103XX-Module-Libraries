/*
 * max7219_8x8_led.h
 *
 *  Created on: 2022. 3. 23.
 *      Author: sungt
 *
 *
 * @reference
 *
 * https://github.com/eziya/STM32_HAL_MAX7219_8x8_MATRIX
 *
 */

#ifndef SRC_COMMON_HW_INCLUDE_CLCD_H_
#define SRC_COMMON_HW_INCLUDE_CLCD_H_

#include "hw_def.h"


#ifdef _USE_HW_DOT_MATRIX



#define CHR(x)	Atoz[(x)- 65]


#define DOT_MATRIX_SPI									hspi2
#define DOT_MATRIX_SPI_CS_PORT                          GPIOA
#define DOT_MATRIX_SPI_CS_PIN                           GPIO_PIN_8


extern const uint64_t matrix_column[];
extern const uint64_t symbol[];
extern const uint64_t numbers[];
extern const uint64_t Atoz[];




void MAX7219_MatrixInit(void);

void MAX7219_MatrixClear(uint8_t index);
void MAX7219_MatrixSetRow(uint8_t index,  uint8_t rows[8]);
void MAX7219_MatrixSetRow64(uint8_t index,  uint64_t rows);
void MAX7219_MatrixSetPixel(uint8_t index, uint8_t row, uint8_t col);
void MAX7219_MatrixLShift(uint8_t step);
void MAX7219_MatrixRShift(uint8_t step);
bool MAX7219_MatrixUpdate();

#endif /* _USE_HW_DOT_MATRIX */

#endif /* SRC_COMMON_HW_INCLUDE_CLCD_H_ */
