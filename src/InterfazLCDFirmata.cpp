
#include <LiquidCrystal_PCF8574.h>
#include "InterfazLCDFirmata.h"
#include "InterfazL293DFirmata.h"
#include "AccelStepperFirmata.h"

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
    byte param1 = argv[0]; // COMMAND
    byte param2 = argv[1]; // DEVICE NUM
    byte param3 = 0;
    char buf[17] = "";

    // CATCH ALL SYSEX MESSAGES
    if (command == ACCELSTEPPER_DATA) {
      if(param1 == ACCELSTEPPER_STEP) {
        AccelStepperFirmata s_tmp;
        long numSteps = s_tmp.decode32BitSignedInteger(argv[2], argv[3], argv[4], argv[5], argv[6]);
        sprintf_P(buf,PSTR(MSG_STEPPER_STEP),param2+1, numSteps);
        pushLCD(buf);
        return false;
      }
    }
    if (command == L293D_DATA) {
      if (argc > 2) param3 = argv[2];
      switch(param1) {
        case L293D_ON: sprintf_P(buf,PSTR(MSG_DC_ON),param2+1); break;
        case L293D_OFF: sprintf_P(buf,PSTR(MSG_DC_OFF),param2+1); break;
        case L293D_BRAKE: sprintf_P(buf,PSTR(MSG_DC_BRAKE),param2+1); break;
        case L293D_INVERSE: sprintf_P(buf,PSTR(MSG_DC_INVERSE),param2+1); break;
        case L293D_DIR: sprintf_P(buf,PSTR(MSG_DC_DIR),param2+1, param3); break;
        case L293D_SPEED: sprintf_P(buf,PSTR(MSG_DC_SPEED),param2+1, map(param3,0,255,0,100)); break;
      }
      pushLCD(buf);
      return false;
    }
    if (command == EXTENDED_ANALOG) {
        for(int i =0; i < MAX_SERVO_MOTORS; i++) {
          if(param1 == ServoOutputs[i].pin) {
              if (argc > 2) param2 |= (argv[2] << 7);
              if (argc > 3) param2 |= (argv[3] << 14);      
              sprintf_P(buf,PSTR(MSG_SERVO_WRITE),i+1, param2);
              pushLCD(buf);
              return false;
          }
        }
    }

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

void InterfazLCDFirmata::reset()
{
  lcd = new LiquidCrystal_PCF8574(LCD_ADDRESS);
  lcd->begin(16,2);
  lcd->setBacklight(255);
  pushLCD("Hola!");  

}


