#include"ActionSendInteger.h"

ActionSendInteger::ActionSendInteger(int _intToSend, AbstractAction *_otherAction = 0):
    AbstractAction(_otherAction),intToSend(_intToSend)
{

}

void ActionSendInteger::execute()
{
    if(otherAction != 0)            // verifico se esiste un'altra action da inviare prima
        otherAction->execute();
    byte message[2];

    message[0] = intToSend >> 8;
    message[1] = intToSend & 255;


    Wire.write(message,2);
}


/*ActionSendInteger::ActionSendInteger(int _intToSend):
    ActionSendInteger(_intToSend,0)
{
}*/
