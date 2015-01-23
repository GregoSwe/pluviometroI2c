/*
 * @File: Timestamp.h
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

#ifndef TIMESTAMP_h
#define TIMESTAMP_h

#include <Arduino.h>

class Timestamp
{
private:
    byte _day;
    byte _month;
    int _year;
    byte _hour;
    byte _minute;
    byte _second;
    int _counter;
public:
    Timestamp(byte _d,byte _m,int _y,byte _h,byte _mm,byte _s,int _c);
    Timestamp();
     byte day();
     byte month();
     int year();
     byte hour();
     byte minute();
     byte second();
     int counter();
};

#endif
