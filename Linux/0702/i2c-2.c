#include<wiringPi.h>
#include<stdio.h>

#define pin 22

int main(int n, char *s[]){

	if(n<2){
		printf("usage : pwm [duty rate(%%)]\n\n");
		return 1;
	}

	int dr, drh, drl, period = 10;
	sscanf(s[1],"%d",&dr);
	drh=(dr*period)/100;
	drl=period-drh;

	wiringPiSetup();
	pinMode(pin, OUTPUT);

	for(int i=0; i<5; i++){
		digitalWrite(pin,1);
		delay(500);
		digitalWrite(pin,0);
		delay(500);
	}

	return 0;
}
