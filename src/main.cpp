#include <Arduino.h>
#include <Wire.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// I2C address
static const uint8_t I2C_ADDR = 0x21;

bool toggle = false;

uint8_t data0 = 0b00000000;
uint8_t data1 = 0b00000000;
uint8_t data2 = 0b11111111;

int ret;

  // Pins
  const uint SDA_PIN = 0;
  const uint SCL_PIN = 1;
  const uint EXT_LED_PIN = 15;

  // Ports
  //i2c_inst_t *i2c = i2c1;

  TwoWire *wire = &Wire;  //I2C0
  //TwoWire *wire = &Wire1; //I2C1


uint8_t rotation_l(uint8_t x) {
  if (x == 0)
    return 1;
  else
    return uint8_t(x << 1) | uint8_t(x >> 15);
}

void add1(uint8_t *x) {
  if (*x == 15)
    *x = 0;
  else
    ++*x;
  return;
}

static bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

void setup()
{

  // Initialize chosen serial port
  //stdio_init_all();
  
  Serial.begin(115200);
  delay(2000);  

  gpio_init(PICO_DEFAULT_LED_PIN);
  gpio_set_drive_strength(PICO_DEFAULT_LED_PIN, GPIO_DRIVE_STRENGTH_8MA);
  gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
  
  gpio_init(EXT_LED_PIN);
  gpio_set_drive_strength(EXT_LED_PIN, GPIO_DRIVE_STRENGTH_8MA);
  gpio_set_dir(EXT_LED_PIN, GPIO_OUT);
  gpio_put(EXT_LED_PIN, false);

  // Initialize I2C pins
  gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(SDA_PIN);
  gpio_pull_up(SCL_PIN);

  wire->setSDA(SDA_PIN);
  wire->setSCL(SCL_PIN);
  wire->begin();
  Serial.printf("Done\n");

  wire->beginTransmission(I2C_ADDR);
  wire->write(data2);
  ret = wire->endTransmission();

  Serial.println(ret);

  // Wait before taking measurements
  sleep_ms(1000);

}

void loop()
{
  delay(1000);
  Serial.printf("W: %u ", data0);
  wire->beginTransmission(I2C_ADDR);
  wire->write(data0);
  ret = wire->endTransmission();

  //i2c_write_blocking(i2c, I2C_ADDR, &data0, 1, false);
  //pcf.write8(data0);
  //pcf.selectNone();
  uint32_t data;
  //data = pcf.read8();
  //i2c_read_blocking(i2c, I2C_ADDR, &data, 1, false);
  wire->requestFrom(I2C_ADDR, 1);
  data = wire->read();

  Serial.printf_P("R: %u\n", data);
  add1(&data0);
  gpio_put(PICO_DEFAULT_LED_PIN, toggle);
  toggle = !toggle;
}
