#include <stdio.h>
#include <wiringPi.h>

#define wpi_pin 2

int psc = 19;
int RANGE = 100;

int range[12];
int pitch[] = { 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494 };

int song[] = { 0, 2, 4, 2, 4, 4, 4, 2, 2, 2, 4, 4, 4, -1 };
int rhythms[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };


void calcRange() {
	for (int i = 0; i < 12; ++i) {
		range[i] = 19200000 / (psc * pitch[i]);
		printf("Pitch %d: Range = %d\n", pitch[i], range[i]);
	}
}

void playsound(int um, int rhythm) {
	pwmSetClock(psc);
	pwmSetRange(range[um]);
	pwmWrite(wpi_pin, range[um] / 2);
	delay(rhythm * 250);

	pwmWrite(wpi_pin, 0); // Stop the sound after the note duration
	delay(50); // Delay between notes
}

int main() {
	if (wiringPiSetup() == -1) {
		printf("Error: wiringPi setup failed.\n");
		return 1;
	}
	pinMode(wpi_pin, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	calcRange();
	for (int i = 0; song[i] != -1; ++i) {
		printf("Playing note %d\n", song[i]);
		playsound(song[i], rhythms[i]);
	}
	return 0;
}