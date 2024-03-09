#ifndef TCS34725Firmata_h
#define TCS34725Firmata_h

// #include <Wire.h>
#include "utility/FirmataInterfaces.h"
#include "Adafruit_TCS34725.h"
#include <ConfigurableFirmata.h>
#include "FirmataFeature.h"

#define TCS34725_DATA  0x05 // control a color sensor


class TCS34725Firmata : public FirmataFeature
{
  public:
    boolean handlePinMode(byte pin, int mode);
    void handleCapability(byte pin);
    boolean handleSysex(byte command, byte argc, byte *argv);
    void reset();
    Adafruit_TCS34725 TCS34725 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

    void init();
};

#endif
