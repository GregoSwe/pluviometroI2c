/*
 * @File: SlaveComunicationHandler.h
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

#ifndef SLAVECOMUNICATIONHANDLER_h
#define SLAVECOMUNICATIONHANDLER_h
#include <Arduino.h>
#include <Wire.h>

class SlaveComunicationHandler
{
private:
     byte BYTERATE;

protected:
    void prepareSlaveRequest(byte _slaveAddress, byte _requestType);
    byte* requireBytes(byte _slaveAddress, byte _requestType, int _howManyBytes); // ATTENZIONE : occupa memoria nello HEAP
    int requireInteger(byte _slaveAddress, byte _requestType);
public:
    SlaveComunicationHandler();
    int requireNewTimestamp(byte _slaveAddress);
    int requireUsedMemory(byte _slaveAddress);
    int requireDeleteMemory(byte _slaveAddress);
    byte* getNewTimestamp(byte _slaveAddress, bool _letUnread);
    byte* getUsedMemory(byte _slaveAddress);

};

#endif
