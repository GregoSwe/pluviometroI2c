#include "ActionSendMemory.h"

ActionSendMemory::ActionSendMemory(byte *_byteToSend, int _howManyByte, AbstractAction *_otherAction = 0 ):
    AbstractAction(_otherAction),byteToSend(_byteToSend),
    howManyByte(_howManyByte), BYTERATE(30),
    actualPointer(_byteToSend)
{

}

/*ActionSendMemory::ActionSendMemory(byte *_byteToSend, int _howManyByte):
    ActionSendMemory(_byteToSend,_howManyByte,0)
{
}
*/
void ActionSendMemory::execute()
{
    if(otherAction != 0)
        otherAction->execute();                      // se esiste un'altra Action la eseguo

    if(howManyByte > 0)                              // controllo per scrupolo di avere almeno un byte da inviare
    {

        if(howManyByte <= BYTERATE)                   // controllo se i byte che devo inviare sono meno del massimo byterate imposto
            Wire.write(actualPointer,howManyByte);      // se true, invio i byte senza problemi
        else
        {
            byte message[BYTERATE];                     // altrimenti creo un array di dimensione del byterate massimo

            for(int i = 0; i <BYTERATE; i++)            // copio altrettanti byte dall'array ricevuto in input
                message[i] = actualPointer[i];

            Wire.write(message,BYTERATE);               // invio il messaggio col massimo byterate
            actualPointer = (actualPointer + BYTERATE);   // incremento il puntatore che tiene traccia di dove siamo arrivati ad inviare i byte
            howManyByte =  howManyByte - BYTERATE;       // decremento il contatore che tiene traccia di quanti byte dobbiamo ancora inviare
        }
    }
}

ActionSendMemory::~ActionSendMemory()
{
    delete [] byteToSend; // rilascio la memoria occupata dall'array di byte, utilizzando il puntatore iniziale
}
