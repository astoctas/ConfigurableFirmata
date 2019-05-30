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

/* LCD STRINGS */

#define MSG_STEPPER_OUTPUT  "PAP %d"
#define MSG_STEPPER_STEP  "%d pasos"
#define MSG_SERVO_OUTPUT   "Servo %d"
#define MSG_SERVO_WRITE         "posicion %d"
#define MSG_DC_OUTPUT        "Salida %d"
#define MSG_DC_ON              "encendido"
#define MSG_DC_OFF             "apagado"
#define MSG_DC_INVERSE     "invertido"
#define MSG_DC_BRAKE        "frenado"
#define MSG_DC_DIR             "direccion %d"
#define MSG_DC_SPEED        "potencia %d%%"
#define MSG_REPORT_ANALOG_1        "Reportando"
#define MSG_REPORT_ANALOG_2        "sensor %d"

class InterfazLCDFirmata : public FirmataFeature
{
  public:
    boolean handlePinMode(byte pin, int mode);
    void handleCapability(byte pin);
    boolean handleSysex(byte command, byte argc, byte *argv);
    void reset();

    LiquidCrystal_PCF8574 *lcd;
    void init();
    void printc(const char* str, byte row);
    void pushLCD(const char* str);
  private:
    char lcdBuffer[17];
};

#endif
