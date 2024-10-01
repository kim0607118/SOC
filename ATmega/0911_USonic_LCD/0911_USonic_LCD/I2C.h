#ifndef I2C_H_
#define I2C_H_

#include "DEF.h"

#define I2C_DDR		DDRD
#define I2C_SCL		PORTD0
#define I2C_SDA		PORTD1

void I2C_Init() {
    I2C_DDR |= (1<<I2C_SDA | 1<<I2C_SCL);
    TWBR = 72;
}

void I2C_start() {
    TWCR = (1<<TWINT | 1<<TWSTA | 1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
}

void I2C_Stop() {
    TWCR = (1<<TWINT | 1<<TWEN | 1<<TWSTO);
}

void I2C_TxData(uint8_t data) {
    TWDR = data;
    TWCR = (1<<TWINT | 1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
}

void I2C_TxByte(uint8_t devAddress, uint8_t data) {
    I2C_start();
    I2C_TxData(devAddress);
    I2C_TxData(data);
    I2C_Stop();
}

#endif