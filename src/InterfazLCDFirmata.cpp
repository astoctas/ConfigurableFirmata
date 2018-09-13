
#include <LiquidCrystal_PCF8574.h>
#include <ConfigurableFirmata.h>
#include "InterfazLCDFirmata.h"

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
    // CATCH ALL SYSEX MESSAGES
    if (command == ACCELSTEPPER_DATA) {
      pushLCD("PAP");
    }

  // LCD MESSAGES
  if (command == LCD_DATA) {
    byte  lcdCommand;

    lcdCommand = argv[0];

      if (lcdCommand == LCD_PRINT) {
        byte row = argv[1];
        char buf[17] = "";
        byte j = 0;
        for (byte i = 2; i < argc - 1; i += 2) {
          buf[j++]  = argv[i] + (argv[i + 1] << 7);
        }
        printc(buf, row);
      }
      else if (lcdCommand == LCD_PUSH) {
        char buf[17] = "";
        byte j = 0;
        for (byte i = 1; i < argc; i += 2) {
          buf[j++]  = argv[i] + (argv[i + 1] << 7);
        }
        pushLCD(buf);        
      }
      else if (lcdCommand == LCD_CLEAR) {
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
    printc(lcdBuffer,1);
    printc(str,0);
}

/*==============================================================================
 * SETUP()
 *============================================================================*/

void InterfazLCDFirmata::reset()
{
  lcd = new LiquidCrystal_PCF8574(LCD_ADDRESS);
  lcd->begin(16,2);
  lcd->setBacklight(255);
  lcd->clear();
  pushLCD("Hola!");  

}


