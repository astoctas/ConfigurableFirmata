// ensure this library description is only included once
#ifndef FirmataL239D_h
#define FirmataL293D_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// library interface description
class FirmataL293D
{
  public:
    FirmataL293D(
                   byte pin1 = 2,
                   byte pin2 = 3,
                   byte pin3 = 4
                   );

    enum Direction
    {
      CCW = 0,
      CW = 1
    };

    byte version(void);

		void turnOn();
		void turnOff();
		void brake(int release = 100);
		void invert();
		void setDirection(uint8_t dir);
		void setSpeed(uint8_t _speed);

  private:
    bool running;
    byte direction; // Direction of rotation
    byte speed; // Speed of rotation

    // motor pin numbers:
    byte motor_enable;
    byte motor_in_1;
    byte motor_in_2;

};

#endif
