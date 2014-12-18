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
