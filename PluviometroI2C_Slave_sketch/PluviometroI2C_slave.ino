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



volatile bool rebounce = false;
void setup()
{
  Wire.begin(2);                                 
  Wire.onReceive(request_decider);                              
  Wire.onRequest(request_handler);         
  pinMode(2,INPUT_PULLUP);                  
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
    detachInterrupt(0);
    delay(400);
    rebounce = false;
    attachInterrupt(0,process_interrupt,FALLING); 
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








