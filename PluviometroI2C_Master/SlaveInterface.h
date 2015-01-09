#ifndef SLAVEINTERFACE_h
#define SLAVEINTERFACE_h

#include <Arduino.h>
#include "TimestampConteiner.h"
#include "SlaveComunicationHandler.h"

class SlaveInterfaceClass
{
private:
    SlaveComunicationHandler SCH;
    byte slaveAddress;
public:
    TimestampContainer requireTimestamp();
    SlaveInterfaceClass(byte _add);
    void setSlaveAddress(int _newAddress);
};

extern SlaveInterfaceClass SlaveInterface;

#endif
