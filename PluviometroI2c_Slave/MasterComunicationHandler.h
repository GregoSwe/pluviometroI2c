#ifndef MASTERCOMUNICATIONHANDLERCLASS_h
#define MASTERCOMUNICATIONHANDLERCLASS_h

#include <Arduino.h>
#include "ActionSendInteger.h"
#include "ActionSendMemory.h"
#include "MemoryHandler.h"

class MasterComunicationHandlerClass
{
private:

    byte requestType;
    AbstractAction* action;
    unsigned int buffer;
    unsigned int MAXRAM;
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
