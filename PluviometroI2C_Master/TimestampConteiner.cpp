/*
 * @File: TimestampContainer.cpp
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

#include "TimestampConteiner.h"


TimestampContainer::TimestampContainer(byte *_rawByte, int _size):
    sizeOf(_size),timestampArray(new Timestamp[_size])
{
    for(int i = 0; i < sizeOf; i++)
    {
        int dValues[7];
        decompress((_rawByte+i*6),dValues);
        timestampArray[i] = Timestamp(dValues[0],dValues[1],dValues[2],dValues[3],dValues[4],dValues[5],dValues[6]);

    }
    delete [] _rawByte;
}

Timestamp TimestampContainer::value(int i) // ritorna il valore
{
    return *(timestampArray + i);
}

Timestamp &TimestampContainer::get(int i) // ritorna il riferimento dell'oggetto
{
    return *(timestampArray +i);
}

int TimestampContainer::size()
{
    return sizeOf;
}

TimestampContainer::~TimestampContainer()
{
    delete [] timestampArray;
}
