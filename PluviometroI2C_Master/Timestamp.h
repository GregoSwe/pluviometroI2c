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
     byte day();
     byte month();
     int year();
     byte hour();
     byte minute();
     byte second();
     int counter();
};

#endif
