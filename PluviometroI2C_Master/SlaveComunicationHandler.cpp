#include"SlaveComunicationHandler.h"

SlaveComunicationHandler::SlaveComunicationHandler():
    BYTERATE(30)
{
}

int SlaveComunicationHandler::requireNewTimestamp(byte _slaveAddress)
{
    return requireInteger(_slaveAddress,0);
}

int SlaveComunicationHandler::requireUsedMemory(byte _slaveAddress)
{
    return requireInteger(_slaveAddress,1);
}

int SlaveComunicationHandler::requireDeleteMemory(byte _slaveAddress)
{
    return requireInteger(_slaveAddress,5);
}

byte *SlaveComunicationHandler::getNewTimestamp(byte _slaveAddress, bool _letUnread)
{
    byte requestType = 3;
    if(_letUnread == true)
        requestType = 2;

    int howManyByte = requireNewTimestamp(_slaveAddress);

    return requireBytes(_slaveAddress,requestType,howManyByte);
}

byte *SlaveComunicationHandler::getUsedMemory(byte _slaveAddress)
{
    int howManyByte = requireUsedMemory(_slaveAddress);
    Serial.print("byte richiesti : ");Serial.println(howManyByte);
    return requireBytes(_slaveAddress,4,howManyByte);
}


void SlaveComunicationHandler::prepareSlaveRequest(byte _slaveAddress, byte _requestType)
{
    Wire.beginTransmission(_slaveAddress);
    Wire.write(_requestType);
    Wire.endTransmission(true);
    delay(20);
}

byte *SlaveComunicationHandler::requireBytes(byte _slaveAddress, byte _requestType, int _howManyBytes)
{

    byte* byteToReturn = new byte[_howManyBytes];
    int index = 0;

    prepareSlaveRequest(_slaveAddress,_requestType);

    delay(100 + _howManyBytes);

    while(_howManyBytes > BYTERATE)
    {
        Wire.requestFrom((int)_slaveAddress,(int)BYTERATE);
        _howManyBytes = _howManyBytes - BYTERATE;

        while(Wire.available())
        {
            byte resoult = Wire.read();
            byteToReturn[index] = resoult;
            index ++ ;
        }
        delay(10);
    }

    if(_howManyBytes > 0)
    {
        Wire.requestFrom((int)_slaveAddress,_howManyBytes);
        while(Wire.available())
        {
            byte resoult = Wire.read();
            byteToReturn[index] = resoult;
            index ++ ;
        }
    }

    return byteToReturn;
}

int SlaveComunicationHandler::requireInteger(byte _slaveAddress, byte _requestType)
{
    int integerToReturn;
    byte resoult[2];
    byte index = 0;

    prepareSlaveRequest(_slaveAddress,_requestType);

    Wire.requestFrom((int)_slaveAddress,2);

    while(Wire.available())
    {
        resoult[index] = Wire.read();
        index ++;
    }
    integerToReturn = resoult[0];
    integerToReturn= integerToReturn << 8;
    integerToReturn= integerToReturn + resoult[1];

    return integerToReturn;
}




