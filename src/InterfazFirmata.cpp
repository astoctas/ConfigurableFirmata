#include "InterfazFirmata.h"

boolean InterfazFirmata::handlePinMode(byte pin, int mode)
{
}

void InterfazFirmata::handleCapability(byte pin)
{
}


void  InterfazFirmata::initSteppers() {
  // CONFIGURAR STEPPERS
  for(int i =0; i < MAX_STEPPERS; i++) {
    digitalWrite(StepperEnables[i].enable, HIGH);
  }

}

void  InterfazFirmata::initDC() {
  for(int i =0; i < MAX_DC_OUTPUTS; i++) {
    Firmata.parse(START_SYSEX);
    Firmata.parse(L293D_DATA);
    Firmata.parse(L293D_CONFIG);
    Firmata.parse(i);
    Firmata.parse(END_SYSEX);
  }
}


/*==============================================================================
 * SYSEX-BASED commands
 *============================================================================*/

boolean InterfazFirmata::handleSysex(byte command, byte argc, byte *argv)
{
}

/*==============================================================================
 * SETUP()
 *============================================================================*/

void InterfazFirmata::reset()
{
  initSteppers();
  initDC();
}
