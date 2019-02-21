/*
  Copyright (C) 2006-2008 Hans-Christoph Steiner.  All rights reserved.
  Copyright (C) 2010-2011 Paul Stoffregen.  All rights reserved.
  Copyright (C) 2009 Shigeru Kobayashi.  All rights reserved.
  Copyright (C) 2013 Norbert Truchsess. All rights reserved.
  Copyright (C) 2009-2017 Jeff Hoefs.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

#ifndef InterfazAccelStepperFirmata_h
#define InterfazAccelStepperFirmata_h

#include <ConfigurableFirmata.h>
#include "utility/AccelStepper.h"
#include "utility/MultiStepper.h"
#include "FirmataFeature.h"

#define MAX_ACCELSTEPPERS 10 // arbitrary value... may need to adjust
#define MAX_GROUPS 5 // arbitrary value... may need to adjust
#define MAX_ACCELERATION 1000000 // 1000^2 so that full speed is reached on first step
#define STEP_TYPE_WHOLE 0x00
#define STEP_TYPE_HALF 0x01
#define ACCELSTEPPER_CONFIG 0x00
#define ACCELSTEPPER_ZERO 0x01
#define ACCELSTEPPER_STEP 0x02
#define ACCELSTEPPER_TO 0x03
#define ACCELSTEPPER_ENABLE 0x04
#define ACCELSTEPPER_STOP 0x05
#define ACCELSTEPPER_REPORT_POSITION 0x06
#define ACCELSTEPPER_LIMIT 0x07
#define ACCELSTEPPER_SET_ACCELERATION 0x08
#define ACCELSTEPPER_SET_SPEED 0x09
#define ACCELSTEPPER_MOVE_COMPLETE 0x0a
#define ACCELSTEPPER_ENABLE_PINS 0x0b
#define MULTISTEPPER_CONFIG 0x20
#define MULTISTEPPER_TO 0x21
#define MULTISTEPPER_STOP 0x23
#define MULTISTEPPER_MOVE_COMPLETE 0x24

class L293DAccelStepper: public AccelStepper 
{
  public:
      L293DAccelStepper(uint8_t interface = AccelStepper::FULL4WIRE, uint8_t pin1 = 2, uint8_t pin2 = 3, uint8_t pin3 = 4, uint8_t pin4 = 5, bool enable = true)
        : AccelStepper(interface, pin1, pin2, pin3, pin4, enable) {};
      void  enablesOn()  {
        digitalWrite(enable1, HIGH);
        digitalWrite(enable2, HIGH);
      };
       void enablesOff() {
        digitalWrite(enable1, LOW);
        digitalWrite(enable2, LOW);
      };      
      void setEnablePins( uint8_t pin1 = 4, uint8_t pin2 = 5 ) {
        enable1 = pin1;
        enable2 = pin2;
      }
  private:
    byte enable1, enable2;
};

class InterfazAccelStepperFirmata: public FirmataFeature
{
  public:
    boolean handlePinMode(byte pin, int mode);
    void handleCapability(byte pin);
    void reportPosition(byte deviceNum, bool complete);
    void reportGroupComplete(byte deviceNum);
    boolean handleSysex(byte command, byte argc, byte *argv);
    float decodeCustomFloat(byte arg1, byte arg2, byte arg3, byte arg4);
    long decode28BitUnsignedInteger(byte arg1, byte arg2, byte arg3, byte arg4);
    long decode32BitSignedInteger(byte arg1, byte arg2, byte arg3, byte arg4, byte arg5);
    void encode32BitSignedInteger(long value, byte pdata[]);
    void update();
    void reset();
  private:
    L293DAccelStepper *stepper[MAX_ACCELSTEPPERS];
    MultiStepper *group[MAX_GROUPS];
    bool isRunning[MAX_ACCELSTEPPERS];
    bool groupIsRunning[MAX_GROUPS];
    byte numSteppers;
    byte numGroups;
    byte groupStepperCount[MAX_GROUPS];
};

#endif /* AccelStepperFirmata_h */
