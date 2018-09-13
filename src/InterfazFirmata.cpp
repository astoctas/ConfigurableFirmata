#include <AccelStepperFirmata.h>
#include "InterfazFirmata.h"

boolean InterfazFirmata::handlePinMode(byte pin, int mode)
{
}

void InterfazFirmata::handleCapability(byte pin)
{
}

void  InterfazFirmata::initSteppers() {
  // CONFIGURAR STEPPERS
    Firmata.parse(START_SYSEX);
    Firmata.parse(ACCELSTEPPER_DATA);
    Firmata.parse(ACCELSTEPPER_CONFIG);
    Firmata.parse(0);
    Firmata.parse(0x13);
    Firmata.parse(38);
    Firmata.parse(39);
    Firmata.parse(40);
    Firmata.parse(0x10);
    Firmata.parse(END_SYSEX);
  
  // APAGAR ENABLE AL ARRANQUE
    Firmata.parse(START_SYSEX);
    Firmata.parse(ACCELSTEPPER_DATA);
    Firmata.parse(ACCELSTEPPER_ENABLE);
    Firmata.parse(0);
    Firmata.parse(0);
    Firmata.parse(END_SYSEX);

    
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


