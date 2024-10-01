#include<wiringPi.h>
#include<stdio.h>

int main(){
	wiringPiSetup();
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(2, INPUT);

	for (int i = 0; i<5; i++){
		digitalWrite(7, HIGH);
		digitalWrite(8, HIGH);
		digitalWrite(9, HIGH);
		delay(i*1000);
		digitalWrite(7, LOW);
		digitalWrite(8, LOW);
		digitalWrite(9, LOW);
		delay(i*1000);
	}
}
