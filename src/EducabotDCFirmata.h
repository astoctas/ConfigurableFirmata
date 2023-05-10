#ifndef EducabotDCFirmata_h
#define EducabotDCFirmata_h

#include <ConfigurableFirmata.h>
#include "utility/FirmataInterfaces.h"
#include "FirmataFeature.h"

#define L293D_DATA            0x02 // control a dc motor

#define L293D_CONFIG 0
#define L293D_ON 1
#define L293D_OFF 2
#define L293D_BRAKE 3
#define L293D_INVERSE 4
#define L293D_DIR 5
#define L293D_SPEED 6

struct EducabotDC {
  int pin_ground;
  int pin_potencia;
  int direccion;
  int velocidad;
  int running;
};

class EducabotDCFirmata : public FirmataFeature
{
  public:
    boolean handlePinMode(byte pin, int mode);
    void handleCapability(byte pin);
    boolean handleSysex(byte command, byte argc, byte *argv);
    void reset();
  private:
    struct EducabotDC outputs[MAX_DC_OUTPUTS];
};

#endif
