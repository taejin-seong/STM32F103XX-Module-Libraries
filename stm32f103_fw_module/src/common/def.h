/*
 * def.h
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */

/* 공통으로 포함시켜야할 헤더파일을 작성합니다.*/


#ifndef SRC_COMMON_DEF_H_
#define SRC_COMMON_DEF_H_





/* TODO: HW 설정 - "공용헤더 추가 및 채널 설정" (4) */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>


/*                            CH NUM
 -------------------------------------------*/


/*       LED         */
#define _DEF_LED1	            0

/*       UART         */
#define _DEF_UART1	          	0
#define _DEF_UART2				1

/*       GPIO         */
#define _DEF_GPIO1				0

#define _DEF_INPUT              0
#define _DEF_INPUT_PULLUP       1
#define _DEF_INPUT_PULLDOWN     2
#define _DEF_OUTPUT             3
#define _DEF_OUTPUT_PULLUP      4
#define _DEF_OUTPUT_PULLDOWN    5

#define _DEF_LOW                0
#define _DEF_HIGH               1








#endif /* SRC_COMMON_DEF_H_ */
