#include "JSonConverter.h"

String JsonConverter::addValue(String _name, const String & _value)
{
  return String ( String("\"")+_name+String("\": \"")+_value+String("\""));
}


int JsonConverter::get_info(byte *_byteArray, int _type)
{

    //inizializzo i byte recuperando le informazioni dall'array
    byte firstByte = _byteArray[0];
    byte secondByte = _byteArray[1];
    byte thirdByte = _byteArray[2];
    byte fourthByte = _byteArray[3];
    byte fithByte = _byteArray[4];
    byte sixthByte = _byteArray[5];
    int unsigned outcome = 0;

    switch(_type)
    {
    case 0:

        outcome = firstByte & B00011111;
        break;  // ritorno il byte mascherando gli utimi tre bit (che non mi servono)

    case 1 :

        firstByte = (unsigned byte)(firstByte & B11100000)  >> 5;
        secondByte = (secondByte & B00000001) << 3;
        outcome = firstByte + secondByte;
        break;

    case 2 :

        outcome =  (unsigned byte) secondByte  >> 1;
        outcome += 2000;
        break;

    case 3 :

        outcome = thirdByte & B00011111;
        break;

    case 4 :

        thirdByte =  (unsigned byte) thirdByte >> 5;
        fourthByte =  (fourthByte & B00000111) << 3 ;
        outcome = thirdByte + fourthByte;
        break;

    case 5 :

        fourthByte = (unsigned byte) fourthByte  >> 3;
        fithByte = (fithByte & B00000001) << 5;
        outcome = fourthByte + fithByte;
        break;

    case 6 :

        fithByte = (unsigned byte) fithByte  >> 1;
        outcome = ((outcome + sixthByte) << 7) + fithByte;
        ;
        break;
    }
    return outcome;

}

void JsonConverter::decompress(byte * _compressedByte, int * _integerArray)
{

  _integerArray[0] = get_info(_compressedByte, DAY);
  _integerArray[1] = get_info(_compressedByte, MONTH);
  _integerArray[2] = get_info(_compressedByte, YEAR);
  _integerArray[3] = get_info(_compressedByte, HOUR);
  _integerArray[4] = get_info(_compressedByte, MINUTE);
  _integerArray[5] = get_info(_compressedByte, SECOND);
  _integerArray[6] = get_info(_compressedByte, COUNTER);
}

String JsonConverter::convertToJson(byte *_compressedByte, int _howMany)
{
    int integerNumb = (_howMany/6)*7;
    int *decompressInformation = new int [integerNumb];

    for(int i = 0; i<_howMany/6;i++)  // per ogni sestupla di byte recupero le informazioni decompresse e le converto in una settupla di interi
        decompress((_compressedByte+i*6),(decompressInformation+i*7));
    delete [] _compressedByte;

    String JsonString = "";
    for(int i = 0; i<integerNumb/7;i++) // per ogni settupla di valori decompressi aggiungo alla stringa gli interi trasformati in Json
    {
      jsonString += "{";
      jsonString += addFild("day",String(d[i*7]));
      jsonString += ",";
      jsonString += addFild("month",String(d[i*7+1]));
      jsonString += ",";
      jsonString += addFild("year",String(2000+d[i*7+2]));
      jsonString += ",";
      jsonString += addFild("hour",String(d[i*7+3]));
      jsonString += ",";
      jsonString += addFild("minute",String(d[i*7+4]));
      jsonString += ",";
      jsonString += addFild("second",String(d[i*7+5]));
      jsonString += ",";
      jsonString += addFild("count",String(d[i*7+6]));
      jsonString+= "}";
    }
    delete [] decompressInformation;
    return JsonString;
}
