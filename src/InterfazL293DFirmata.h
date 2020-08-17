#ifndef InterfazL293DFirmata_h
#define InterfazL293DFirmata_h

#include <ConfigurableFirmata.h>
#include "utility/FirmataL293D.h"
#include "utility/FirmataInterfaces.h"
#include "FirmataFeature.h"

// #define MAX_OUTPUTS 8 // arbitrary value... may need to adjust
#define L293D_CONFIG 0
#define L293D_ON 1
#define L293D_OFF 2
#define L293D_BRAKE 3
#define L293D_INVERSE 4
#define L293D_DIR 5
#define L293D_SPEED 6

class InterfazL293DFirmata : public FirmataFeature
{
  public:
    boolean handlePinMode(byte pin, int mode);
    void handleCapability(byte pin);
    boolean handleSysex(byte command, byte argc, byte *argv);
    void reset();
  private:
    FirmataL293D *outputs[MAX_DC_OUTPUTS];
    byte numOutputs;
};

#endif
