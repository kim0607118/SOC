#include "ap.h"
#include "led.h"

void apInit()
{

}

void apMain()
{
  while (1)
    {
      HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
      for(uint8_t i = 0; i<8; i++){
          ledOn(i);
          delay(100);
      }
      for(uint8_t i = 0; i<8; i++)
        {
          ledOff(i);
          delay(100);
        }
    }
}
