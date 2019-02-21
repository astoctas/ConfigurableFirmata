#ifndef InterfazLCDFirmata_h
#define InterfazLCDFirmata_h

// #include <Wire.h>
#include "utility/FirmataInterfaces.h"
#include <LiquidCrystal_PCF8574.h>
#include <ConfigurableFirmata.h>
#include "FirmataFeature.h"

#define LCD_ADDRESS 0x27 
#define LCD_PRINT 0x00
#define LCD_PUSH 0x01
#define LCD_CLEAR 0x02

class InterfazLCDFirmata : public FirmataFeature
{
  public:
    boolean handlePinMode(byte pin, int mode);
    void handleCapability(byte pin);
    boolean handleSysex(byte command, byte argc, byte *argv);
    void reset();
    
    LiquidCrystal_PCF8574 *lcd;  
    void printc(const char* str, byte row);
    void pushLCD(const char* str);
  private:
    char lcdBuffer[17];
};

#endif
