/*
 * uart.c
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */


/*******************************************
 *                                         *
 *   UART ->  [RX : DMA,  TX : DMA ]       *
 *                                         *
 *******************************************/


#include "uart.h"
#include "qbuffer.h"



#define UART_MAX_BUF_SIZE       256

static bool       is_open[UART_MAX_CH];
static qbuffer_t  qbuffer[UART_MAX_CH];

static uint8_t    rx_buf[UART_MAX_BUF_SIZE];
static uint8_t    tx_buf[UART_MAX_BUF_SIZE];

/* UART 관련 HandleTypeDef 선언   */
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;




bool uartInit(void)
{
  for (int i = 0; i < UART_MAX_CH; i++)
  {
    is_open[i] = false;
  }

  return true;
}


bool uartOpen(uint8_t ch, uint32_t baud)
{
  bool ret = false;

  switch(ch)
  {
    /* UART1 */
    case _DEF_UART1:
      huart1.Instance             = USART1;
      huart1.Init.BaudRate        = baud;
      huart1.Init.WordLength      = UART_WORDLENGTH_8B;
      huart1.Init.StopBits        = UART_STOPBITS_1;
      huart1.Init.Parity          = UART_PARITY_NONE;
      huart1.Init.Mode            = UART_MODE_TX_RX;
      huart1.Init.HwFlowCtl       = UART_HWCONTROL_NONE;
      huart1.Init.OverSampling    = UART_OVERSAMPLING_16;

      HAL_UART_DeInit(&huart1);

      qbufferCreate(&qbuffer[ch], &rx_buf[0], 256);

      __HAL_RCC_DMA1_CLK_ENABLE();

      HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0); // RX DMA
      HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);


      if (HAL_UART_Init(&huart1) != HAL_OK)
      {
        ret = false;
      }
      else
      {
        ret = true;
        is_open[ch] = true;


        if (HAL_UART_Receive_DMA(&huart1, (uint8_t *)&rx_buf[0], 256) != HAL_OK)
        {
          ret = false;
        }

        qbuffer[ch].in  = qbuffer[ch].len - hdma_usart1_rx.Instance->CNDTR;
        qbuffer[ch].out = qbuffer[ch].in;

        HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0); // TX DMA
        HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
      }

      break;


    /* UART2 */
    case _DEF_UART2:
    	  huart2.Instance = USART2;
    	  huart2.Init.BaudRate = baud;
    	  huart2.Init.WordLength = UART_WORDLENGTH_8B;
    	  huart2.Init.StopBits = UART_STOPBITS_1;
    	  huart2.Init.Parity = UART_PARITY_NONE;
    	  huart2.Init.Mode = UART_MODE_TX_RX;
    	  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    	  huart2.Init.OverSampling = UART_OVERSAMPLING_16;

          HAL_UART_DeInit(&huart2);

          qbufferCreate(&qbuffer[ch], &rx_buf[0], 256);

          __HAL_RCC_DMA1_CLK_ENABLE();

          HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);  // RX DMA
          HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);


          if (HAL_UART_Init(&huart2) != HAL_OK)
          {
            ret = false;
          }
          else
          {
            ret = true;
            is_open[ch] = true;


            if (HAL_UART_Receive_DMA(&huart2, (uint8_t *)&rx_buf[0], 256) != HAL_OK)
            {
              ret = false;
            }

            qbuffer[ch].in  = qbuffer[ch].len - hdma_usart2_rx.Instance->CNDTR;
            qbuffer[ch].out = qbuffer[ch].in;

            HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);  // TX DMA
            HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
          }

          break;
  }

  return ret;

}



uint32_t uartAvailable(uint8_t ch)
{
  uint32_t ret = 0;

  switch(ch)
  {
    /* UART1 */
    case _DEF_UART1:
      qbuffer[ch].in = (qbuffer[ch].len - hdma_usart1_rx.Instance->CNDTR);
      ret = qbufferAvailable(&qbuffer[ch]);
      break;


    /* UART2 */
    case _DEF_UART2:
        qbuffer[ch].in = (qbuffer[ch].len - hdma_usart2_rx.Instance->CNDTR);
        ret = qbufferAvailable(&qbuffer[ch]);
        break;

  }

  return ret;
}



uint8_t uartRead(uint8_t ch)
{
  uint8_t ret;

  switch(ch)
  {
    /* UART1 */
    case _DEF_UART1:
      qbufferRead(&qbuffer[_DEF_UART1], &ret, 1);
      break;


    /* UART2 */
    case _DEF_UART2:
        qbufferRead(&qbuffer[_DEF_UART2], &ret, 1);
        break;

  }

  return ret;

}



uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length)
{
  uint32_t ret = 0;
  uint32_t pre_time;

  switch(ch)
  {
  	/* UART1 */
    case _DEF_UART1:
        pre_time = millis();
        while(millis() - pre_time < 100)
        {
          if (huart1.gState == HAL_UART_STATE_READY)
          {

            for (int i = 0; i < length; i++)
            {
              tx_buf[i] = p_data[i];
            }

            if(HAL_UART_Transmit_DMA(&huart1, &tx_buf[0], length) == HAL_OK)
            {
              ret = length;
            }

            break;
          }
        }
      break;


    /* UART2 */
    case _DEF_UART2:
        pre_time = millis();
        while(millis() - pre_time < 100)
        {
          if (huart2.gState == HAL_UART_STATE_READY)
          {

            for (int i = 0; i < length; i++)
            {
              tx_buf[i] = p_data[i];
            }

            if(HAL_UART_Transmit_DMA(&huart2, &tx_buf[0], length) == HAL_OK)
            {
              ret = length;
            }

            break;
          }
        }
      break;

  }
  return ret;
}



uint32_t uartPrintf(uint8_t ch, char *fmt, ...)
{
  char buf[256];
  va_list args;
  int len;
  uint32_t ret;

  va_start(args, fmt);
  len = vsnprintf(buf, 256, fmt, args);

  ret = uartWrite(ch, (uint8_t *)buf, len);

  va_end(args);

  return ret;
}



uint32_t uartGetBaud(uint8_t ch)
{
  uint32_t ret = 0;

  switch(ch)
  {
    /* UART1 */
    case _DEF_UART1:
      ret = huart1.Init.BaudRate;
      break;

    /* UART2 */
    case _DEF_UART2:
        ret = huart2.Init.BaudRate;
        break;

  }

  return ret;
}



void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{

}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

}



void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  return;
}



void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

 //   __HAL_RCC_GPIOA_CLK_ENABLE();				/* bsp.c에서 초기화 시킴 */
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA1_Channel5;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_CIRCULAR;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1_TX Init */
    hdma_usart1_tx.Instance = DMA1_Channel4;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart1_tx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 DMA Init */
    /* USART2_RX Init */
    hdma_usart2_rx.Instance = DMA1_Channel6;
    hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_rx.Init.Mode = DMA_CIRCULAR;
    hdma_usart2_rx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart2_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart2_rx);

    /* USART2_TX Init */
    hdma_usart2_tx.Instance = DMA1_Channel7;
    hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_tx.Init.Mode = DMA_NORMAL;
    hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart2_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart2_tx);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}


void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
}
