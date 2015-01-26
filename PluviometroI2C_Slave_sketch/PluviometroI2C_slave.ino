/*
 * @File: PluviometroI2C_slave.ino
 * 
 * @Creation Date: 19/DIC/2014
 * 
 * @Last Update: 26/GEN/2015
 * 
 * @Version: 1.0.1
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
 * @Details: Questo file deve essere compilato e inserito all'interno
 * del microprocessore Arduino che si intende usare come scheda Slave
 *
 *
 * @Updates:
 *
 * @26/GEN/2015 v1.0.1
 *  Modificato il delay di tolleranza fra una basculata e l'altra per evitare rimbalzi: da 400 a 500 ms
 */

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
    delay(500);
    rebounce = false;
    attachInterrupt(0,process_interrupt,FALLING); 
  }
   

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







