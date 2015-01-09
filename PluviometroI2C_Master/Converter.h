#ifndef CONVERTER_h
#define CONVERTER_h
#include<Arduino.h>
class Converter
{
protected:
    int get_info(byte* _byteArray,int _type);
    void  decompress(byte * _compressedByte, int * _integerArray);
};

#endif
