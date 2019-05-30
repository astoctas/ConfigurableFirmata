#ifndef InterfazFirmata_h
#define InterfazFirmata_h

#include "utility/FirmataInterfaces.h"
#include "InterfazL293DFirmata.h"
#include <AccelStepperFirmata.h>
#include "FirmataFeature.h"

#define SERVO_ATTACH            0x01 // attach a servo
#define SERVO_WRITE            0x02 // write to servo motor


class InterfazFirmata : public FirmataFeature
{
  public:
    boolean handlePinMode(byte pin, int mode);
    void handleCapability(byte pin);
    boolean handleSysex(byte command, byte argc, byte *argv);
    void reset();

    void initSteppers();
    void initDC();
    void initServos();
    void initDigitalInputs();
};

#endif