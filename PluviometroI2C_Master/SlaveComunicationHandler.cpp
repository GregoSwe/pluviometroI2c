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

// Funzione generica che richiede dei byte allo slave secondo uno specifico protocollo
byte *SlaveComunicationHandler::requireBytes(byte _slaveAddress, byte _requestType, int _howManyBytes)
{

    byte* byteToReturn = new byte[_howManyBytes]; // inizializzo un array di byte a seconda di quanti ne ho richiesti
    int index = 0;

    prepareSlaveRequest(_slaveAddress,_requestType); // avviso lo slave della richiesta che ho intenzione di richiedere

    delay(100 + _howManyBytes); // attendo che lo slave si prepari e raccolga le informazioni che ho richiesto

    while(_howManyBytes > BYTERATE)  // finchè i byte che devo richiedere sono superiori ma massimo rate che il bus può sopportare
    {
        Wire.requestFrom((int)_slaveAddress,(int)BYTERATE); // richiedo i byte
        _howManyBytes = _howManyBytes - BYTERATE;  // ho richiesto i byte, quindi la prossima iterazione avrò BYTERATE byte in meno da richiedere

        while(Wire.available()) // recupero le informazioni e le salvo nell'array, il cui indice verrà incrementato di volta in volta
        {
            byte resoult = Wire.read();
            byteToReturn[index] = resoult;
            index ++ ;
        }
        delay(10);
    }

    if(_howManyBytes > 0) // quando arrivo qui i byte restanti da chiedere sono minori del rate massimo che il bus può sopportare, quindi procedo con la richiesta
    {
        Wire.requestFrom((int)_slaveAddress,_howManyBytes); // informo lo slave
        while(Wire.available())  // recupero i dati
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




