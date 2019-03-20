#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

int taster = 4;
int tasterstatus;
int pinStatus1 ;
int PIR_SENSOR = 8;
int PirLED = 5;
int bewegungsstatus = 0;

void setup()
{
pinMode(taster, INPUT_PULLUP);
pinMode(PIR_SENSOR, INPUT);
pinMode(PirLED, OUTPUT);
  
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
 if (digitalRead(taster) == LOW) {
     if (pinStatus1 == HIGH){ 
     digitalWrite(PirLED, HIGH);//Programmabschnitt des IF-Befehls öffnen.
     pinStatus1 = LOW;
     }
     else {
     pinStatus1 = HIGH;
     digitalWrite(PirLED, LOW);//Programmabschnitt des IF-Befehls öffnen.
     }
    digitalWrite(tasterstatus, pinStatus1);
    delay(500);
   }
}
