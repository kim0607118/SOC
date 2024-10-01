
#define button_h_
#ifdef button_h_
//#define F_CPU 16000000ul
#include <avr/io.h>
#include <util/delay.h>

#define	LED_DDR			DDRC
#define LED_PORT		PORTC
#define Button_DDR		DDRD
#define Button_PIN		PIND
#define Button_ON		0
#define Button_OFF		1
#define Button_Toggle	2

enum {PUSHED,RELEASED};
enum {NO_ACT, ACT_PUSHED, ACT_RELEASE};

typedef struct _button{
	volatile uint8_t	*ddr;
	volatile uint8_t	*pin;
	uint8_t				btnPin;
	uint8_t				prevState;
}Button;

void Button_Init(Button *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNumber);
uint8_t Button_getState(Button *button);

#endif