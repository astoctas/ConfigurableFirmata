
#include "Matrix8x8Firmata.h"



boolean Matrix8x8Firmata::handlePinMode(byte pin, int mode)
{
}

void Matrix8x8Firmata::handleCapability(byte pin)
{
}




/*==============================================================================
 * SYSEX-BASED commands
 *============================================================================*/

boolean Matrix8x8Firmata::handleSysex(byte command, byte argc, byte *argv)
{
    byte param1 = argv[0]; // SUBCOMMAND


  // LCD MESSAGES
  if (command == MATRIX_8x8_DATA) {

      if (param1 == MATRIX_8x8_PRINT) {
        uint8_t bufferArray[8] = {
            (argv[1] & 0x7F) | ((argv[2] & 0x7F) << 7),
            (argv[3] & 0x7F) | ((argv[4] & 0x7F) << 7),
            (argv[5] & 0x7F) | ((argv[6] & 0x7F) << 7),
            (argv[7] & 0x7F) | ((argv[8] & 0x7F) << 7),
            (argv[9] & 0x7F) | ((argv[10] & 0x7F) << 7),
            (argv[11] & 0x7F) | ((argv[12] & 0x7F) << 7),
            (argv[13] & 0x7F) | ((argv[14] & 0x7F) << 7),
            (argv[15] & 0x7F) | ((argv[16] & 0x7F) << 7)
        };

        matrix_8x8.clear();
        matrix_8x8.setRotation(1);
        matrix_8x8.drawBitmap(0, 0, bufferArray, 8, 8, LED_ON);
        matrix_8x8.writeDisplay();        
      }
      else if (param1 == MATRIX_8x8_WRITE) {
          char data;
          String str;

          for (byte i = 1; i < argc; i += 2) {
            data = argv[i] + (argv[i + 1] << 7);
            str.concat(data);
          }

        int desplazamiento_texto = (str.length()*6)+9;
        matrix_8x8.setRotation(1);
        matrix_8x8.setTextSize(1);
        matrix_8x8.setTextWrap(false);
        matrix_8x8.setTextColor(LED_ON);

        for (int x_ = 9; x_ >= -desplazamiento_texto; x_--) {
          matrix_8x8.clear();
          matrix_8x8.setCursor(x_, 0);
          matrix_8x8.print(str);
          matrix_8x8.writeDisplay();
          delay(100);
        }        
      }
      else if (param1 == MATRIX_8x8_CLEAR) {
        matrix_8x8.clear();
        matrix_8x8.writeDisplay();        
      }
      return true;
  }
  return false;
}


/*==============================================================================
 * SETUP()
 *============================================================================*/

void Matrix8x8Firmata::init() {
  matrix_8x8.begin(MATRIX_8x8_ADDRESS);  // pass in the address
}

 void Matrix8x8Firmata::reset()
{
  init();

}
