/*
  StringFirmata.cpp - Firmata library
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

  Last updated by Jeff Hoefs: November 15th, 2015
*/

#include <ConfigurableFirmata.h>
#include "StringFirmata.h"

//StringFirmata *StringFirmataInstance;

void stringCallback(char *myString)
{
  Firmata.sendString(myString);
//  StringFirmataInstance->reportDigital(port, value);
}

StringFirmata::StringFirmata()
{
  //StringFirmataInstance = this;
  Firmata.attach(STRING_DATA, stringCallback);
}

boolean StringFirmata::handleSysex(byte command, byte argc, byte* argv)
{
  return false;
}


boolean StringFirmata::handlePinMode(byte pin, int mode)
{
  return false;
}

void StringFirmata::handleCapability(byte pin)
{
}

void StringFirmata::reset()
{
}
