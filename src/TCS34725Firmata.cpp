
#include "TCS34725Firmata.h"



boolean TCS34725Firmata::handlePinMode(byte pin, int mode)
{
}

void TCS34725Firmata::handleCapability(byte pin)
{
}




/*==============================================================================
 * SYSEX-BASED commands
 *============================================================================*/

boolean TCS34725Firmata::handleSysex(byte command, byte argc, byte *argv)
{
    byte param1 = argv[0]; // SUBCOMMAND


  // LCD MESSAGES
  if (command == TCS34725_DATA) {

    uint16_t r, g, b, c, colorTemp, lux;
    TCS34725.getRawData(&r, &g, &b, &c);

    byte responseArray[5];

    responseArray[0] = (((unsigned long)r & 0xFF));
    responseArray[1] = (((unsigned long)r >> 8) & 0xFF);
    responseArray[2] = (((unsigned long)g & 0xFF));
    responseArray[3] = (((unsigned long)g >> 8) & 0xFF);
    responseArray[4] = (((unsigned long)b & 0xFF));
    responseArray[5] = (((unsigned long)b >> 8) & 0xFF);

    Firmata.sendSysex(TCS34725_DATA, 6, responseArray);
      return true;
  }
  return false;
}


/*==============================================================================
 * SETUP()
 *============================================================================*/

void TCS34725Firmata::init() {
  TCS34725.begin();  // pass in the address
}

 void TCS34725Firmata::reset()
{
  init();

}
