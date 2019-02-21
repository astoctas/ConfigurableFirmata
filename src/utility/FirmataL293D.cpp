#include "FirmataL293D.h"

FirmataL293D::FirmataL293D(
                               byte pin1,
                               byte pin2,
                               byte pin3
                               )
{
  this->direction = 0;      // motor direction
  this->speed = 255;      // max speed
  this->running = false;

  this->motor_enable = pin1;
  this->motor_in_1 = pin2;
  this->motor_in_2 = pin3;

  // setup the pins on the microcontroller:
  pinMode(this->motor_enable, OUTPUT);
  pinMode(this->motor_in_1, OUTPUT);
  pinMode(this->motor_in_2, OUTPUT);

}

	void FirmataL293D::turnOn() {
		analogWrite(this->motor_enable, speed);
		digitalWrite(this->motor_in_1, direction);
		digitalWrite(this->motor_in_2, !direction);
		running = true;
	}

	void FirmataL293D::turnOff() {
		analogWrite(this->motor_enable, LOW);
		running = false;
	}

	void FirmataL293D::brake(int release) {
		if (running) {
			analogWrite(this->motor_enable, HIGH);
			digitalWrite(this->motor_in_1, HIGH);
			digitalWrite(this->motor_in_2, HIGH);
			delay(release);
			turnOff();
		}
	}

	void FirmataL293D::setDirection(uint8_t dir) {
		if (dir > 1) dir = 1;
		direction = dir;
		if (running) turnOn();
	}

	void FirmataL293D::setSpeed(uint8_t _speed) {
		speed = _speed;
		if (running) turnOn();
	}

	void FirmataL293D::invert() {
		direction = !direction;
		if (running) turnOn();
	}

/**
 * @return The version number of this library.
 */
byte FirmataL293D::version(void)
{
  return 1;
}
