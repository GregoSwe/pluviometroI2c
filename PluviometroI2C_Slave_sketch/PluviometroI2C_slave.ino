#include <ActionSendMemory.h>
#include <MemoryHandler.h>
#include <AbstractAction.h>
#include <ActionSendInteger.h>

#include <MasterComunicationHandler.h>

#include <EEPROM.h>
#include <MemoryFree.h>
#include <Wire.h>
#include <Time.h>
#include <MemoryHandler.h>
#include <DS1307RTC.h>

#include<MemoryFree.h>

volatile bool rebounce = false;
void setup()
{
  Wire.begin(2);                                 
  Wire.onReceive(request_decider);                              
  Wire.onRequest(request_handler);                           
  attachInterrupt(0,process_interrupt,FALLING);  
  Serial.begin(9600);
  Serial.println("ready");
}
void loop()
{
  MemoryHandler.checkInterrupt();
  MasterHandler.prepareAction();

  if(rebounce == true)
  {
    delay(400);
    rebounce = false;
  }
  // 
  debug();

}
void process_interrupt()
{
  if(rebounce == false)
  {
    MemoryHandler.interrupt();
    rebounce = true;
  }
}

void request_decider(int numBytes)
{
  int requestType = 0;

  while(Wire.available())
    requestType = Wire.read();

  Serial.println(requestType);
  MasterHandler.selectAction(requestType);
}

void request_handler()
{
  MasterHandler.executeAction();
}




////////////////////////////// DEBUG //////////////////////////////
void debug()
{
  if(Serial.available())
  {
    byte res = Serial.read();
    if(res == 'd')
    {
      Serial.println(EEPROM.read(0));
      Serial.println(EEPROM.read(1));
    }
    if(res == 'z')
    {
      MemoryHandler.printC();
    }
    if(res == 'q')
    {
      MemoryHandler.printC();

      MemoryHandler.eraseMemory();

      MemoryHandler.printC();
    }
    if(res == 'w')
    {
      MemoryHandler.interrupt();


    }
    if(res == 'e')
    {
      byte * arr = MemoryHandler.getNewTimestamp(true);
      print_information(arr,MemoryHandler.newTimestamp()*6);
      // delete [] arr;
    }

    if(res == 'r')
    {
      int h = MemoryHandler.newTimestamp()*6;
      byte * arr = MemoryHandler.getNewTimestamp(false);

      print_information(arr,h);
      // delete [] arr;

    }
    if(res == 't')
    {
      int h = MemoryHandler.memoryUsed();
      byte * arr = MemoryHandler.getMemoryUsed();

      print_information(arr,h);
    }
  }

}


void print_information(byte* array, int dimension)
{
  if(dimension == 0)
    Serial.println("nulla");
  Serial.print("dimension = ");
  Serial.println(dimension);
  int manyTimes = dimension/6;
  for(int i = 0 ; i<manyTimes; i ++)
  {
    Serial.println();
    Serial.println(" *** Bytes *** ");
    Serial.print(" -- ");
    for(int j=0;j<6;j++)
    {
      Serial.print(array[i*6+j]); 
      Serial.print(" -- ");
    }
    Serial.println();
    int valori[6] = {
    };

    decompress(array + i*6,valori);
    Serial.print("Data: "); 
    Serial.print(valori[0]); 
    Serial.print("/");
    Serial.print(valori[1]);
    Serial.print("/");
    Serial.println(valori[2]);
    Serial.print("Ora: "); 
    Serial.print(valori[3]); 
    Serial.print(":");
    Serial.print(valori[4]);
    Serial.print(":");
    Serial.println(valori[5]);
    Serial.print("Contatore: "); 
    Serial.println(valori[6]);         
    Serial.println("------------------------------");

  }

}


int get_info(byte * _byteArray, int _type)
{
  //inizializzo i byte recuperando le informazioni dall'array
  byte firstByte = _byteArray[0];
  byte secondByte = _byteArray[1];
  byte thirdByte = _byteArray[2];
  byte fourthByte = _byteArray[3];
  byte fithByte = _byteArray[4];
  byte sixthByte = _byteArray[5];
  int unsigned outcome = 0;

  switch(_type)
  {
  case DAY:

    outcome = firstByte & B00011111;
    break;  // ritorno il byte mascherando gli utimi tre bit (che non mi servono)

  case MONTH :

    firstByte = (unsigned byte)(firstByte & B11100000)  >> 5;
    secondByte = (secondByte & B00000001) << 3;
    outcome = firstByte + secondByte;
    break;

  case YEAR :

    outcome =  (unsigned byte) secondByte  >> 1;
    outcome += 2000;
    break;

  case HOUR :

    outcome = thirdByte & B00011111;
    break;

  case MINUTE :

    thirdByte =  (unsigned byte) thirdByte >> 5;
    fourthByte =  (fourthByte & B00000111) << 3 ;
    outcome = thirdByte + fourthByte;
    break;

  case SECOND :

    fourthByte = (unsigned byte) fourthByte  >> 3;
    fithByte = (fithByte & B00000001) << 5;
    outcome = fourthByte + fithByte;    
    break;  

  case COUNTER :

    fithByte = (unsigned byte) fithByte  >> 1;
    outcome = ((outcome + sixthByte) << 7) + fithByte;
    ;
    break;
  }
  return outcome;
}
void decompress(byte * _compressedByte, int * _integerArray)
{

  _integerArray[0] = get_info(_compressedByte, DAY);
  _integerArray[1] = get_info(_compressedByte, MONTH);
  _integerArray[2] = get_info(_compressedByte, YEAR);
  _integerArray[3] = get_info(_compressedByte, HOUR);
  _integerArray[4] = get_info(_compressedByte, MINUTE);
  _integerArray[5] = get_info(_compressedByte, SECOND);
  _integerArray[6] = get_info(_compressedByte, COUNTER);
}



