/*
  Interfaces.h - Hardware Abstraction Layer for Firmata library

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.

*/
#include "Arduino.h"

#ifndef Firmata_Interfaces_h
#define Firmata_Interfaces_h

struct stepper_pins {
	byte enable;
};

// Arduino Duemilanove, Diecimila, and NG
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
#define MAX_STEPPERS 0
static   stepper_pins StepperEnables[MAX_STEPPERS] = {};


// Wiring (and board)
#elif defined(WIRING)
// old Arduinos
#elif defined(__AVR_ATmega8__)
// Arduino Mega
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define MAX_STEPPERS 3
  static   stepper_pins StepperEnables[MAX_STEPPERS] = {
    { 40 },
    { 43 },
    { 46 }
  };
// Arduino DUE
#elif defined(__SAM3X8E__)
// Arduino/Genuino MKR1000
#elif defined(ARDUINO_SAMD_MKR1000)
// Arduino MKRZero
#elif defined(ARDUINO_SAMD_MKRZERO)
// Arduino MKRFox1200
#elif defined(ARDUINO_SAMD_MKRFox1200)
// Arduino MKR WAN 1300
#elif defined(ARDUINO_SAMD_MKRWAN1300)
// Arduino MKR GSM 1400
#elif defined(ARDUINO_SAMD_MKRGSM1400)
// Arduino Zero
// Note this will work with an Arduino Zero Pro, but not with an Arduino M0 Pro
// Arduino M0 Pro does not properly map pins to the board labeled pin numbers
#elif defined(_VARIANT_ARDUINO_ZERO_)
// Arduino Primo
#elif defined(ARDUINO_PRIMO)
// Arduino 101
#elif defined(_VARIANT_ARDUINO_101_X_)
// Teensy 1.0
#elif defined(__AVR_AT90USB162__)
// Teensy 2.0
#elif defined(__AVR_ATmega32U4__) && defined(CORE_TEENSY)
// Teensy 3.5 and 3.6
// reference: https://github.com/PaulStoffregen/cores/blob/master/teensy3/pins_arduino.h
#elif defined(__MK64FX512__) || defined(__MK66FX1M0__)
// Teensy 3.0, 3.1 and 3.2
#elif defined(__MK20DX128__) || defined(__MK20DX256__)
// Teensy-LC
#elif defined(__MKL26Z64__)
// Teensy++ 1.0 and 2.0
#elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
// Leonardo
#elif defined(__AVR_ATmega32U4__)
// Intel Galileo Board (gen 1 and 2) and Intel Edison
#elif defined(ARDUINO_LINUX)
// RedBearLab BLE Nano with factory switch settings (S1 - S10)
#elif defined(BLE_NANO)
// Pinoccio Scout
// Note: digital pins 9-16 are usable but not labeled on the board numerically.
// SS=9, MOSI=10, MISO=11, SCK=12, RX1=13, TX1=14, SCL=15, SDA=16
#elif defined(ARDUINO_PINOCCIO)
// Sanguino
#elif defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644__)
// Illuminato
#elif defined(__AVR_ATmega645__)
// ESP8266
// note: boot mode GPIOs 0, 2 and 15 can be used as outputs, GPIOs 6-11 are in use for flash IO
#elif defined(ESP8266)
// STM32 based boards
#elif defined(ARDUINO_ARCH_STM32)
// Adafruit Bluefruit nRF52 boards
#elif defined(ARDUINO_NRF52_ADAFRUIT)
// anything else
#else
#error "Please edit Boards.h with a hardware abstraction for this board"
#endif

// as long this is not defined for all boards:



#endif /* Firmata_Interfaces_h */
