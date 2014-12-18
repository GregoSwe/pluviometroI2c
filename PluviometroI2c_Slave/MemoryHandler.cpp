#include "MemoryHandler.h"


MemoryHandlerClass::MemoryHandlerClass() :
    MEMORYADD(0x50),RTCADD(0x68),MAXMEMORY(32768),
    currentPosition(0),
    timestampCount(0),
    lastTimestampPosition(0)
{
    MAXSTACK = MAXMEMORY/6;
    setCounters();
}

/*
 *   in  -> int * _params è un puntatore ad un array completamente vuoto di dim = 6
 *   out -> _params contiene dei valori numerici che corrispondono a -> {giorno,mese,anno,ore,minuti,secondi}
 */
void MemoryHandlerClass::ask_time(int *_params)
{
    Wire.beginTransmission(RTCADD);
    Wire.write(0);
    Wire.endTransmission(true);
    Wire.requestFrom(RTCADD, 7);
    int second = bcdToDec(Wire.read());
    int minute = bcdToDec(Wire.read());
    int hour = bcdToDec(Wire.read());
    int weekday = bcdToDec(Wire.read());
    int monthday = bcdToDec(Wire.read());
    int month = bcdToDec(Wire.read());
    int year = bcdToDec(Wire.read());

    _params[0] = monthday;
    _params[1] = month;
    _params[2] = year;
    _params[3] = hour;
    _params[4] = minute;
    _params[5] = second;
}

// Funzione che recupera dalla memoria del microprocessore le informazioni salvate in esso.
/*
 *  currentPosition -> contatore che ci dice la posizione da cui iniziare a salvare i timestamp
 *  timestampCount  -> contatore che ci dice quanti timestamp sono stati inseriti dall'ultima lettura
 *  lastTimestampPosition -> contatore che ci dice la posizione dell'ultimo timestamp inviato
 */
void MemoryHandlerClass::setCounters()
{
    // inizializzo il contatore che identifica la posizione dell'ultimo timestamp inserito
    byte firstByte = EEPROM.read(0);
    byte secondByte = EEPROM.read(1);



    int valTem = 0;
    valTem += secondByte;
    valTem = valTem << 8;
    valTem += firstByte;
    currentPosition = valTem;

    // inizializzo il contatore che identifica il numero di timestamp inseriti dall'ultima lettura
    firstByte = EEPROM.read(4);
    secondByte =EEPROM.read(5);

    valTem = 0;
    valTem += secondByte;
    valTem = valTem << 8;
    valTem += firstByte;
    timestampCount = valTem;
    // inizializzo il contatore che identifica la posizione dell'ultimo timestamp inviato
    firstByte = EEPROM.read(6);
    secondByte = EEPROM.read(7);
    valTem = 0;
    valTem += secondByte;
    valTem = valTem << 8;
    valTem += firstByte;
    lastTimestampPosition = valTem;
}



