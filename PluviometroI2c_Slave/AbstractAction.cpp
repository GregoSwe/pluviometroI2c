#include "AbstractAction.h"

AbstractAction::AbstractAction(AbstractAction *_otherAction = 0):
    otherAction(_otherAction)
{
}

AbstractAction::~AbstractAction()
{
    if(otherAction != 0)
        delete otherAction;
}
