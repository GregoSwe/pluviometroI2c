#ifndef SLAVECOMUNICATIONHANDLER_h
#define SLAVECOMUNICANTIONHANDLER_h
#include <Arduino.h>
#include <Wire.h>

class SlaveComunicationHandler
{
private:
     byte BYTERATE;

protected:
    void prepareSlaveRequest(byte _slaveAddress, byte _requestType);
    byte* requireBytes(byte _slaveAddress, byte _requestType, int _howManyBytes); // ATTENZIONE : occupa memoria nello HEAP
    int requireInteger(byte _slaveAddress, byte _requestType);
public:
    SlaveComunicationHandler();
    int requireNewTimestamp(byte _slaveAddress);
    int requireUsedMemory(byte _slaveAddress);
    int requireDeleteMemory(byte _slaveAddress);
    byte* getNewTimestamp(byte _slaveAddress, bool _letUnread);
    byte* getUsedMemory(byte _slaveAddress);

};

#endif