// I valori numerici contenuti in _array vengono salvati all'interno di _compressedValue in un formato compresso che ottimizza l'utilizzo di memoria
void MemoryHandlerClass::compressInformation(byte *_compressedValue, int *_array)
{
    byte day = _array[0];
    byte month = _array[1];
    byte year = _array[2];
    byte hour = _array[3];
    byte minute = _array[4];
    byte second = _array[5];

    _compressedValue[0] = day + (month << 5);                               // ~ 1°byte |m||m||m||d||d||d||d||d|
    //    prendo i 5 bit per salvare day e li salvo in firstByte + i primi tre bit di month, shiftati di 5 posizioni a sinistra
    _compressedValue[1] = ((byte) month  >> 3) + (year << 1);               // ~ 2°byte |y||y||y||y||y||y||y||m|
    //    3 shift a destra per month, cosi da prendere il 4° bit mancante + year shiftato a sinistra per fare spazio al bit di month
    _compressedValue[2] = hour + ((minute & B00000111) << 5);               // ~ 3°byte|mi||mi||mi||h||h||h||h||h|
    //    prendo i 5 bit per salvare hour e sommo i primi tre bit di minute, shiftati di 5 posizioni a sinistra
    _compressedValue[3] = ( (byte) minute  >> 3) + (second << 3);           // ~ 4°byte |s||s||s||s||s||mi||mi||mi|
    //    3 shift a destra per recuperare i 3 bit mancanti di minute e 3 shift a sinistra di second per fare spazio ai 3 bit di minute
    _compressedValue[4] = ((byte)second  >> 5) + (timestampCount << 1);     // ~ 5°byte |c||c||c||c||c||c||c||s|
    //    recupero il bit mancante da secondi e ci aggiungo i primi 7 bit di timestampCount
    _compressedValue[5] = (byte)(timestampCount >> 7) & B01111111;          // ~ 6°byte |c||c||c||c||c||c||c||c|
    //     recupero gli ultimi 8 bit restanti, faccio uno shift di 7 posizioni per avere tutto in un byte e salvo nel sesto byte
}
void MemoryHandlerClass::updateCounter(int _oldValue,int _newValue,int _type)
{
    int firstByteAdd = 0;
    int secondByteAdd = 0;

    switch (_type)
    {
    case CURRENT_POSITION:
        firstByteAdd = 0;
        secondByteAdd = 1;
        break;

    case TIMESTAMP_COUNTER:
        firstByteAdd = 4;
        secondByteAdd = 5;
        break;

    case LAST_POSITION:
        firstByteAdd = 6;
        secondByteAdd = 7;
        break;
    }
    byte firstOldByteValue = _oldValue;        // prendi i primi 8 bit del vecchio valore
    byte secondOldByteValue = _oldValue >> 8;  // prendo i secondi 8 bit del vecchio valore

    byte firstNewByteValue = _newValue;       // prendo i primi 8 bit del nuovo valore
    byte secondNewByteValue = _newValue >> 8; // prendo i secondi 8 bit del nuovo valore

    if(firstNewByteValue != firstOldByteValue)  // verifico che i nuovi 8 bit sono diversi da quelli vecchi
        EEPROM.write(firstByteAdd,firstNewByteValue);   // se sono diversi li salvo

    if(secondNewByteValue != secondOldByteValue) // verifico che i nuovi 8 bit siano diversi da quelli vecchi
        EEPROM.write(secondByteAdd,secondNewByteValue);    // se sono diversi li salvo


}
int MemoryHandlerClass::incrementCounters()
{
    int index = currentPosition;

    //incremento e salvo currentPosition
    updateCounter(currentPosition,currentPosition+1,CURRENT_POSITION);
    currentPosition++;
    // incremento e salvo timestampCount
    updateCounter(timestampCount,timestampCount+1,TIMESTAMP_COUNTER);
    timestampCount++;

    return index;
}

byte MemoryHandlerClass::bcdToDec(byte _val)
{
    return ((_val/16*10) + (_val%16));
}

int MemoryHandlerClass::getInfo(int _position, int _type)
{
    int  realPosition =  _position * 6; // la posizione dell'indirizzo fisico della prima unità logica di dati salvati
    byte firstByte = 0;
    byte secondByte = 0;
    byte thirdByte = 0;
    byte fourthByte = 0;
    byte fithByte = 0;
    byte sixthByte = 0;
    int outcome = 0;

    switch(_type)
    {
    case DAY:

        firstByte = readEEPROM(realPosition);
        outcome = firstByte & 00011111;
        break;  // ritorno il byte mascherando gli utimi tre bit (che non mi servono)

    case MONTH :

        firstByte = readEEPROM(realPosition);
        secondByte = readEEPROM(realPosition + 1);
        firstByte = (unsigned byte) (firstByte & B11100000)  >> 5;
        secondByte = (secondByte & B00000001) << 3;
        outcome = firstByte + secondByte;
        break;

    case YEAR :

        secondByte = readEEPROM(realPosition + 1);
        outcome = (unsigned byte) secondByte  >> 1;
        outcome += 2000;
        break;

    case HOUR :

        thirdByte = readEEPROM(realPosition + 2);
        outcome = thirdByte & B00011111;
        break;

    case MINUTE :

        thirdByte = readEEPROM(realPosition + 2);
        fourthByte = readEEPROM(realPosition + 3);
        thirdByte = (unsigned byte) thirdByte  >> 5 ;
        fourthByte =  (fourthByte & B00000111) << 3 ;
        outcome = thirdByte + fourthByte;
        break;

    case SECOND :

        fourthByte = readEEPROM(realPosition + 3);
        fithByte = readEEPROM(realPosition + 4);
        fourthByte = (unsigned byte) fourthByte  >> 3;
        fithByte = (fithByte & B00000001) << 5;
        outcome = fourthByte + fithByte;
        break;

    case COUNTER :

        fithByte = readEEPROM(realPosition + 4);
        sixthByte = readEEPROM(realPosition + 5);
        fithByte = (unsigned byte) fithByte  >> 1;
        outcome = ((outcome + sixthByte) << 7) + fithByte;
        break;
    }
    return outcome;
}

