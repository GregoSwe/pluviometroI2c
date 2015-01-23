/*
 * @File: MasterComunicationHandler.h
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

#ifndef MASTERCOMUNICATIONHANDLERCLASS_h
#define MASTERCOMUNICATIONHANDLERCLASS_h

#include <Arduino.h>
#include "ActionSendInteger.h"
#include "ActionSendMemory.h"
#include "MemoryHandler.h"

class MasterComunicationHandlerClass
{
private:

    //ATTRIBUTI
    byte requestType;
    AbstractAction* action;
    unsigned int buffer;
    unsigned int MAXRAM;
    //FUNZIONI
    void sendBytes(byte* _bytes,int _howMany);
    void sendInteger(int _integer);
public:

    MasterComunicationHandlerClass();
    void selectAction(byte _actionType);
    void prepareAction();
    void executeAction();
};

extern MasterComunicationHandlerClass MasterHandler;
#endif
