#include "LCD.h"

int main(void){
	LCD_Init();
	
	LCD_GotoXY(0,0);
	LCD_WriteString("");
	LCD_GotoXY(1,0);
	LCD_WriteString("4Bit ATmega128A");
	
	while(1){
		
	}
}