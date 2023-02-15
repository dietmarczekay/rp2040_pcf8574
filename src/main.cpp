#include <Arduino.h>
#include <bits/stdc++.h>
//#include <hardware/gpio.h>
//#include "hardware/pio.h"
#include <strings.h>

#include <I2CKeyPad.h>

#include "SD.h"

#include "globals.h"
#include "lv_helper.h"
#include "my_i2c.h"

bool toggle = false;
bool toggle2 = false;
uint32_t atime = 0;
uint16_t debounce = 600;

const uint8_t KEYPAD_ADDRESS = 0x20;

I2CKeyPad keyPad(KEYPAD_ADDRESS);

uint32_t start, stop;
uint32_t lastKeyPressed = 0;

void handleTouchInterrupt()
{  
    Serial.println("Interrupt2 ");
}

void callInterrupt2()
{
  digitalWrite(25, toggle2 ? LOW : HIGH);
  toggle2 = !toggle2;
  if ( (millis() - debounce) > atime){
//    handleTouchInterrupt();
    isTouched = true;
    atime = millis();
  }
  delay(50);
}

void setup()
{
  Serial.begin(115200);
  delay(4000);

  gpio_init(PICO_DEFAULT_LED_PIN);
  gpio_set_drive_strength(PICO_DEFAULT_LED_PIN, GPIO_DRIVE_STRENGTH_8MA);
  gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
  
  gpio_init(15);
  gpio_set_drive_strength(15, GPIO_DRIVE_STRENGTH_8MA);
  gpio_set_dir(15, GPIO_OUT);
  gpio_put(15, false);
  Serial.println("Test 22");

  SPI1.setCS(SPI_CS);
  SPI1.setRX(SPI_RX);
  SPI1.setTX(SPI_TX);
  SPI1.setSCK(SPI_CLK);

  SD.begin( SPI_CS, SPI1);

  File myFile = SD.open("test.txt", FILE_READ|FILE_WRITE);
  if (myFile) {
    Serial.println("Test");

    while (myFile.available()) {
      Serial.print(myFile.read());
      Serial.println("second test");
    }

    myFile.close();
  } else {
    Serial.println("test failed");
  }

  setupI2C();

}

void loop()
{
  //lv_timer_handler();
  gpio_put(15, toggle);
  toggle = !toggle;
  delay(50);
  

  //uint8_t index = keyPad.getKey();

  //Serial.print("\t");
  //Serial.print(index);
}
