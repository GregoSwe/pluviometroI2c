/*
 * @File: SlaveInterface.cpp
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

#include "SlaveInterface.h"
 TimestampContainer SlaveInterfaceClass::requireTimestamp()
{

   int timestamps = SCH.requireNewTimestamp(slaveAddress)/6; // requireNewTimestamp ritorna il numero di byte che sono richiesti per i timestamp, dividendo per 6 ho il numero di timestamp
   byte* rawByte = SCH.getNewTimestamp(slaveAddress,false);

    return TimestampContainer(rawByte,timestamps);
 }

 int SlaveInterfaceClass::resetMemory()
 {
     return SCH.requireDeleteMemory(slaveAddress);
 }

SlaveInterfaceClass::SlaveInterfaceClass(byte _add):
    slaveAddress(_add)
{

}

void SlaveInterfaceClass::setSlaveAddress(int _newAddress)
{
    slaveAddress = _newAddress;
}



SlaveInterfaceClass SlaveInterface = SlaveInterfaceClass(2);
