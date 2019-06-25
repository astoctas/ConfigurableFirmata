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
}
