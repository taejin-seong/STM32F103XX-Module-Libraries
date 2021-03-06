/*
 * gpio.c
 *
 *  Created on: 2022. 2. 23.
 *      Author: sungt
 */


#include "gpio.h"






typedef struct
{
  GPIO_TypeDef  *port;
  uint16_t       pin;
  uint8_t        mode;
  GPIO_PinState  on_state;
  GPIO_PinState  off_state;
  bool           init_vlaue;

}gpio_tbl_t;




gpio_tbl_t gpio_tbl[GPIO_MAX_CH] =
{
         /* GPIO을 사용할 Port와 Pin을 입력하세요.*/
    {GPIOB, GPIO_PIN_9, _DEF_OUTPUT, GPIO_PIN_RESET, GPIO_PIN_SET, _DEF_HIGH},
};




bool gpioInit(void)
{
  bool ret = true;

 // __HAL_RCC_GPIOB_CLK_ENABLE();

  for (int i = 0; i < GPIO_MAX_CH; i++)
  {
    gpioPinMode(i, gpio_tbl[i].mode);
    gpioPinWrite(i, gpio_tbl[i].init_vlaue);
  }

  return ret;

}


bool gpioPinMode(uint8_t ch, uint8_t mode)
{
  bool ret = true;
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  switch(mode)
  {
      case _DEF_INPUT:
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        break;

      case _DEF_INPUT_PULLUP:
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        break;

      case _DEF_INPUT_PULLDOWN:
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        break;

      case _DEF_OUTPUT:
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Push-Pull, Open Drain 필요 시 OD로 변경
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // 필요 시  Medium, High로 변경
        break;

      case _DEF_OUTPUT_PULLUP:
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        break;

      case _DEF_OUTPUT_PULLDOWN:
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        break;
  }

  GPIO_InitStruct.Pin = gpio_tbl[ch].pin;
  HAL_GPIO_Init(gpio_tbl[ch].port, &GPIO_InitStruct);

  return ret;
}


void gpioPinWrite(uint8_t ch, bool value)
{
  if (ch > GPIO_MAX_CH)
  {
    return ;
  }

  if (value == true)
  {
    HAL_GPIO_WritePin(gpio_tbl[ch].port, gpio_tbl[ch].pin, gpio_tbl[ch].on_state);
  }

  else
  {
    HAL_GPIO_WritePin(gpio_tbl[ch].port, gpio_tbl[ch].pin, gpio_tbl[ch].off_state);
  }

}


bool gpioPinRead(uint8_t ch)
{
  bool ret = false;

  if (ch >= GPIO_MAX_CH)
  {
    return false;
  }

  if (HAL_GPIO_ReadPin(gpio_tbl[ch].port, gpio_tbl[ch].pin) == gpio_tbl[ch].on_state)
  {
    ret = true;
  }

  return ret;

}


void gpioPinToogle(uint8_t ch)
{
  if (ch >= GPIO_MAX_CH)
  {
    return ;
  }

  HAL_GPIO_TogglePin(gpio_tbl[ch].port, gpio_tbl[ch].pin);
}
