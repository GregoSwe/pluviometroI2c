#ifndef ACTIONSENDINTEGER_h
#define ACTIONSENDINTEGER_h

#include"AbstractAction.h"
#include <Wire.h>
class ActionSendInteger : public AbstractAction
{
private:
   unsigned int intToSend;
public:
    ActionSendInteger(int _intToSend, AbstractAction *_otherAction);
    //ActionSendInteger(int _intToSend);
    virtual void execute();
    virtual ~ActionSendInteger(){}
};

#endif
