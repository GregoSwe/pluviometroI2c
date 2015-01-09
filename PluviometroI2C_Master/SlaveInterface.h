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
    TimestampContainer requireTimestamp(); // ritorna un TimestampContainer con tutti i timestamp non ancora letti
    int resetMemory(); // richiede la cancellazione della memoriadella scheda slave il ripristino dei contatori, ritorna il numero di byte che sono stati cancellati
    SlaveInterfaceClass(byte _add);
    void setSlaveAddress(int _newAddress);
};

extern SlaveInterfaceClass SlaveInterface;

#endif
