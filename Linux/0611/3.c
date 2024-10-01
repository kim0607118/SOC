#include<wiringPi.h>
#include<stdio.h>
#include<stdlib.h>

#define	RED	8
#define YELLOW	7
#define	sw	2
#define	sw2	4

int mode = 0;
int intv = 2;
int tim;
int ps[40];


void Toggle(int pin){
	ps[pin]=!ps[pin];
	digitalWrite(pin,ps[pin]);
}

void gpioisr()
{
	if(++intv>9)	intv=1;
	printf("gpio intterupt occured\n");
}

void stop()
{
	digitalWrite(RED, LOW);
	digitalWrite(YELLOW, LOW);
	exit(0);
}
int main(){
	wiringPiSetup();
	pinMode(RED, OUTPUT);
	pinMode(YELLOW, OUTPUT);
	pinMode(sw, INPUT);
	pinMode(sw2, INPUT);

	wiringPiISR(sw, INT_EDGE_FALLING, gpioisr);
	wiringPiISR(sw2, INT_EDGE_FALLING, stop);

	while(1){
		tim = (9-intv)*100;
		if(mode)
		{
			Toggle(RED);
			Toggle(YELLOW);
			delay(tim);
		}
		else
		{
			Toggle(RED);
			Toggle(YELLOW);
			delay(tim);
		}
	}
	return 0;
}
