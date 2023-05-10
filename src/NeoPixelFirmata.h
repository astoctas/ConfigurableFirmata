/*
  NeoPixelFirmata.h - Firmata library
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

  NeoPixelFirmata.cpp has been merged into this header file as a hack to avoid having to
  include Servo.h for every arduino sketch that includes ConfigurableFirmata.

  Last updated by Jeff Hoefs: November 15th, 2015
*/

#ifndef NeoPixelFirmata_h
#define NeoPixelFirmata_h

#include <ConfigurableFirmata.h>
#include <Adafruit_NeoPixel.h>
#include "FirmataFeature.h"

#define PIXEL_COMMAND           0x51 // firmata command used for a pixel

// pixel command instruction set
#define PIXEL_OFF               0x00 // set strip to be off
#define PIXEL_CONFIG            0x01 // DEPRECATED was setting pin and length
#define PIXEL_SHOW              0x02 // latch the pixels and show them
#define PIXEL_SET_PIXEL         0x03 // set the color value of pixel n using 32bit packed color value
#define PIXEL_SET_STRIP         0x04 // set color of whole strip
#define PIXEL_SHIFT             0x05 // shift all pixels n places along the strip

// define the colour element layouts
#define PIXEL_COLOUR_GRB        0x0
#define PIXEL_COLOUR_RGB        0x1
#define PIXEL_COLOUR_BRG        0x2

#define STRIP_START_PIN 0

#define MAX_STRIPS 8
#define LED_DEFAULT_PIN 6
#define STRIP_LENGTH 64

#define BUFLENGTH 64

#define OFFSET_R(r) r+offsetRed
#define OFFSET_G(g) g+offsetGreen
#define OFFSET_B(b) b+offsetBlue

class NeoPixelFirmata: public FirmataFeature
{
  public:
    NeoPixelFirmata();
    boolean analogWrite(byte pin, int value);
    boolean handlePinMode(byte pin, int mode);
    void handleCapability(byte pin);
    boolean handleSysex(byte command, byte argc, byte* argv);
    void reset();
  private:
    int num_pixels;
    Adafruit_NeoPixel *pixels = new Adafruit_NeoPixel(2, 13, NEO_GRB + NEO_KHZ800);

};


/*
 * NeoPixelFirmata.cpp
 * Copied here as a hack to avoid having to include Servo.h in all sketch files that
 * include ConfigurableFirmata.h
 */


NeoPixelFirmata::NeoPixelFirmata()
{

}


boolean NeoPixelFirmata::handlePinMode(byte pin, int mode)
{
  return true;
}

void NeoPixelFirmata::handleCapability(byte pin)
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

boolean NeoPixelFirmata::handleSysex(byte command, byte argc, byte* argv)
{
  byte param1 = argv[0]; // SUBCOMMAND

  if (command == PIXEL_COMMAND) {
      if (argc > 0) {
          // maybe bounce the first command off here.
          if(param1 == PIXEL_CONFIG) {
            int num  = (argv[1] & 0x7F) | ((argv[2] & 0x7F) << 7);
            int pin     = (argv[3] & 0x7F) | ((argv[4] & 0x7F) << 7);
            Adafruit_NeoPixel *p = new Adafruit_NeoPixel(num, pin, NEO_GRB + NEO_KHZ800);
            this->num_pixels = num;
            pixels = p;
            pixels->begin();
            pixels->setBrightness(30);
          } else 
          if(param1 == PIXEL_SHOW) {
            pixels->show();             
          } else 
          if(param1 == PIXEL_SET_PIXEL) {
            uint16_t index = (uint16_t)argv[1] + ((uint16_t)argv[2]<<7);
            uint32_t colour = (uint32_t)argv[3] + ((uint32_t)argv[4]<<7) +
                ((uint32_t)argv[5]<<14) + ((uint32_t)argv[6] << 21);
            byte red, green, blue;
            red = colour >> 16; 
            green = (colour & 0x00ff00) >> 8;
            blue = (colour & 0x0000ff);
            pixels->setPixelColor(index, pixels->Color(red, green, blue));
            pixels->show();      
          } else 
          if(param1 == PIXEL_SET_STRIP) {
            uint32_t colour = (uint32_t)argv[1] + ((uint32_t)argv[2]<<7) +
                ((uint32_t)argv[3]<<14) + ((uint32_t)argv[4] << 21);
            byte red, green, blue;
            red = colour >> 16; 
            green = (colour & 0x00ff00) >> 8;
            blue = (colour & 0x0000ff);
            for(int i = 0; i <= this->num_pixels; i++) {
              pixels->setPixelColor(i, pixels->Color(red, green, blue));
            }
            pixels->show();     
          }

          return true;
      }
    }
  return false;
}

void NeoPixelFirmata::reset()
{

}

#endif /* NeoPixelFirmata_h */
