/*
 * ap.c
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 *
 ******************************************************************************
 * @attention
 *
 * clcd.h와 max7219.h의  #define에서  0x00~0x0f 부분이 중복되어 오류가 발생합니다.
 * 따라서  clcd와 dot matrix는  동시에 테스트할 수 없습니다.
 * 양쪽(clcd & dot matrix)을 동시에 테스트하려면 max7219.h의 #define 0x00 ~0x0f 부분을 static const하게 선언하여 사용해야합니다.
 *
 *
 *
 * An error occurs due to overlapping parts 0x00~0x0f in #define of clcd.h and max7219.h.
 * Therefore, clcld and dot matrix cannot be tested at the same time.
 * To test both simultaneously (clcd & dot matrix), you must use the static const declaration of #define 0x00 to 0x0f (max7219.h).
 *
 *
 ******************************************************************************
 */

#ifndef SRC_AP_AP_C_
#define SRC_AP_AP_C_


#include "ap.h"





void apInit(void)
{
	uartOpen(_DEF_UART1, 9600); /* DFplayer와 통신하기 위한 UART 설정, Default : 9600/8/n/1/n */
	uartOpen(_DEF_UART2, 115200);

//	uartOpen(_DEF_UART1, 115200);
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



/* nRF24L01 모듈  Rx 테스트 */
void apNRF24L01RxTest(void)
{
	/* nRF24L01 수신 버퍼 (받을 데이터 버퍼) */
	uint8_t tmp_buf[256]; // 임시로 지정

	/* nRF24L01 수신 초기화   */
	while(NRF24L01_Check())
	{
		uartPrintf(_DEF_UART1,"NRF24L01 wireless module cannot be found by hardware\n");
		delay_ms(100);
	}

	uartPrintf(_DEF_UART1,"NRF24L01 wireless module hardware connection is normal\n");

	NRF24L01_RX_Mode();
	uartPrintf(_DEF_UART1, "Enter data receiving mode\n");



	/* nRF24L01 수신 시작 */
	while(1)
	{
		if(NRF24L01_RxPacket(tmp_buf)==0)
		{
			// tmp_buf[32]=0;//Add string terminator
			uartPrintf(_DEF_UART1,"NRF24L01 wireless module data received successfully: %s\n",tmp_buf);
		}

		else
		{
			uartPrintf(_DEF_UART1,"NRF24L01 wireless module data reception failed \n");
			delay_ms(100);
		}

		delay_ms(10);
	}
}



/* nRF24L01 모듈  Tx 테스트 */
void apNRF24L01TxTest(void)
{
	/* nRF24L01 송신 버퍼 (보낼 데이터 버퍼) */
	uint8_t tmp_buf[]="Hey, data is received!";

	/* nRF24L01 송신 초기화   */
	while(NRF24L01_Check())
	{
		uartPrintf(_DEF_UART1,"NRF24L01 wireless module cannot be found by hardware\n");
		delay_ms(100);
	}

	uartPrintf(_DEF_UART1,"NRF24L01 wireless module hardware connection is normal\n");

	NRF24L01_TX_Mode();
	uartPrintf(_DEF_UART1, "Enter data transmission mode\n");


	/* nRF24L01 송신 시작 */
	while(1)
	{
		if (NRF24L01_TxPacket(tmp_buf) == TX_OK)
		{
			uartPrintf(_DEF_UART1,"NRF24L01 wireless module data sent successfully: %s\n",tmp_buf);
		}

		else
		{
			uartPrintf(_DEF_UART1, "NRF24L01 wireless module data transmission failed\n");
		}

		delay_ms(10);

	}

}


/*
 *  @attention을 참고하세요.
 *  Please refer to @attention
 */

/* CLCD With I2C 4-bit 모드 테스트 */
void apCLCDTest(void)
{


//#define _OVERLAPS_MAX7219_DEFINE_
#ifdef  _OVERLAPS_MAX7219_DEFINE_

	char data1[] = "Hello, World !!";
	char data2[] = "(*^_^*) (/^^)/";
	char data3[] = "12345";
	char data4[] = "67890";
	char data5[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	char buffer[64];

	uint8_t freq1 = 45/10;
	float 	freq2 = 45./10;

	while (1)
	{
		/* Using Array */
		clcd_Position(0, 0);
		clcd_Str(data1);
		delay_ms(1000);

		clcd_Position(1, 0);
		clcd_Str(data2);
		delay_ms(1000);


		clcd_Clear();
		delay_ms(500);


		/* Using ASCII CODE */
		clcd_Position(0, 7);
		clcd_Data(0x4C);
		clcd_Data(0x6F);
		clcd_Data(0x76);
		clcd_Data(0x65);
		delay_ms(1000);

		/* One Data */
		clcd_Position(1, 3);
		clcd_Data('L');
		clcd_Data('O');
		clcd_Data('V');
		clcd_Data('E');
		delay_ms(1000);


		clcd_Clear();
		delay_ms(500);

		/* Using Command */
		clcd_Command(CMD_ENTRY_MODE_SET_OPTION1);
		clcd_Position(0, 7);
		clcd_Str(data3);
		delay_ms(500);

		clcd_Command(CMD_ENTRY_MODE_SET_OPTION3);
		clcd_Position(1, 7);
		clcd_Str(data4);
		delay_ms(500);


		clcd_Clear();
		delay_ms(500);

		clcd_Position(0, 0);
		clcd_Str(data3);
		clcd_Position(1, 0);
		clcd_Str(data4);

		for(int i = 0; i < 3; i++)
		{
			clcd_Command(CMD_DISPLAY_OPTION7);
			delay_ms(500);
			clcd_Command(CMD_DISPLAY_OPTION8);
			delay_ms(500);
		}


		clcd_Clear();
		delay_ms(500);


		clcd_Position(0, 0);
		clcd_Str(data5);
		delay_ms(500);

		for(int i = 0; i < 26; i++)
		{
			clcd_Command(CMD_CURSOR_DISPLAY_SHIFT_OPTION3);
			clcd_Command(CMD_CURSOR_DISPLAY_SHIFT_OPTION1);
			delay_ms(300);
		}

		delay_ms(1000);
		clcd_Position(0, 0);
		clcd_Str(data5);
		delay_ms(1000);
		for(int i = 0; i < 26; i++)
		{
			clcd_Command(CMD_CURSOR_DISPLAY_SHIFT_OPTION4);
			delay_ms(300);
		}

		delay_ms(1000);


		clcd_Clear();
		delay_ms(500);

		/* float value */
		sprintf(buffer, "gen: %3d kHz", freq1);
		clcd_Position(0, 0);
		clcd_Str(buffer);

		/* Check your MCU Settings from Project Properties > C/C++ Build > Settings > Tool Settings, or add manually "-u_printf_float" in linker flags.*/
		sprintf(buffer, "cnt: %3.3f kHz", freq2);
		clcd_Position(1, 0);
		clcd_Str(buffer);

		delay_ms(3000);


		clcd_Clear();
		delay_ms(500);

	}
#endif /*  _OVERLAPS_MAX7219_DEFINE_ */

}


/*
 *  @attention을 참고하세요.
 *  Please refer to @attention
 */

/* 8x8 Dot Matrix With SPI 모드 테스트 */
void apDotMatrixTest(void)
{

#define _OVERLAPS_CLCD_DEFINE_
#ifdef  _OVERLAPS_CLCD_DEFINE_

	MAX7219_MatrixUpdate();

	while (1)
	{
		MAX7219_MatrixSetRow64(0, CHR('S'));
		MAX7219_MatrixUpdate();
		delay_ms(300);

		MAX7219_MatrixSetRow64(0, CHR('T'));
		MAX7219_MatrixUpdate();
		delay_ms(300);

		MAX7219_MatrixSetRow64(0, CHR('A'));
		MAX7219_MatrixUpdate();
		delay_ms(300);

		MAX7219_MatrixSetRow64(0, CHR('R'));
		MAX7219_MatrixUpdate();
		delay_ms(300);

		MAX7219_MatrixSetRow64(0, CHR('T'));
		MAX7219_MatrixUpdate();
		delay_ms(300);

		for(int i = 0; i < 10; i ++)
		{
			MAX7219_MatrixSetRow64(0, numbers[i]);
			MAX7219_MatrixUpdate();
			delay_ms(100);
		}

		for (int i = 0; i < 8; i ++)
		{

				MAX7219_MatrixSetRow64(0, matrix_column[i] | 0xFF);
				MAX7219_MatrixUpdate();
				delay_ms(300);

				if (i > 0)
				{
					MAX7219_MatrixSetRow64(0, matrix_column[i] << i);
					MAX7219_MatrixUpdate();
					delay_ms(300);
				}

		}


	}
#endif /*  _OVERLAPS_CLCD_DEFINE_ */
}




#endif /* SRC_AP_AP_C_ */
