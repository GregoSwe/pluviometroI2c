#include "Timestamp.h"

Timestamp::Timestamp(byte _d, byte _m, int _y, byte _h, byte _mm, byte _s, int _c):
    _day(_d),_month(_m),_year(_y),
    _hour(_h),_minute(_mm),_second(_s),
    _counter(_c)
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
