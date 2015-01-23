/*
 * @File: Timestamp.cpp
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

#include "Timestamp.h"

Timestamp::Timestamp(byte _d, byte _m, int _y, byte _h, byte _mm, byte _s, int _c):
    _day(_d),_month(_m),_year(_y),
    _hour(_h),_minute(_mm),_second(_s),
    _counter(_c)
{

}

Timestamp::Timestamp():
_day(0),_month(0),_year(0),
_hour(0),_minute(0),_second(0),
_counter(0)
{

}
byte Timestamp::day()
{
    return _day;
}

byte Timestamp::month()
{
    return _month;
}

int Timestamp::year()
{
    return _year;
}

byte Timestamp::hour()
{
    return _hour;
}

byte Timestamp::minute()
{
    return _minute;
}

byte Timestamp::second()
{
    return _second;
}

int Timestamp::counter()
{
    return _counter;
}
