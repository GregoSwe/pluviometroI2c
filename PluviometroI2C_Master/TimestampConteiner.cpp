#include "TimestampConteiner.h"


TimestampContainer::TimestampContainer(byte *_rawByte, int _size):
    sizeOf(_size),array(new Timestamp[_size])
{
    for(int i = 0; i < sizeOf; i++)
    {
        int dValues[7];
        decompress((_rawByte+i*6),dValues);
        (array+i) = new Timestamp(dValues[0],dValues[1],dValues[2],dValues[3],dValues[4],dValues[5],dValues[6]);

    }
    delete [] _rawByte;
}

Timestamp TimestampContainer::value(int i) // ritorna il valore
{
    return *(array + i);
}

Timestamp &TimestampContainer::get(int i) // ritorna il riferimento dell'oggetto
{
    return *(array +i);
}

int TimestampContainer::size()
{
    return sizeOf;
}

TimestampContainer::~TimestampCounter()
{
    delete [] array;
}
