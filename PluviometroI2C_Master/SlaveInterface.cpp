#include "SlaveInterface.h"
const TimestampContainer &SlaveInterfaceClass::requireTimestamp() const
{
    byte* rawByte = SCH.getNewTimestamp(slaveAddress,false);
    int timestamps = SCH.requireNewTimestamp(slaveAddress)/6; // requireNewTimestamp ritorna il numero di byte che sono richiesti per i timestamp, dividendo per 6 ho il numero di timestamp
    return TimestampContainer(rawByte,timestamps);
}

SlaveInterfaceClass::SlaveInterfaceClass(byte _add):
    slaveAddress(_add)
{

}

void SlaveInterfaceClass::setSlaveAddress(int _newAddress)
{
    slaveAddress = _newAddress;
}



SlaveInterfaceClass SlaveInterface = SlaveInterfaceClass(2);