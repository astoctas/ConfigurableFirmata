#include "InterfazFirmata.h"

boolean InterfazFirmata::handlePinMode(byte pin, int mode)
{
  return false;
}

void InterfazFirmata::handleCapability(byte pin)
{
}


void  InterfazFirmata::initSteppers() {
  // CONFIGURAR STEPPERS
  /*
  for(int i =0; i < MAX_STEPPERS; i++) {
    digitalWrite(StepperEnables[i].enable, HIGH);
  }
  */

}

void  InterfazFirmata::initDC() {
  for(int i =0; i < MAX_DC_OUTPUTS; i++) {
    Firmata.parse(START_SYSEX);
    Firmata.parse(L293D_DATA);
    Firmata.parse(L293D_CONFIG);
    Firmata.parse(i);
    Firmata.parse(END_SYSEX);
  }
  // SERVOS INTERFAZ
  #ifdef _INTERFAZ_
    Firmata.parse(SET_PIN_MODE);
    Firmata.parse(0x09);
    Firmata.parse(PIN_MODE_SERVO);
    Firmata.parse(SET_PIN_MODE);
    Firmata.parse(0x0A);
    Firmata.parse(PIN_MODE_SERVO);
  #endif
  
}


/*==============================================================================
 * SYSEX-BASED commands
 *============================================================================*/

boolean InterfazFirmata::handleSysex(byte command, byte argc, byte *argv)
{
  return true;
}

/*==============================================================================
 * SETUP()
 *============================================================================*/

void InterfazFirmata::reset()
{
  initSteppers();
  initDC();
}
