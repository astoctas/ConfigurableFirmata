/*
  UltrasonicFirmata.h - Firmata library
  Copyright (C) 2006-2008 Hans-Christoph Steiner.  All rights reserved.
  Copyright (C) 2010-2011 Paul Stoffregen.  All rights reserved.
  Copyright (C) 2009 Shigeru Kobayashi.  All rights reserved.
  Copyright (C) 2013 Norbert Truchsess. All rights reserved.
  Copyright (C) 2009-2015 Jeff Hoefs.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.

  UltrasonicFirmata.cpp has been merged into this header file as a hack to avoid having to
  include Servo.h for every arduino sketch that includes ConfigurableFirmata.

  Last updated by Jeff Hoefs: November 15th, 2015
*/

#ifndef UltrasonicFirmata_h
#define UltrasonicFirmata_h

#include <ConfigurableFirmata.h>
#include "FirmataFeature.h"

#define PING_READ 0x76

class UltrasonicFirmata: public FirmataFeature
{
  public:
    UltrasonicFirmata();
    boolean analogWrite(byte pin, int value);
    boolean handlePinMode(byte pin, int mode);
    void handleCapability(byte pin);
    boolean handleSysex(byte command, byte argc, byte* argv);
    void reset();
};


/*
 * UltrasonicFirmata.cpp
 * Copied here as a hack to avoid having to include Servo.h in all sketch files that
 * include ConfigurableFirmata.h
 */


UltrasonicFirmata::UltrasonicFirmata()
{
}


boolean UltrasonicFirmata::handlePinMode(byte pin, int mode)
{
 }

void UltrasonicFirmata::handleCapability(byte pin)
{
    if (IS_PIN_DIGITAL(pin)) {
          Firmata.write((byte)PING_READ);
          Firmata.write(1);
    }
    if (IS_PIN_ANALOG(pin)) {
          Firmata.write((byte)PING_READ);
          Firmata.write(1);
    }
    
}

boolean UltrasonicFirmata::handleSysex(byte command, byte argc, byte* argv)
{
  if (command == PING_READ) {
        int triggerPin  = (argv[0] & 0x7F) | ((argv[1] & 0x7F) << 7);
        int echoPin     = (argv[2] & 0x7F) | ((argv[3] & 0x7F) << 7);
        unsigned long duration;
        byte responseArray[5];

        unsigned long timeout = 100000;

        unsigned long pulseDuration = 10;
        pinMode(triggerPin,OUTPUT);
        pinMode(echoPin,INPUT);

        digitalWrite(triggerPin,LOW);
        delayMicroseconds(4);
        digitalWrite(triggerPin,HIGH);
        delayMicroseconds(10);
        // digitalWrite(triggerPin,LOW);
        duration = pulseIn(echoPin, HIGH);
        responseArray[0] = triggerPin;
        responseArray[1] = (((unsigned long)duration >> 24) & 0xFF);
        responseArray[2] = (((unsigned long)duration >> 16) & 0xFF);
        responseArray[3] = (((unsigned long)duration >> 8) & 0xFF);
        responseArray[4] = (((unsigned long)duration & 0xFF));
        responseArray[5] = echoPin;


        Firmata.sendSysex(PING_READ, 6, responseArray);
        return true;
    }
  return false;
}

void UltrasonicFirmata::reset()
{
}

#endif /* UltrasonicFirmata_h */
