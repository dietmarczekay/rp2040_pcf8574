#ifndef GLOBALS_H
#define GLOBALS_H

#include <pico/stdlib.h>
// Array to represent keys on keypad
const char hexaKeys[16] = {
'*', '0', '#', 'D', '7', '8', '9', 'C', '4', '5', '6', 'B', '1', '2', '3', 'A'
};

#define EEPROM_ADDR 0

#define SPI_CS 13
#define SPI_TX 11
#define SPI_RX 12
#define SPI_CLK 14

#define I2C_SDA 0
#define I2C_SCL 1
#endif