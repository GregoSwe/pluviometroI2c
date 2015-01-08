#include "JSonConverter.h"

String JsonConverter::addValue(String _name, String _value)
{
  return String ( String("\"")+_name+String("\": \"")+_value+String("\""));
}






String JsonConverter::convertToJson(byte *_compressedByte, int _howMany)
{
    int integerNumb = (_howMany/6)*7;
    int *decompressInformation = new int [integerNumb];

    for(int i = 0; i<_howMany/6;i++)  // per ogni sestupla di byte recupero le informazioni decompresse e le converto in una settupla di interi
        decompress((_compressedByte+i*6),(decompressInformation+i*7));
    delete [] _compressedByte;

    String jsonString = "";
    for(int i = 0; i<integerNumb/7;i++) // per ogni settupla di valori decompressi aggiungo alla stringa gli interi trasformati in Json
    {
      jsonString += "{";
      jsonString += addValue("day",String(decompressInformation[i*7]));
      jsonString += ",";
      jsonString += addValue("month",String(decompressInformation[i*7+1]));
      jsonString += ",";
      jsonString += addValue("year",String(2000+decompressInformation[i*7+2]));
      jsonString += ",";
      jsonString += addValue("hour",String(decompressInformation[i*7+3]));
      jsonString += ",";
      jsonString += addValue("minute",String(decompressInformation[i*7+4]));
      jsonString += ",";
      jsonString += addValue("second",String(decompressInformation[i*7+5]));
      jsonString += ",";
      jsonString += addValue("count",String(decompressInformation[i*7+6]));
      jsonString+= "}";
    }
    delete [] decompressInformation;
    return jsonString;
}
