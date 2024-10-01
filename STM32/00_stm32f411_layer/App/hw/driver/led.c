#include "led.h"

typedef struct
{
  GPIO_TypeDef  *port;
  uint16_t      pinNumber;
  GPIO_PinState onState;
  GPIO_PinState offState;
}LED_TBL;

LED_TBL led_tbl[8]=
    {
        {GPIOB, bar0_Pin, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOB, bar1_Pin, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOB, bar2_Pin, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOA, bar3_Pin, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOC, bar4_Pin, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOB, bar5_Pin, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOA, bar6_Pin, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOA, bar7_Pin, GPIO_PIN_SET, GPIO_PIN_RESET}
    };

void ledInit(void)
{

}

void ledOn(uint8_t ch)
{
  HAL_GPIO_WritePin(led_tbl[ch].port, led_tbl[ch].pinNumber, led_tbl[ch].onState);
}

void ledOff(uint8_t ch)
{
  HAL_GPIO_WritePin(led_tbl[ch].port, led_tbl[ch].pinNumber, led_tbl[ch].offState);
}

void ledToggle(uint8_t ch)
{
  HAL_GPIO_TogglePin(led_tbl[ch].port, led_tbl[ch].pinNumber);
}
