#ifndef TIMESTAMPCONTAINER_h
#define TIMESTAMPCONTAINER_h

#include "Converter.h"
#include "Timestamp.h"

class TimestampContainer : public Converter
{
private:
    Timestamp* timestampArray; // array di timestamp
    int sizeOf;       // identifica il numero di timestamp che sono contenuti nel container

public:
    TimestampContainer(byte * _rawByte, int _size);
    Timestamp value(int i);
    Timestamp &get(int i);
    int size();
   ~TimestampContainer();
};

#endif
