#include<wiringPi.h>
#include<stdio.h>

int main(){
	wiringPiSetup();
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(2, INPUT);

	for(int i = 0; i < 5; i++){
		digitalWrite(8, HIGH);
		digitalWrite(9, HIGH);
		digitalWrite(7, HIGH);
		delay(1000);
	}

	if(digitalRead(2) == 0){
		digitalWrite(8, 

}

