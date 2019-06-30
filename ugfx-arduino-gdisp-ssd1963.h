#ifndef UGFX_ARDUINO_SSD1963_H
#define UGFX_ARDUINO_SSD1963_H

#include <stdint.h>

typedef struct {
  const uint8_t reset;
  const uint8_t cs;
  const uint8_t rs;
  const uint8_t wr;
  const uint8_t rd;
} ssd1963_pins_t;

extern const ssd1963_pins_t ssd1963_pins;

#endif // UGFX_ARDUINO_SSD1963_H
