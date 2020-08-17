
#include <ConfigurableFirmata.h>
#include "utility/AFMotor.h"
#include "InterfazL293DShieldFirmata.h"
// #include "utility/FirmataL293D.h"

boolean InterfazL293DShieldFirmata::handlePinMode(byte pin, int mode)
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

void InterfazL293DShieldFirmata::handleCapability(byte pin)
{
}

/*==============================================================================
 * SYSEX-BASED commands
 *============================================================================*/

boolean InterfazL293DShieldFirmata::handleSysex(byte command, byte argc, byte *argv)
{
  if (command == L293D_DATA) {
    byte  stepCommand, deviceNum, motorPin1, motorPin2, motorPin3;

    stepCommand = argv[0];
    deviceNum = argv[1];


    if (deviceNum < MAX_DC_OUTPUTS) {
      if (stepCommand == L293D_CONFIG) {
        outputs[deviceNum] = new AF_DCMotor(deviceNum + 1);
        outputs[deviceNum]->setSpeed(255);
        outputs[deviceNum]->running = 0;
      }
      else if (stepCommand == L293D_ON) {
        byte dir = outputs[deviceNum]->direction ? FORWARD : BACKWARD;
        outputs[deviceNum]->run(dir);
        outputs[deviceNum]->running = 1;
      }
      else if (stepCommand == L293D_OFF) {
        outputs[deviceNum]->run(RELEASE);
        outputs[deviceNum]->running = 0;
      }
      else if (stepCommand == L293D_BRAKE) {
        outputs[deviceNum]->run(BRAKE);
        delay(150);
        outputs[deviceNum]->run(RELEASE);
        outputs[deviceNum]->running = 0;
      }
      else if (stepCommand == L293D_DIR) {
        byte direction = argv[2] ? 1 : 0;
        outputs[deviceNum]->direction = direction;
        if(outputs[deviceNum]->running) {
          byte dir = outputs[deviceNum]->direction ? FORWARD : BACKWARD;
          outputs[deviceNum]->run(dir);
        }
      }
      else if (stepCommand == L293D_INVERSE) {
        outputs[deviceNum]->direction = ! outputs[deviceNum]->direction;
        if(outputs[deviceNum]->running) {
          byte dir = outputs[deviceNum]->direction ? FORWARD : BACKWARD;
          outputs[deviceNum]->run(dir);
        }
      }
      else if (stepCommand == L293D_SPEED) {
        byte speed = argv[2] | argv[3] << 7;
        outputs[deviceNum]->setSpeed(map(speed,0,100,0,255));
        if(outputs[deviceNum]->running) {
          byte dir = outputs[deviceNum]->direction ? FORWARD : BACKWARD;
          outputs[deviceNum]->run(dir);
        } else {
          outputs[deviceNum]->run(RELEASE);
        }
      }
      return true;
    }
  }
  return false;
}

/*==============================================================================
 * SETUP()
 *============================================================================*/

void InterfazL293DShieldFirmata::reset()
{
  for (byte i = 0; i < MAX_DC_OUTPUTS; i++) {
    if (outputs[i]) {
      free(outputs[i]);
      outputs[i] = 0;
    }
  }

}
