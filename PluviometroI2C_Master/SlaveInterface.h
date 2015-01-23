/*
 * @File: SlaveInterface.h
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

#ifndef SLAVEINTERFACE_h
#define SLAVEINTERFACE_h

#include <Arduino.h>
#include "TimestampConteiner.h"
#include "SlaveComunicationHandler.h"

class SlaveInterfaceClass
{
private:
    SlaveComunicationHandler SCH;
    byte slaveAddress;
public:
    TimestampContainer requireTimestamp(); // ritorna un TimestampContainer con tutti i timestamp non ancora letti
    int resetMemory(); // richiede la cancellazione della memoriadella scheda slave il ripristino dei contatori, ritorna il numero di byte che sono stati cancellati
    SlaveInterfaceClass(byte _add);
    void setSlaveAddress(int _newAddress);
};

extern SlaveInterfaceClass SlaveInterface;

#endif
