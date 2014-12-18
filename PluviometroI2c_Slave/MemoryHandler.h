
/*!
 * Formato salvataggio dati in EEPROM esterna: 6 byte totali per ogni basculata
 * 6 byte composti ->  (dai bit meno significativi ai più)
 *                 ->  2 byte data                 ->  5 bit giorno;    0-31        1°byte |m||m||m||d||d||d||d||d|          # d : day;  m : month;  y : year.
 *                                                 ->  4 bit mese;      0-11        2°byte |y||y||y||y||y||y||y||m|          # h : hour;  mi: minute;  s : second;
 *                                                 ->  7 bit anno;      0-99                                                 # c : counter;
 *                                                 -----------------
 *                 ->  2 byte + 1 bit tempo        -> 5 bit ora;        0-23        3°byte |mi||mi||mi||h||h||h||h||h|
 *                                                 -> 6 bit minuti;     0-59        4°byte |s||s||s||s||s||mi||mi||mi|
 *                                                 -> 6 bit secondi;    0-59
 *                                                 -----------------
 *                  ->  7bit + 1 byte #basculata   -> 15 bit contatore; 0-32767     5°byte |c||c||c||c||c||c||c||s|
 *                                                                                  6°byte |c||c||c||c||c||c||c||c|
 *
 * Nella memoria interna verrà salvato il contatore per individuare a che punto siamo arrivati con la scrittura in memoria
 *  setSyncProvider(RTC.get);
 */


#ifndef MEMORYHANDLERCLASS_h
#define MEMORYHANDLERCLASS_h

#include <Arduino.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include <EEPROM.h>


enum Information
{
  DAY,
  MONTH,
  YEAR,
  HOUR,
  MINUTE,
  SECOND,
  COUNTER
};

enum Counter
{
    CURRENT_POSITION,
    LAST_POSITION,
    TIMESTAMP_COUNTER

};

class MemoryHandlerClass
{
    private:
        // PARAMETRI //
        int MEMORYADD;       // indirizzo memoria esterna
        int RTCADD;            // indirizzo tiny RTC
        int MAXMEMORY;        // idendifica la quantità di memoria presente in byte
        int MAXSTACK;   // corrisponde al numero di timestamp salvabili in memoria
        int unsigned currentPosition;       // identifica l'attuale posizione in cui abbiamo salvato i dati da 6 byte l'ultima volta
        int unsigned lastTimestampPosition;  // identifica l'attuale posizione dell'ultimo timestamp che abbiamo inviato l'ultima volta
        int unsigned timestampCount;        // identifica il prossimo contatore da inserire nei bit del timestamp
        bool interrupted;                    // identifica la presenza di una interruzione
        // FUNZIONI //
        void ask_time(int * _params);       // funzione che richiede alla RTC data ed ora
        void setCounters();                 // funzione che inizializza tutti i contatori salvati in EEPROM interna al microprocessore
        void compressInformation(byte * _compressedValue, int * _array);    // funzione che trasforma un array di interi in un array di byte comprimendo le informazioni per essere salvate in memoria
        void writeEEPROM(unsigned int,byte);// funzione per scrivere dalla EEPROM esterna
        byte readEEPROM(unsigned int);      // funzione per leggere dalla EEPROM esterna
        byte * getMemory(int _from,int _to);    // ATTENZIONE: occupa spazio HEAP
        int incrementCounters();            // funzione che aggiorna i vari contatori e ritorna l'indice in cui salvare le informazioni
        byte decToBcd(byte _val);     // converte decimali in byte
        byte bcdToDec(byte _val);     // converte byte in decimali
        int getInfo(int _position, int _type);
        int getInfo(byte*_byteArray, int _type);
        void updateCounter(int, int, int);        // funzione che aggiorna il valore in memoria del contatore indicato dal tipo
    public:
        MemoryHandlerClass();               // costruttore di default
        void storeTimestamp();              // funzione core della classe, chiede alla RTC l'orario e la salva in memoria nella posizione corretta
        int newTimestamp();                 // funzione che ritorna il numero di timeStamp che non sono ancora stati letti
        byte* getNewTimestamp(bool _letUnread); // ATTENZIONE: occupa spazio HEAP -> funzione che ritorna il puntatore di un array di byte vuoto e lo ritorna per riferimento con i timestamp non ancora letti, letUnread identifica la richiesta di lasciare come non letti i timestamp inviati
        byte* getNewTimestamp(int _from,int _howmany,bool _letUnread);
        int memoryUsed();                   // ritorna il numero di byte usati
        byte* getMemoryUsed();
        byte *getMemoryUsed(int _from,int _howMany);
        void checkInterrupt();
        void interrupt();
        int eraseMemory();                  // ritorna il numero di byte cancellati dall'operazione e ripristina i contatori ai valori corretti
        void printC();
};

extern MemoryHandlerClass MemoryHandler;
#endif