int MemoryHandlerClass::getInfo(byte *_byteArray, int _type)
{
    byte firstByte = _byteArray[0];
    byte secondByte = _byteArray[1];
    byte thirdByte = _byteArray[2];
    byte fourthByte = _byteArray[3];
    byte fithByte = _byteArray[4];
    byte sixthByte = _byteArray[5];
    int unsigned outcome = 0;

    switch(_type)
    {
    case DAY:

        outcome = firstByte & B00011111;
        break;  // ritorno il byte mascherando gli utimi tre bit (che non mi servono)

    case MONTH :

        firstByte = (unsigned byte)(firstByte & B11100000)  >> 5;
        secondByte = (secondByte & B00000001) << 3;
        outcome = firstByte + secondByte;
        break;

    case YEAR :

        outcome =  (unsigned byte) secondByte  >> 1;
        outcome += 2000;
        break;

    case HOUR :

        outcome = thirdByte & B00011111;
        break;

    case MINUTE :

        thirdByte =  (unsigned byte) thirdByte >> 5;
        fourthByte =  (fourthByte & B00000111) << 3 ;
        outcome = thirdByte + fourthByte;
        break;

    case SECOND :

        fourthByte = (unsigned byte) fourthByte  >> 3;
        fithByte = (fithByte & B00000001) << 5;
        outcome = fourthByte + fithByte;
        break;

    case COUNTER :

        fithByte = (unsigned byte) fithByte  >> 1;
        outcome = ((outcome + sixthByte) << 7) + fithByte;
        ;
        break;
    }
    return outcome;
}

byte MemoryHandlerClass::decToBcd(byte _val)
{
    return ((_val/10*16) + (_val%10));
}

void MemoryHandlerClass::storeTimestamp()
{

    int timeInformation[6] = {}; // inizializzo un array vuoto che conterrà la data con l'ora recuperata dalla RTC
    ask_time(timeInformation);


    byte valuesToStore[6] = {};

    compressInformation(valuesToStore,timeInformation);      // funzione che comprime le informazioni nel formato indicato di _array in valuesStored -> valuesToStore conterrà i valori compressi in 6byte


    int unsigned storeIndex = incrementCounters();  // ritorna l'indice di memoria in cui salvare il prossimo timestamp incremento delle variabili di controllo dei vari contatori


    //ciclo for in cui vengono salvati i 6 byte consecutivamente
    for(int i = 0; i < 6; i++)
        writeEEPROM(storeIndex*6 + i , valuesToStore[i]);

}

// funzione che ritorna il numero di timestamp non ancora letti (timestamp, non byte. Byte = timestampCount * 6)
int MemoryHandlerClass::newTimestamp()
{
    return timestampCount;
}

