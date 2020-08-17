/*
  PixelFirmata.h - Firmata library
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

  PixelFirmata.cpp has been merged into this header file as a hack to avoid having to
  include Servo.h for every arduino sketch that includes ConfigurableFirmata.

  Last updated by Jeff Hoefs: November 15th, 2015
*/

#ifndef PixelFirmata_h
#define PixelFirmata_h

#include <ConfigurableFirmata.h>
#include "FirmataFeature.h"

#include "./lw_ws2812.h"
#include "./ws2812.h"

class PixelFirmata: public FirmataFeature
{
  public:
    PixelFirmata();
    boolean analogWrite(byte pin, int value);
    boolean handlePinMode(byte pin, int mode);
    void handleCapability(byte pin);
    boolean handleSysex(byte command, byte argc, byte* argv);
    void reset();
};


/*
 * PixelFirmata.cpp
 * Copied here as a hack to avoid having to include Servo.h in all sketch files that
 * include ConfigurableFirmata.h
 */


PixelFirmata::PixelFirmata()
{
  ws2812_initialise();
}


boolean PixelFirmata::handlePinMode(byte pin, int mode)
{
 }

void PixelFirmata::handleCapability(byte pin)
{
    if (IS_PIN_DIGITAL(pin)) {
          Firmata.write((byte)PIXEL_COMMAND);
          Firmata.write(1);
    }
    /*
    if (IS_PIN_ANALOG(pin)) {
          Firmata.write((byte)PING_READ);
          Firmata.write(1);
    }
    */
}

boolean PixelFirmata::handleSysex(byte command, byte argc, byte* argv)
{

  if (command == PIXEL_COMMAND) {
      if (argc > 0) {
          // maybe bounce the first command off here.
          process_command(argc, argv);
          return true;
      }
    }
  return false;
}

void PixelFirmata::reset()
{
  ws2812_initialise();
}

#endif /* PixelFirmata_h */
