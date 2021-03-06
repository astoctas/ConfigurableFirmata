
#include "InterfazLCDFirmata.h"
#if defined(_L293SHIELD_)
#include "InterfazL293DShieldFirmata.h"
#else
#include "InterfazL293DFirmata.h"
#endif
#include "AccelStepperFirmata.h"

#define SERVO_WRITE            0x02 // write to servo motor


boolean InterfazLCDFirmata::handlePinMode(byte pin, int mode)
{
}

void InterfazLCDFirmata::handleCapability(byte pin)
{
}




/*==============================================================================
 * SYSEX-BASED commands
 *============================================================================*/

boolean InterfazLCDFirmata::handleSysex(byte command, byte argc, byte *argv)
{
    byte param1 = argv[0]; // SUBCOMMAND
    byte param2 = argv[1]; // DEVICE NUM
    byte param3 = 0;
    char buf[17] = "";


  // LCD MESSAGES
  if (command == LCD_DATA) {

      if (param1 == LCD_PRINT) {
        byte row = argv[1];
        byte j = 0;
        for (byte i = 2; i < argc - 1; i += 2) {
          buf[j++]  = argv[i] + (argv[i + 1] << 7);
        }
        printc(buf, row);
      }
      else if (param1 == LCD_PUSH) {
        byte j = 0;
        for (byte i = 1; i < argc; i += 2) {
          buf[j++]  = argv[i] + (argv[i + 1] << 7);
        }
        pushLCD(buf);
      }
      else if (param1 == LCD_CLEAR) {
        lcd->clear();
      }
      return true;
  }
  return false;
}


void InterfazLCDFirmata::printc(const char* str, byte row) {
    lcd->setCursor(0,row);
    String b  = String("");
    lcd->print(b.c_str());
    String s = String(str);
    byte col = floor((16 - s.length())/2);
    lcd->setCursor(col, row);
    lcd->print(s.c_str());
    if(row==0)  memcpy(lcdBuffer,str,16);
}

void InterfazLCDFirmata::pushLCD(const char* str) {
    lcd->clear();
    printc(lcdBuffer,1);
    printc(str,0);
}


/*==============================================================================
 * SETUP()
 *============================================================================*/

void InterfazLCDFirmata::init() {
  lcd = new LiquidCrystal_PCF8574(LCD_ADDRESS);
  lcd->begin(16,2);
  lcd->setBacklight(255);
}

 void InterfazLCDFirmata::reset()
{
  init();
  lcd->clear();
  printc("Hola!",0);
}
