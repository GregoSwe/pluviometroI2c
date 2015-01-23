/*
 * @File: TimestampContainer.h
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
