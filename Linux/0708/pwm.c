#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define wpi_pin 22

int main(int n, char* s[]) {

	if (n < 2) {
		printf("usage: pwm2 [duty rate(%%)] [[period]] \n\n");
		printf("       period = 10ms if empty\n\n");
		printf("default value : period = 10ms, DR = 50%%\n\n");
	}
	int dr = 50, drh, period = 10;
	if (n > 1) sscanf(s[1], "%d", &dr);
	if (n > 2) sscanf(s[2], "%d", &period);
	drh = (dr * period) / 100;

	wiringPiSetup();
	pinMode(wpi_pin, OUTPUT);

	pwmSetMode(PWM_MODE_MS);
	softPwmCreate(wpi_pin, drh, period);

	delay(5000);
	softPwmStop(wpi_pin);
	return 0;
}