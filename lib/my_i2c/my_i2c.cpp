 
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <SerialUSB.h>
#include "PCF8574.h"

#include "../../include/globals.h"
#include "my_i2c.h"

#define address 0x21

PCF8574 pcf_0(0x21);
 
// I2C reserves some addresses for special purposes. We exclude these from the scan.
// These are any addresses of the form 000 0xxx or 111 1xxx
bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

void setupI2C()
{

  i2c_init(i2c_default, 100 * 1000);
  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA);
  gpio_pull_up(I2C_SCL);

  Wire.setSDA(0);
  Wire.setSCL(1);

  // This example will use I2C0 on the default SDA and SCL pins (GP4, GP5 on a Pico)
/* 
  i2c_init(i2c_default, 100 * 1000);
  gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
  gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
  */
  Serial.println("I2C initialisiert");

  /*
  ret = i2c_read_blocking(i2c_default, addr, &rxdata, 1, false);

  Serial.printf(ret < 0 ? "." : "@");
  Serial.printf(addr % 16 == 15 ? "\n" : "  ");
  */
  Serial.println("Scanning...");
  for (int addr = 0; addr < (1 << 7); ++addr) {
    if (addr % 16 == 0) {
        Serial.printf("%02x ", addr);
    }

    // Perform a 1-byte dummy read from the probe address. If a slave
    // acknowledges this address, the function returns the number of bytes
    // transferred. If the address byte is ignored, the function returns
    // -1.

    // Skip over any reserved addresses.
    int ret;
    uint8_t rxdata;
    if (reserved_addr(addr))
        ret = PICO_ERROR_GENERIC;
    else
        ret = i2c_read_blocking(i2c0, addr, &rxdata, 1, false);
        //ret = i2c_read_blocking(i2c_default, addr, &rxdata, 1, false);

    Serial.printf(ret < 0 ? "." : "@");
    Serial.printf(addr % 16 == 15 ? "\n" : "  ");
  }
  Serial.printf("Done 2.\n");
/* 
  i2c_write_blocking(i2c0, 0x21, &rxdata, 8, true);

	pcf_0.digitalWrite(P1, 8);
  delay(1000);
	pcf_0.digitalWrite(P1, 0);
  delay(1000);
	pcf_0.digitalWrite(P1, 8);
  delay(1000);
	pcf_0.digitalWrite(P1, 0);
  delay(1000);
 */
    delay(100);

  Serial.println("Write byte(0) test");

  Wire.begin();

  for(int i = 0; i<10;i++){
    Wire.beginTransmission(address);
    Wire.write(byte(0));
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.println("OK");
    } else {
      Serial.println("Fail");
    }
    delay(200);

    Serial.println("Write 1 test");
    Wire.beginTransmission(address);
    Wire.write(3);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.println("OK");
    } else {
      Serial.println("Fail");
    }
    delay(200);
  }
    Wire.beginTransmission(address);
    Wire.write(byte(0));
    Wire.endTransmission();

  Serial.printf("Done 3.\n");

  return;
}
