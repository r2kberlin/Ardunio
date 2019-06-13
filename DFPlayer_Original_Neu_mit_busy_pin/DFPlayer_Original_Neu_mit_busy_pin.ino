
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

int taster = 4;
int PIR_SENSOR = 8;
int PirLED = 5;
int busytest = 7;

bool pinStatus1 = HIGH;
int bewegungsstatus ;
int spielt = 0;
int tasterstatus;
int i = 0; 

uint32_t lastseen = 0;
uint32_t interval = 1000;  

void setup()
{
pinMode(taster, INPUT_PULLUP);
pinMode(PIR_SENSOR, INPUT);
pinMode(busytest, INPUT);
pinMode(PirLED, OUTPUT);
  
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... Hello Rick da KING"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30      HIER LAUSTÄRKE EINSTELLEN

 Serial.println(myDFPlayer.readState());
}

void loop()
{

//---------------------------------------------- Hier versuche ich  bewegungsstatus = LOW zu setzen, wenn nicht innerhalb der 15s auf 0 gesetzt wird
//if (millis() - lastseen > interval) {
//  if ( digitalRead(taster) == LOW){
//  lastseen = 0;
//   bool bewegungsstatus = HIGH;
//   digitalWrite(PirLED, LOW);//
//   Serial.println("if");
//  }
//  else{
//    lastseen = millis();   // aktuelle Zeit abspeichern
//    bool bewegungsstatus = LOW; //Die 15 sekunden wurden überschritten
//    digitalWrite(PirLED, HIGH);//
//    Serial.println("else");
//  }
//}


//------------------------------------------------Neuer Versuch: jede sek hochzählen bis 15, dann ist bewegungsstatus = LOW (wenn !nicht! vorher zurückgesetzt)

if (millis() - lastseen > interval) {
  ++i;
  lastseen = millis();
  
  Serial.println(" ");
  Serial.print("Zähler_i = ");Serial.println(i);
  Serial.print("PIR_bewegungsstatus="); Serial.println(bewegungsstatus);
  Serial.print("Zähler_bewegungsstatus=");Serial.println(bewegungsstatus);
  Serial.print("Spielt="); Serial.println(spielt);
  Serial.println(" ");
  
  if(i==15)                                // HIER SEKUNDEN BIS NEUSTART EINTRAGEN
  {i=0; bewegungsstatus = LOW; 
  lastseen = millis();

  Serial.println(" ");
  Serial.print("über 15s - NEUSTART /LED AUS");
  Serial.println(" ");
  
 // digitalWrite(PirLED, LOW); 
 }
}

if(digitalRead(PIR_SENSOR) == HIGH){
  i=0; bewegungsstatus = 1; 
  lastseen = millis();
  delay(100);
//  Serial.println(" ");
 Serial.print("i = ");Serial.println(i);
//  Serial.println(" ");
 Serial.print("PIR_bewegungsstatus="); Serial.println(bewegungsstatus);
//  Serial.print("Spielt="); Serial.println(spielt);
 // digitalWrite(PirLED, HIGH);
  } 

//--------------------------------------------------------------------------------- Taster wird zum Schalter, auch zum Testen

//bewegungsstatus=digitalRead(taster);

//  if (digitalRead(taster) == LOW) { //Teste mit LED Tasterstatus
//     if (pinStatus1 == HIGH){ 
//   //  digitalWrite(PirLED, HIGH);//
//     pinStatus1 = LOW;
//     }
//     else {
//     pinStatus1 = HIGH;
// //    digitalWrite(PirLED, LOW);//
//     }
//    digitalWrite(tasterstatus, pinStatus1);
//    delay(50);
//   }
//------------------------------------------------------------------------------------------------
if (digitalRead(busytest) == HIGH){spielt = 0; digitalWrite(PirLED, LOW);}
if (digitalRead(busytest) == LOW){spielt = 1; digitalWrite(PirLED, HIGH);}


if (bewegungsstatus == HIGH && spielt == 0 )              // myDFPlayer.readState() == 512 heißt keine "Music" -> Music startet (&& myDFPlayer.readState() == 512)
{    
 // digitalWrite(PirLED, HIGH);
  myDFPlayer.play(1);  //Play the first mp3
 // spielt = 1;
 // delay(500);
  Serial.println(myDFPlayer.readState());
  //delay(301800);
}

if (bewegungsstatus == LOW && spielt == 1)              //myDFPlayer.readState() == 513 heißt SPIELT "Music"
{    
 // digitalWrite(PirLED, LOW);//Programmabschnitt des IF-Befehls öffnen.
 myDFPlayer.pause();  //PAUSE
 //spielt = 0;
 // delay(500);
  Serial.println(myDFPlayer.readState());
  //delay(301800);
}




//if (digitalRead(taster) == LOW && myDFPlayer.readState() != 512 && spielt == 0)              //Verarbeitung: Wenn der bewegungsstatus ist (Das Spannungssignal ist hoch)
//{    
// // digitalWrite(PirLED, HIGH);//Programmabschnitt des IF-Befehls öffnen.
//  myDFPlayer.play(1);  //Play the first mp3
//  delay(500);
//  Serial.println(myDFPlayer.readState());
//  //delay(301800);
//  
//}

  
  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
