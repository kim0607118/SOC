#include<stdio.h>
#include<wiringPi.h>
#include<wiringPiI2C.h>

int main(){
	int fd = wiringPiI2CSetup(0x48);
	wiringPiI2CWrite(fd, 3);
	while(1){
		int val = wiringPiI2CRead(fd);
		float f = val/255*5;
		printf("VR input level = %d\n (%4.1V)\n", val, f);
		delay(500);
	}
}