byte *MemoryHandlerClass::getNewTimestamp(bool _letUnread = false)
{


        /*
         *  Eseguo il for a partire da "lastTimestampPosition" per timestampCount*6, poichè per ogni timestamp ci sono 6 byte da leggere e salvare
         *  i per scorrere la memoria, j per scorrere l'array
         *  j[0,timestampCount*6-1] ; i[lastTimestampPosition,lastTimestampPosition + timestampCount*6 -1]
         */

   /* for(int i = lastTimestampPosition,j=0; i< lastTimestampPosition + timestampCount*6; i++,j++ )
        byteToReturn[j] = readEEPROM(i);*/

    byte * byteToReturn = getMemory(lastTimestampPosition*6,currentPosition*6);

    if(_letUnread == false) // se la booleana è falsa allora i timestamp letti verranno segnati come già letti e i contatori di conseguenza aggiornati
    {

        updateCounter(timestampCount,0,TIMESTAMP_COUNTER); // salvo in memoria il nuovo valore del contatore
        timestampCount = 0;

        updateCounter(lastTimestampPosition,currentPosition,LAST_POSITION); // salvo in memoria il nuovo valore del contatore
        lastTimestampPosition = currentPosition;
    }
    return byteToReturn;
}

byte *MemoryHandlerClass::getNewTimestamp(int _from, int _howmany, bool _letUnread)
{
    byte* byteToReturn = getMemory(lastTimestampPosition*6+_from,lastTimestampPosition*6+_from+_howmany);
    if(_letUnread == false) // se la booleana è falsa allora i timestamp letti verranno segnati come già letti e i contatori di conseguenza aggiornati
    {

        updateCounter(timestampCount,0,TIMESTAMP_COUNTER); // salvo in memoria il nuovo valore del contatore
        timestampCount = 0;

        updateCounter(lastTimestampPosition,currentPosition,LAST_POSITION); // salvo in memoria il nuovo valore del contatore
        lastTimestampPosition = currentPosition;
    }
    return byteToReturn;
}

void MemoryHandlerClass::checkInterrupt()
{
    if(interrupted == true)
    {
        interrupted = false;
        storeTimestamp();
    }
}

void MemoryHandlerClass::interrupt()
{
    interrupted = true;
}

int MemoryHandlerClass::eraseMemory()
{
    int byteErased = currentPosition * 6;
    for (int i = 0; i < byteErased; i++)
        writeEEPROM(i,255);
    updateCounter(currentPosition,0,CURRENT_POSITION);
    currentPosition = 0;
    updateCounter(lastTimestampPosition,0,LAST_POSITION);
    lastTimestampPosition = 0;
    updateCounter(timestampCount,0,TIMESTAMP_COUNTER);
    timestampCount = 0;

    return byteErased;
}

void MemoryHandlerClass::printC()
{
    Serial.println("#####");
    Serial.print("Current Position = ");Serial.println(currentPosition);
    Serial.print("last Time stamp Position = ");Serial.println(lastTimestampPosition);
    Serial.print("time stamp counter = ");Serial.println(timestampCount);
    Serial.println(" ~~~~~ ");
}

void MemoryHandlerClass::writeEEPROM(unsigned int eeaddress, byte data )
{

    Wire.beginTransmission(MEMORYADD);
    Wire.write((int)(eeaddress >> 8));   // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.write(data);
    Wire.endTransmission(true);

    delay(5);
}

byte MemoryHandlerClass::readEEPROM(unsigned int eeaddress )
{
    byte rdata = 0xFF;
    
    Wire.beginTransmission(MEMORYADD);
    Wire.write((int)(eeaddress >> 8));   // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission(true);

    Wire.requestFrom(MEMORYADD,1);

    if (Wire.available())
        rdata = Wire.read();
    

    return rdata;
}

int MemoryHandlerClass::memoryUsed()
{
    return currentPosition * 6;
}

byte *MemoryHandlerClass::getMemoryUsed()
{
    return getMemory(0,currentPosition*6);
}

byte *MemoryHandlerClass::getMemoryUsed(int _from, int _howMany)
{
    return getMemory(_from,_from+_howMany);
}

byte *MemoryHandlerClass::getMemory(int _from, int _to)
{
    byte* byteToReturn = new byte[_to - _from];
    if(_from>_to)
        return 0;


    for(int i = _from , j = 0; i < _from + _to;i++,j++)
    {
        byteToReturn[j] = readEEPROM(i);
    }

    return byteToReturn;
}

MemoryHandlerClass MemoryHandler = MemoryHandlerClass();



