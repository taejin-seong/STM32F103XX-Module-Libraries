/*
 * ap.h
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */
/* 실질적으로  Main 함수를 담당하는 부분입니다.*/

#ifndef SRC_AP_AP_H_
#define SRC_AP_AP_H_


#include "hw.h"




void apInit(void);
void apBoardTest(void);
void apUartTest(void);
void apGpioTest(void);
void apDotMatrixTest(void);
void apCLCDTest(void);
void apNRF24L01RxTest(void);
void apNRF24L01TxTest(void);
void apDFPlayerTest(void);







#endif /* SRC_AP_AP_H_ */
