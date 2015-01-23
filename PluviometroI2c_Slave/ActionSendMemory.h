/*
 * @File: ActionSendMemory.h
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

#ifndef ACTIONSENDMEMORY_h
#define ACTIONSENDMEMORY_h
#include "AbstractAction.h"
#include <Wire.h>

class ActionSendMemory: public AbstractAction
{
private:
    byte* byteToSend;
    int howManyByte;
    const byte BYTERATE;
    byte* actualPointer;
public:
    ActionSendMemory(byte* _byteToSend,int _howManyByte, AbstractAction* _otherAction);
    //ActionSendMemory(byte *_byteToSend, int _howManyByte);
    virtual void execute();
    virtual ~ActionSendMemory();
};

#endif
