pluviometroI2c
==============

Librerie per la gestione di un PluviometroI2C con scheda Arduino, connessa ad una memoria EEPROM 24LC256 e una TinyRTC.
Documentazione : https://github.com/GregoSwe/pluviometroI2c/wiki

*****************************************************************
Componenti richieste :
- una scheda Arduino in cui caricare lo sketch per la gestione dello slave;
- una scheda Arduino Master in cui aggiungere la libreria per interrogare lo slave;
- un orologio tinyRTC;
- una memoria EEPROM 24LC256 da 32kb, oppure 23LC512 da 64kb (attenzione nel caso in cui si utilizzi la memoria da 64kb bisogna modificare un parametro dentro /ArduinoSlave/MemoryHandler.cpp --> MAXMEMORY(32768) in MAXMEMORY(65536)).


*****************************************************
Come installare:

Estrarre i contenuto del file .zip e inserire le cartelle PluviometroI2C\_Slave e PluviometroI2C\_Master all'interno della cartella ~/sketchbook/libraries. Dopodichè inserire la cartella PluviometroI2C\_Slave\_Sketch in ~/sketchbook, aprire il proprio IDE Arudino (1.0.6 o 1.0.5 compatibili) e caricare nella scheda che si desidera utilizzare per monitorare il pluviometro lo sketch.

Usare invece l'oggetto SlaveInterface, della libreria libreria PluviometroI2C\_Master, nella propria scheda Master per comunicare tramite I2C con la scheda Slave.
