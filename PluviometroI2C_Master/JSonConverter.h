#ifndef JSONCONVERTER_h
#define JSONCONVERTER_h

#include<Arduino.h>

class JsonConverter
{
private:
    String addValue(String _name, const & String  _value);
    int get_info(byte* _byteArray,int _type);
    void  decompress(byte * _compressedByte, int * _integerArray);
public:

   String convertToJson(byte* _compressedByte, int _howMany);
};

#endif
