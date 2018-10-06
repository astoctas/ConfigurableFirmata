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

/* LCD STRINGS */

#define MSG_STEPPER_STEP  "PAP %d %dp"
#define MSG_SERVO_WRITE   "Servo %d %d"
#define MSG_DC_ON              "DC %d ENCENDIDO"
#define MSG_DC_OFF             "DC %d APAGADO"
#define MSG_DC_INVERSE     "DC %d INVERTIR"
#define MSG_DC_BRAKE        "DC %d FRENADO"
#define MSG_DC_DIR             "DC %d DIR %d"
#define MSG_DC_SPEED        "DC %d POT %d%%"

// Arduino Duemilanove, Diecimila, and NG
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
// Wiring (and board)
#elif defined(WIRING)
// old Arduinos
#elif defined(__AVR_ATmega8__)
// Arduino Mega
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	struct dc_pins {
			byte enable, in1, in2;
	};
		struct stepper_pins {
			byte step, dir;
			byte enable;
			byte invert;
		};
		struct servo_pins {
			byte pin;
		};

#define MAX_DC_OUTPUTS  8
#define MAX_STEPPERS  3
#define MAX_SERVO_MOTORS  3
    static  dc_pins DCOutputs[MAX_DC_OUTPUTS] = {
      { 2,22,23 },
      { 3,24,25 },
      { 4,26,27 },
      { 5,28,29 },
      { 6,30,31 },
      { 7,32,33 },
      { 8,34,35 },
      { 9,36,37 }
    };
    static   stepper_pins StepperOutputs[MAX_STEPPERS] = {
      { 38,39,40,0b00010000 },
      { 41,42,43,0b00010000 },
      { 44,45,46,0b00010000 }
    };
    static   servo_pins ServoOutputs[MAX_SERVO_MOTORS] = {
      {10},
      {11},
      {12}
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
