#include "InterfazFirmata.h"

boolean InterfazFirmata::handlePinMode(byte pin, int mode)
{
}

void InterfazFirmata::handleCapability(byte pin)
{
}

void  InterfazFirmata::initServos() {
  for(int i =0; i < MAX_SERVO_MOTORS; i++) {
    Firmata.parse(SET_PIN_MODE);
    Firmata.parse(ServoOutputs[i].pin);
    Firmata.parse(PIN_MODE_SERVO);
  }
}

void  InterfazFirmata::initDC() {
  for(int i =0; i < MAX_DC_OUTPUTS; i++) {
    Firmata.parse(START_SYSEX);
    Firmata.parse(L293D_DATA);
    Firmata.parse(L293D_CONFIG);
    Firmata.parse(i);
    Firmata.parse(DCOutputs[i].enable);
    Firmata.parse(DCOutputs[i].in1);
    Firmata.parse(DCOutputs[i].in2);
    Firmata.parse(END_SYSEX);
  }
}

void  InterfazFirmata::initSteppers() {
  // CONFIGURAR STEPPERS
  for(int i =0; i < MAX_STEPPERS; i++) {
    Firmata.parse(START_SYSEX);
    Firmata.parse(ACCELSTEPPER_DATA);
    Firmata.parse(ACCELSTEPPER_CONFIG);
    Firmata.parse(i);
    Firmata.parse(0x13);
    Firmata.parse(StepperOutputs[i].step);
    Firmata.parse(StepperOutputs[i].dir);
    Firmata.parse(StepperOutputs[i].enable);
    Firmata.parse(StepperOutputs[i].invert);
    Firmata.parse(END_SYSEX);

  // APAGAR ENABLE AL ARRANQUE
    Firmata.parse(START_SYSEX);
    Firmata.parse(ACCELSTEPPER_DATA);
    Firmata.parse(ACCELSTEPPER_ENABLE);
    Firmata.parse(i);
    Firmata.parse(0);
    Firmata.parse(END_SYSEX);

  // VELOCIDAD POR DEFAULT = 100
    Firmata.parse(START_SYSEX);
    Firmata.parse(ACCELSTEPPER_DATA);
    Firmata.parse(ACCELSTEPPER_SET_SPEED);
    Firmata.parse(i);
    Firmata.parse(1);
    Firmata.parse(0);
    Firmata.parse(0);
    Firmata.parse(52);
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
  initDC();
  initSteppers();
  initServos();

}


