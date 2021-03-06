/*
 * hw.c
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */


#include "hw.h"


void hwInit(void)
{
	bspInit();

/*  TODO: HW 설정 - "하드웨어 초기화" (3) */

	uartInit();
	MX_I2C1_Init();
	MX_SPI1_Init();
	MX_SPI2_Init();
	gpioInit();
	MAX7219_MatrixInit();
//	clcd_Init();
	NRF24L01_Init();
	dfplayer_Init();
	ledInit();

}
