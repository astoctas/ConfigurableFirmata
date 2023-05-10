#ifndef Matrix8x8Firmata_h
#define Matrix8x8Firmata_h

// #include <Wire.h>
#include "utility/FirmataInterfaces.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <ConfigurableFirmata.h>
#include "FirmataFeature.h"

#define MATRIX_8x8_DATA  0x04 // control a matrix display
#define MATRIX_8x8_ADDRESS 0x70
#define MATRIX_8x8_PRINT 0x00
#define MATRIX_8x8_WRITE 0x01
#define MATRIX_8x8_CLEAR 0x02


class Matrix8x8Firmata : public FirmataFeature
{
  public:
    boolean handlePinMode(byte pin, int mode);
    void handleCapability(byte pin);
    boolean handleSysex(byte command, byte argc, byte *argv);
    void reset();
    Adafruit_8x8matrix matrix_8x8 = Adafruit_8x8matrix();

    void init();
  private:
    uint8_t lcdBuffer[8];
};

#endif
