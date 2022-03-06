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
	MX_SPI1_Init();
	gpioInit();
	NRF24L01_Init();
	dfplayer_Init();
	ledInit();

}
