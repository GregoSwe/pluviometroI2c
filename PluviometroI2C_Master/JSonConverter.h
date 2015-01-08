#ifndef JSONCONVERTER_h
#define JSONCONVERTER_h

#include "Converter.h"
#include<Arduino.h>
#include<WProgram.h>

class JsonConverter : public Converter
{
private:
    String addValue(String _name, String  _value);

public:

   String convertToJson(byte* _compressedByte, int _howMany);
};

#endif
