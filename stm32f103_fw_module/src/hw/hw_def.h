/*
 * hw_def.h
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */

/*hw 폴더 밑에 만들어지는 모듈들이 공통으로 쓰는 하드웨어 관련 정의를 선언합니다.*/

#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_


#include "def.h"
#include "bsp.h"


/* TODO: HW 설정 - "컴파일 유무 선언" (2) */



/*          Peripheral         Parameter     */
#define   _USE_HW_UART
#define        HW_UART_MAX_CH     2

#define	  _USE_HW_SPI
#define   _USE_HW_I2C


/*           Hardware          Parameter      */
#define   _USE_HW_LED
#define        HW_LED_MAX_CH      1

#define   _USE_HW_GPIO
#define        HW_GPIO_MAX_CH     1

#define	  _USE_HW_CLCD

#define   _USE_HW_NRF24L01

#define   _USE_HW_DFPLAYER




#endif /* SRC_HW_HW_DEF_H_ */
