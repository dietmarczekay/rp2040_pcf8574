this is my playground fro the Raspberry Pico rp2040

it uses to following hardware

MSH-4.0inch Display B

4x4 keypad

The goal is
- use different pins for I2C0

This is done wir Earle Philhowers tools

access I2C with WIRE object on pin GPIO0 (SDA) and GPIO1 (SCL)

first declare usage of pins

```
  i2c_init(i2c_default, 100 * 1000);
  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA);
  gpio_pull_up(I2C_SCL);
```

then change setup for Wire object and initialize

```
  Wire.setSDA(0);
  Wire.setSCL(1);

  Wire.begin();
```

for using with LEDs for blink, remember the PCF8574 pins are open collector! Writing a "1" means turning LED off.
