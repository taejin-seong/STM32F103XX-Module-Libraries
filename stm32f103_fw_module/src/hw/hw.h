/*
 * hw.h
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */

#ifndef SRC_HW_HW_H_
#define SRC_HW_HW_H_




#include <max7219_dotmatrix.h>
#include "hw_def.h"


/* TODO: HW 설정 - "헤더파일 추가시키기" (1) */


#include "uart.h"
#include "i2c.h"
#include "spi.h"
#include "max7219.h"
#include "max7219_dotmatrix.h"
#include "clcd.h"
#include "nrf24l01.h"
#include "gpio.h"
#include "dfplayer.h"
#include "led.h"






void hwInit(void);






#endif /* SRC_HW_HW_H_ */
