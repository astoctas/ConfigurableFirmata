
#include <ConfigurableFirmata.h>
#include "InterfazL293DFirmata.h"
// #include "utility/FirmataL293D.h"

boolean InterfazL293DFirmata::handlePinMode(byte pin, int mode)
{
  if (mode == OUTPUT) {
    if (IS_PIN_DIGITAL(pin)) {
      digitalWrite(PIN_TO_DIGITAL(pin), LOW); // disable PWM
      pinMode(PIN_TO_DIGITAL(pin), OUTPUT);
      return true;
    }
  }
  if (mode == PIN_MODE_PWM) {
    if (IS_PIN_DIGITAL(pin)) {
      pinMode(PIN_TO_DIGITAL(pin), PIN_MODE_PWM);
      return true;
    }
  }  
  return false;
}

void InterfazL293DFirmata::handleCapability(byte pin)
{
}

/*==============================================================================
 * SYSEX-BASED commands
 *============================================================================*/

boolean InterfazL293DFirmata::handleSysex(byte command, byte argc, byte *argv)
{
  if (command == L293D_DATA) {
    byte  stepCommand, deviceNum, motorPin1, motorPin2, motorPin3;

    stepCommand = argv[0];
    deviceNum = argv[1];


    if (deviceNum < MAX_OUTPUTS) {
      if (stepCommand == L293D_CONFIG) {
        motorPin1 = argv[2];
        motorPin2 = argv[3];
        motorPin3 = argv[4];
        if (Firmata.getPinMode(motorPin1) == PIN_MODE_IGNORE || Firmata.getPinMode(motorPin2) == PIN_MODE_IGNORE  || Firmata.getPinMode(motorPin3) == PIN_MODE_IGNORE)
          return false;
        Firmata.setPinMode(motorPin1, PIN_MODE_PWM);
        Firmata.setPinMode(motorPin2, OUTPUT);
        Firmata.setPinMode(motorPin3, OUTPUT);

        if (!outputs[deviceNum]) {
          numOutputs++;
        }
        outputs[deviceNum] = new FirmataL293D(motorPin1, motorPin2, motorPin3);
      }
      else if (stepCommand == L293D_ON) {
        outputs[deviceNum]->turnOn();
      }
      else if (stepCommand == L293D_OFF) {
        outputs[deviceNum]->turnOff();
      }
      else if (stepCommand == L293D_BRAKE) {
        outputs[deviceNum]->brake(100);
      }
      else if (stepCommand == L293D_DIR) {
        byte direction = argv[2];
        outputs[deviceNum]->setDirection(direction);
      }
      else if (stepCommand == L293D_INVERSE) {
        outputs[deviceNum]->invert();
      }
      else if (stepCommand == L293D_SPEED) {
        byte speed = argv[2];
        outputs[deviceNum]->setSpeed(speed);
      }
      return true;
    }
  }
  return false;
}

/*==============================================================================
 * SETUP()
 *============================================================================*/

void InterfazL293DFirmata::reset()
{
  for (byte i = 0; i < MAX_OUTPUTS; i++) {
    if (outputs[i]) {
      free(outputs[i]);
      outputs[i] = 0;
    }
  }
  numOutputs = 0;
}


