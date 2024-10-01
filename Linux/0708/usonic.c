#include <stdio.h>
#include <wiringPi.h>

#define trig 8
#define echo 9

int main(int argc, char** argv) {
	wiringPiSetup();
	pinMode(trig, OUTPUT);
	pinMode(echo, INPUT);

	for (;;) {
		digitalWrite(trig, 1);
		delayMicroseconds(10);
		digitalWrite(trig, 0);
		delayMicroseconds(200);


		while (digitalRead(echo) != 1); //»ó½Â ¿§Áö °ËÃâ
		int t1 = micros();
		while (digitalRead(echo) != 0); //ÇÏ°­ ¿§Áö °ËÃâ
		int t2 = micros();

		double dist = (t2 - t1) * 0.017;
		printf("distance : %f(cm)\n", dist);
	}
	return 0;
}