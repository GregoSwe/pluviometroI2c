/*
 * @File: Converter.cpp
 *
 * @Creation Date: 19/DIC/2014
 *
 * @Last Update: 23/GEN/2015
 *
 * @Version: 1.0
 *
 * @Author: Gregorini Marco
 *
 * @Email: gregorini.marco91@gmail.com
 *
 * @Licence: This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include"Converter.h"

int Converter::get_info(byte *_byteArray, int _type)
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


void Converter::decompress(byte *_compressedByte, int *_integerArray)
{

    _integerArray[0] = get_info(_compressedByte, 0);
    _integerArray[1] = get_info(_compressedByte, 1);
    _integerArray[2] = get_info(_compressedByte, 2);
    _integerArray[3] = get_info(_compressedByte, 3);
    _integerArray[4] = get_info(_compressedByte, 4);
    _integerArray[5] = get_info(_compressedByte, 5);
    _integerArray[6] = get_info(_compressedByte, 6);
}
