/*
  PingFirmata.h - Firmata library
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

  PingFirmata.cpp has been merged into this header file as a hack to avoid having to
  include Servo.h for every arduino sketch that includes ConfigurableFirmata.

  Last updated by Jeff Hoefs: November 15th, 2015
*/

#ifndef PingFirmata_h
#define PingFirmata_h

#include <ConfigurableFirmata.h>
#include "FirmataFeature.h"

#define PING_READ 0x75

class PingFirmata: public FirmataFeature
{
  public:
    PingFirmata();
    boolean analogWrite(byte pin, int value);
    boolean handlePinMode(byte pin, int mode);
    void handleCapability(byte pin);
    boolean handleSysex(byte command, byte argc, byte* argv);
    void reset();
};


/*
 * PingFirmata.cpp
 * Copied here as a hack to avoid having to include Servo.h in all sketch files that
 * include ConfigurableFirmata.h
 */


PingFirmata::PingFirmata()
{
}


boolean PingFirmata::handlePinMode(byte pin, int mode)
{
 }

void PingFirmata::handleCapability(byte pin)
{
    if (IS_PIN_DIGITAL(pin)) {
          Firmata.write((byte)PING_READ);
          Firmata.write(1);
    }
    /*
    if (IS_PIN_ANALOG(pin)) {
          Firmata.write((byte)PING_READ);
          Firmata.write(1);
    }
    */
}

boolean PingFirmata::handleSysex(byte command, byte argc, byte* argv)
{
  if (command == PING_READ) {
        byte pulseDurationArray[4] = {
        (argv[2] & 0x7F) | ((argv[3] & 0x7F) << 7),
        (argv[4] & 0x7F) | ((argv[5] & 0x7F) << 7),
        (argv[6] & 0x7F) | ((argv[7] & 0x7F) << 7),
        (argv[8] & 0x7F) | ((argv[9] & 0x7F) << 7)
        };
        unsigned long pulseDuration = ((unsigned long)pulseDurationArray[0] << 24)
                + ((unsigned long)pulseDurationArray[1] << 16)
                + ((unsigned long)pulseDurationArray[2] << 8)
                + ((unsigned long)pulseDurationArray[3]);
        if (argv[1] == HIGH){
        pinMode(argv[0],OUTPUT);
        digitalWrite(argv[0],LOW);
        delayMicroseconds(2);
        digitalWrite(argv[0],HIGH);
        delayMicroseconds(pulseDuration);
        digitalWrite(argv[0],LOW);
        } else {
        digitalWrite(argv[0],HIGH);
        delayMicroseconds(2);
        digitalWrite(argv[0],LOW);
        delayMicroseconds(pulseDuration);
        digitalWrite(argv[0],HIGH);
        }
        unsigned long duration;
        byte responseArray[5];
        byte timeoutArray[4] = {
            (argv[10] & 0x7F) | ((argv[11] & 0x7F) << 7),
            (argv[12] & 0x7F) | ((argv[13] & 0x7F) << 7),
            (argv[14] & 0x7F) | ((argv[15] & 0x7F) << 7),
            (argv[16] & 0x7F) | ((argv[17] & 0x7F) << 7)
        };
        unsigned long timeout = ((unsigned long)timeoutArray[0] << 24) +
                                ((unsigned long)timeoutArray[1] << 16) +
                                ((unsigned long)timeoutArray[2] << 8) +
                                ((unsigned long)timeoutArray[3]);

        pinMode(argv[0],INPUT);
        duration = pulseIn(argv[0], argv[1],timeout);
        responseArray[0] = argv[0];
        responseArray[1] = (((unsigned long)duration >> 24) & 0xFF);
        responseArray[2] = (((unsigned long)duration >> 16) & 0xFF);
        responseArray[3] = (((unsigned long)duration >> 8) & 0xFF);
        responseArray[4] = (((unsigned long)duration & 0xFF));

        Firmata.sendSysex(PING_READ, 5, responseArray);
        return true;
    }
  return false;
}

void PingFirmata::reset()
{
}

#endif /* PingFirmata_h */
