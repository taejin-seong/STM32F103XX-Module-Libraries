/*
 * ap.c
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */

#ifndef SRC_AP_AP_C_
#define SRC_AP_AP_C_


#include "ap.h"





void apInit(void)
{
   uartOpen(_DEF_UART1, 9600); /* DFplayer와 통신하기 위한 UART 설정, Default : 9600/8/n/1/n */
   uartOpen(_DEF_UART2, 115200);
}



/* Black Pill 보드 내부 LED 테스트 */
void apBoardTest(void)
{
  uint32_t pre_time = millis();

  while(1)
  {
    if (millis() - pre_time >= 100)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }
  }

}



/* UART 테스트  */
void apUartTest(void)
{
  uartPrintf(_DEF_UART1, "UART BaudRate : %d\n", uartGetBaud(_DEF_UART1));

  while(1)
  {
    if (uartAvailable(_DEF_UART1) > 0)
    {

      uartPrintf(_DEF_UART1, "Rx Data : %c , 0x%X\n", uartRead(_DEF_UART1));
    }
  }

}



/* PINB 9에 외부 LED 부품 연결 후 GPIO 테스트 */
void apGpioTest(void)
{
  gpioPinMode(_DEF_GPIO1, _DEF_OUTPUT);

  while(1)
  {
    gpioPinToogle(_DEF_GPIO1);
    delay_ms(100);
  }

}


/* DFplayer 모듈  테스트 */
void apDFPlayerTest(void)
{

	char rx_data;

	dfplayer_SetSource(PLAYBACK_SOURCE_TF); /* 저장장치 SD카드로 설정 */
	dfplayer_SetVolume(10); /* 초기 볼륨 10으로 설정 */
	dfplayer_SetEQ(EQ_CLASSIC); /* EQ를 클래식으로 설정 */

	while(1)
	{
		if (uartAvailable(_DEF_UART2) > 0)
		{
			rx_data = uartRead(_DEF_UART2);
			uartPrintf(_DEF_UART2, "%c\n", rx_data);

			switch (rx_data)
			{
				case 'S':
					dfplayer_Play(); /* 음악 재생  */
					uartPrintf(_DEF_UART2, "Playing...\r\n");
					break;

				case 'D':
					dfplayer_Next(); /* 다음곡 재생  */
					uartPrintf(_DEF_UART2, "Playing Next Song...\r\n");
					break;

				case 'A':
					dfplayer_Previous(); /* 이전곡 재생  */
					uartPrintf(_DEF_UART2, "Playing Previous Song...\r\n");
					break;

				case 'Q':
					dfplayer_Pause(); /* 일시정지  */
					uartPrintf(_DEF_UART2, "Pause\r\n");
					break;

				case 'W':
					dfplayer_IncreaseVolume(); /* 볼륨 증가  */
					uartPrintf(_DEF_UART2, "Volume Up\r\n");
					break;

				case 'X':
					dfplayer_DecreaseVolume(); /* 볼륨 감소 */
					uartPrintf(_DEF_UART2, "Volume Down\n");
					break;

				case 'V':
					dfplayer_Stop(); /* 정지 */
					uartPrintf(_DEF_UART2, "Stop\n");
					break;

				case 'E':
					dfplayer_InsertAdvertisement(1); /* ADVERT폴더에 있는 음악 인터럽트 실행  */
					uartPrintf(_DEF_UART2, "Ad Start\n");
					break;

				case 'T':
					dfplayer_StopAdvertisement(); /* ADVERT 폴더에 있는 음악 인터럽트 정지 후 원래 실행하던 곡으로 복귀  */
					uartPrintf(_DEF_UART2, "AD Stop & Go Back\n");
					break;

				default:
					break;
			}
		}

	}

}





#endif /* SRC_AP_AP_C_ */
