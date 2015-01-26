/*
*
* Questo codice viene utilizzato per testare la capacità del pluviometro di calcolare correttamente il passaggio di mezzo litro d'acqua in un minuto (equivalente di 300ml di pioggia in un'ora
* 
*/

int i = 0;
volatile bool vai = false;
volatile  double startTime = 0;
 double x[30];
void setup()
{

  pinMode(7,OUTPUT);
  pinMode(2,INPUT_PULLUP);
  digitalWrite(7,LOW);
  Serial.begin(9600);
  attachInterrupt(0,interr,FALLING);

}

byte firstTime = 1;
void loop()
{
  if(vai == true)
  {
    if(firstTime==1)
    {
      startTime = millis();
      firstTime = 0;
    }
    detachInterrupt(0);
    x[i] = millis()-startTime;
    
    delay(500);
    Serial.print("i : ");
    Serial.print(i);
    Serial.print(" intervallo -> ");
    Serial.print((x[i]-x[i-1])/1000);
    Serial.print(" - time -> ");
    if(i==0)
      Serial.println(0);
      else
      Serial.println(x[i]/1000);
     i++; 
    attachInterrupt(0,interr,FALLING);
    vai = false;
  }
  if(i==28)
  {
    i = 0;
    resoults();
  }
}

void resoults() // stampa i risultati ottenuti
{
   double totalTime = (millis() - startTime)/1000;
  Serial.print(" tempo totale di esecuzione = ");
  Serial.println( totalTime );


   double minorIntervallo = 10000;
   double maggiorIntervallo = 0;
  int minorT = 0;
  int maggiorT = 0;

   double media = 0;

  for(int i = 0; i <27; i++)
  {
     double valore = x[i+1] - x[i];
    if(valore >maggiorIntervallo)  // calcolo il maggior tempo di basculata e quando è avvenuto
    {
      maggiorIntervallo = valore;
      maggiorT = i;
    }
    if(valore < minorIntervallo) // calcolo il minor tempo di basculata e quando è avvenuto
    {
      minorIntervallo = valore;
      minorT = i;  
    }
    media +=valore;
  }
  media = media / 28;
  
  Serial.println("*****");
  Serial.print(" maggior tempo di basculata = ");Serial.print(maggiorIntervallo/1000);Serial.print("s - avvenuto dopo la basculata #");Serial.println(maggiorT);

  Serial.print(" minor tempo di basculata = ");Serial.print(minorIntervallo/1000);Serial.print("s - avvenuto dopo la basculata #");Serial.println(minorT);
  
  Serial.print(" con una media di ");Serial.print(media/1000);Serial.print(" secondi");
}

void interr()
{
  if(vai == false)
  {
    vai = true;
  }
}






