/*
 * @File: MasterComunicationHandler.cpp
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

#include"MasterComunicationHandler.h"

MasterComunicationHandlerClass::MasterComunicationHandlerClass()
    :action(0),requestType(255),buffer(0),MAXRAM(1200)
{
}

void MasterComunicationHandlerClass::selectAction(byte _actionType)
{
    if(requestType == 255)
    {
        requestType = _actionType;
    }
}

void MasterComunicationHandlerClass::prepareAction()
{


    if(requestType != 255)
    {
        int intToSend = 0;
        int numberOfByte = 0;
        byte* bytesToSend = 0;
        if(action != 0)
        {
            delete action;
            action = 0;
        }
        switch (requestType)
        {
        case 0: // invia un intero contenente il numero di byte da leggere
            intToSend = MemoryHandler.newTimestamp()*6;
            sendInteger(intToSend);
            break;
        case 1: // invia un intero contenente il numero di byte occupati in memoria
            intToSend = MemoryHandler.memoryUsed();
            sendInteger(intToSend);
            break;
        case 2: // invia i byte non letti e li conserva come non letti
            numberOfByte = MemoryHandler.newTimestamp()*6;
            if(intToSend > MAXRAM)
            {
                if(intToSend-buffer > MAXRAM)
                {
                    bytesToSend = MemoryHandler.getNewTimestamp(buffer,buffer+MAXRAM,true);
                    numberOfByte = MAXRAM;
                    buffer = buffer + MAXRAM;
                }
                else
                {
                    bytesToSend = MemoryHandler.getNewTimestamp(buffer,numberOfByte,true);
                    numberOfByte = numberOfByte - buffer;
                    buffer = 0;
                }
            }
            else
                bytesToSend = MemoryHandler.getNewTimestamp(true);
            sendBytes(bytesToSend,numberOfByte);
            break;
        case 3: // invia i byte non letti e li imposta come letti
            numberOfByte = MemoryHandler.newTimestamp()*6;
            if(intToSend > MAXRAM)
            {
                if(intToSend-buffer > MAXRAM)
                {
                    bytesToSend = MemoryHandler.getNewTimestamp(buffer,buffer+MAXRAM,false);
                    numberOfByte = MAXRAM;
                    buffer = buffer + MAXRAM;
                }
                else
                {
                    bytesToSend = MemoryHandler.getNewTimestamp(buffer,numberOfByte,false);
                    numberOfByte = numberOfByte - buffer;
                    buffer = 0;
                }
            }
            else
                bytesToSend = MemoryHandler.getNewTimestamp(true);
            sendBytes(bytesToSend,numberOfByte);
            break;
        case 4: // invia tutta la memoria usata
            numberOfByte = MemoryHandler.memoryUsed();
            if(intToSend > MAXRAM)
            {
                if(intToSend-buffer > MAXRAM)
                {
                    bytesToSend = MemoryHandler.getMemoryUsed(buffer,buffer+MAXRAM);
                    numberOfByte = MAXRAM;
                    buffer = buffer + MAXRAM;
                }
                else
                {
                    bytesToSend = MemoryHandler.getMemoryUsed(buffer,numberOfByte);
                    numberOfByte = numberOfByte - buffer;
                    buffer = 0;
                }
            }
            else
                bytesToSend = MemoryHandler.getMemoryUsed();
            sendBytes(bytesToSend,numberOfByte);
            break;
        case 5: // cancella la memoria EEPROM e invia il numero di byte eliminati
            intToSend = MemoryHandler.eraseMemory();
            action = new ActionSendInteger(intToSend,0);
            break;
        case 6:
            buffer = 0;

        }
        requestType = 255;
    }
}

void MasterComunicationHandlerClass::executeAction()
{

    if(action != 0)
        action->execute();
}

MasterComunicationHandlerClass MasterHandler = MasterComunicationHandlerClass();


void MasterComunicationHandlerClass::sendBytes(byte *_bytes, int _howMany)
{
    action = new ActionSendMemory(_bytes,_howMany,0);
}

void MasterComunicationHandlerClass::sendInteger(int _integer)
{
    action = new ActionSendInteger(_integer,0);
}
