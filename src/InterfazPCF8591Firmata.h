/*
  InterfazPCF8591Firmata.h - Firmata library
  Copyright (C) 2006-2008 Hans-Christoph Steiner.  All rights reserved.
  Copyright (C) 2010-2011 Paul Stoffregen.  All rights reserved.
  Copyright (C) 2009 Shigeru Kobayashi.  All rights reserved.
  Copyright (C) 2013 Norbert Truchsess. All rights reserved.
  Copyright (C) 2009-2016 Jeff Hoefs.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.

  InterfazPCF8591Firmata.cpp has been merged into this header file as a hack to avoid having to
  include Wire.h for every arduino sketch that includes ConfigurableFirmata.

  Last updated by Jeff Hoefs: January 23rd, 2015
*/

#ifndef PCF8591_h
#define PCF8591_h

#include <Adafruit_I2CDevice.h>
#include <Adafruit_PCF8591.h>
#include <ConfigurableFirmata.h>
#include "FirmataFeature.h"
#include "FirmataReporting.h"

#define PCF8591_REQUEST  1


class InterfazPCF8591Firmata: public FirmataFeature
{
  public:
    InterfazPCF8591Firmata();
    boolean handlePinMode(byte pin, int mode);
    void handleCapability(byte pin);
    boolean handleSysex(byte command, byte argc, byte* argv);
    void reset();
    void report();

  private:
    Adafruit_PCF8591 pcf = Adafruit_PCF8591();
    void readAndReportData();
    byte isReporting = false;
};


/*
 * InterfazPCF8591Firmata.cpp
 * Copied here as a hack to avoid having to include Wire.h in all sketch files that
 * include ConfigurableFirmata.h
 */

InterfazPCF8591Firmata::InterfazPCF8591Firmata()
{
}

void InterfazPCF8591Firmata::readAndReportData() {
  // allow I2C requests that don't require a register read
  // for example, some devices using an interrupt pin to signify new data available
  // do not always require the register read so upon interrupt you call Wire.requestFrom()
      byte v[4];
      v[0] = pcf.analogRead(0);
      v[1] = pcf.analogRead(1);
      v[2] = pcf.analogRead(2);
      v[3] = pcf.analogRead(3);
      Firmata.sendSysex(PCF8591_DATA, 4, v);

}

boolean InterfazPCF8591Firmata::handlePinMode(byte pin, int mode)
{
  if (IS_PIN_I2C(pin)) {
    if (mode == PIN_MODE_I2C) {
      // the user must call I2C_CONFIG to enable I2C for a device
      return true;
    }
  }
  return false;
}

void InterfazPCF8591Firmata::handleCapability(byte pin)
{
  if (IS_PIN_I2C(pin)) {
    Firmata.write(PIN_MODE_I2C);
    Firmata.write(1); // TODO: could assign a number to map to SCL or SDA
  }
}

boolean InterfazPCF8591Firmata::handleSysex(byte command, byte argc, byte *argv)
{
  switch (command) {
    case PCF8591_DATA:
      isReporting = true;
      return true;
    break;
  }
  return false;
}


void InterfazPCF8591Firmata::reset()
{
  pcf.begin();
}

void InterfazPCF8591Firmata::report()
{
  // report i2c data for all device with read continuous mode enabled
  if(isReporting)
    readAndReportData();
}

#endif /* InterfazPCF8591Firmata_h */
