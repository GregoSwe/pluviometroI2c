pluviometroI2c
==============

Librerie per la gestione di un PluviometroI2C con scheda Arduino, connessa ad una memoria EEPROM 24LC256 e una TinyRTC

*****************************************************************
Componenti richieste :
- una scheda Arduino in cui caricare lo sketch per la gestione dello slave;
- una scheda Arduino Master in cui aggiungere la libreria per interrogare lo slave;
- un orologio tinyRTC;
- una memoria EEPROM 24LC256 da 32kb, oppure 23LC512 da 64kb (attenzione nel caso in cui si utilizzi la memoria da 64kb bisogna modificare un parametro dentro /ArduinoSlave/MemoryHandler.cpp --> MAXMEMORY(32768) in MAXMEMORY(65536)).
****************************************************************

