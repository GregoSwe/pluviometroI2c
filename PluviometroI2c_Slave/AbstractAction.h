#ifndef ABSTRACTACTION_h
#define ABSTRACTACTION_h
#include <Arduino.h>
class AbstractAction
{
private:
protected:
    AbstractAction* otherAction;
public:
    AbstractAction(AbstractAction* _otherAction);
    virtual void execute()=0;
    virtual ~AbstractAction();
};

#endif
