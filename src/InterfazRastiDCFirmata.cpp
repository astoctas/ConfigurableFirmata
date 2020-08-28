
#include <ConfigurableFirmata.h>
#include "InterfazRastiDCFirmata.h"
// #include "utility/FirmataL293D.h"

boolean InterfazRastiDCFirmata::handlePinMode(byte pin, int mode)
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

void InterfazRastiDCFirmata::handleCapability(byte pin)
{
}

/*==============================================================================
 * SYSEX-BASED commands
 *============================================================================*/

boolean InterfazRastiDCFirmata::handleSysex(byte command, byte argc, byte *argv)
{
  if (command == L293D_DATA) {
    byte  stepCommand, deviceNum, motorPin1, motorPin2, motorPin3;

    stepCommand = argv[0];
    deviceNum = argv[1];


    if (deviceNum < MAX_DC_OUTPUTS) {
      if (stepCommand == L293D_CONFIG) {
        outputs[deviceNum].pin_ground = deviceNum == 1 ? 7 : 4;
        outputs[deviceNum].pin_potencia = deviceNum == 1 ? 6 : 5;
        pinMode(outputs[deviceNum].pin_ground, OUTPUT);
        pinMode(outputs[deviceNum].pin_potencia, PWM);
        outputs[deviceNum].direccion = 0;
        outputs[deviceNum].velocidad = 255;
        outputs[deviceNum].running = 0;
      }
      else if (stepCommand == L293D_ON) {
        analogWrite(outputs[deviceNum].pin_potencia, outputs[deviceNum].direccion ? 255 - outputs[deviceNum].velocidad : outputs[deviceNum].velocidad);
        digitalWrite(outputs[deviceNum].pin_ground,outputs[deviceNum].direccion);
        outputs[deviceNum].running = 1;
      }
      else if (stepCommand == L293D_OFF) {
        analogWrite(outputs[deviceNum].pin_potencia, outputs[deviceNum].direccion ? 255 : 0);
        outputs[deviceNum].running = 0;
      }
      else if (stepCommand == L293D_BRAKE) {
      }
      else if (stepCommand == L293D_DIR) {
        byte direction = argv[2] == 1 ? 1 : 0;
        outputs[deviceNum].direccion = direction;
        digitalWrite(outputs[deviceNum].pin_ground, outputs[deviceNum].direccion);
        if(outputs[deviceNum].running) 
          analogWrite(outputs[deviceNum].pin_potencia, outputs[deviceNum].direccion ? 255 - outputs[deviceNum].velocidad : outputs[deviceNum].velocidad);
      }
      else if (stepCommand == L293D_INVERSE) {
        outputs[deviceNum].direccion = ! outputs[deviceNum].direccion ? 1 : 0;
        digitalWrite(outputs[deviceNum].pin_ground, outputs[deviceNum].direccion);
        if(outputs[deviceNum].running) 
          analogWrite(outputs[deviceNum].pin_potencia, outputs[deviceNum].direccion ? 255 - outputs[deviceNum].velocidad : outputs[deviceNum].velocidad);
      }
      else if (stepCommand == L293D_SPEED) {
        byte speed = argv[2] | argv[3] << 7;
        outputs[deviceNum].velocidad = map(speed,0,100,0,255);
        if(outputs[deviceNum].running) 
          analogWrite(outputs[deviceNum].pin_potencia, outputs[deviceNum].direccion ? 255 - outputs[deviceNum].velocidad : outputs[deviceNum].velocidad);
      }
      return true;
    }
  }
  return false;
}

/*==============================================================================
 * SETUP()
 *============================================================================*/

void InterfazRastiDCFirmata::reset()
{

}
