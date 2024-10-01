
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define	FND_DATA_DDR	DDRC
#define	FND_SELECT_DDR	DDRG
#define FND_DATA_PORT	PORTC
#define FND_SELECT_PORT	PORTG

void FND_Display(uint16_t data){
	static uint8_t position = 0;
	uint8_t fndData[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};
		
	switch(position)
	{
		case 0:
		FND_SELECT_PORT &= ~(1<<0);
		FND_SELECT_PORT |= (1<<1) | (1<<2) | (1<<3);	//digit 234 high
		FND_DATA_PORT = fndData[data/1000];
		break;
		
		case 1:
		FND_SELECT_PORT &= ~(1<<1);
		FND_SELECT_PORT |= (1<<0) | (1<<2) | (1<<3);	//digit 134 high
		FND_DATA_PORT = fndData[data/100%10];
		break;
		
		case 2:
		FND_SELECT_PORT &= ~(1<<2);
		FND_SELECT_PORT |= (1<<0) | (1<<1) | (1<<3);	//digit 234 high
		FND_DATA_PORT = fndData[data/10%10];
		break;
		
		case 3:
		FND_SELECT_PORT &= ~(1<<3);
		FND_SELECT_PORT |= (1<<0) | (1<<1) | (1<<2);	//digit 123 high
		FND_DATA_PORT = fndData[data/100%10];
		break;
	}
	position++;
	position=position%4;
}

int main(void)
{
	FND_DATA_DDR = 0xff;
	FND_SELECT_DDR = 0xff;
	FND_SELECT_PORT = 0x00;
	
	uint16_t count=0;
	uint32_t timeTick = 0;
	uint32_t prevTime = 0;
	
    while (1) 
    {
		FND_Display(count);
		if(timeTick-prevTime>100){
			prevTime=timeTick;
			count++;
		}
		_delay_ms(5);
		timeTick++;
    }
}


