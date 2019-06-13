#include <RCSwitch.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>
RCSwitch mySwitch = RCSwitch();
RCSwitch sender = RCSwitch();

int Radar_SENSOR = 7;
int RadarLED = 12;
int taster = 5;
int val = 0;
int value=LOW;
int bewegungsstatus=0;


void setup() {
  mySwitch.enableTransmit(2);
  Serial.begin(9600); //4Radar
  sender.setProtocol(1);
  sender.setPulseLength(323);
  pinMode (Radar_SENSOR, INPUT); 
   pinMode(RadarLED, OUTPUT);
   pinMode(taster, INPUT_PULLUP);
 //pinMode(PirLED, OUTPUT);
}
 
void loop() {

if (digitalRead(taster) == LOW) {
// if (pinStatus1 == HIGH)
// pinStatus1 = LOW;
//else pinStatus1 = HIGH;
//digitalWrite(RadarLED, pinStatus1);
//pinStatus1 = Radar_SENSOR;
digitalWrite(RadarLED, HIGH);
Radar_SENSOR = HIGH; 
value == HIGH;}
else{ 
digitalWrite(RadarLED, LOW);
value == LOW; 
//delay(5000);
}
//digitalWrite(RadarLED, Radar_SENSOR);



int value = digitalRead(Radar_SENSOR);
//  digitalWrite(RadarLED, value > 0 ? HIGH : LOW);
//  delay(1000);

//digitalWrite(11, LOW);   für PIR Modul

//bewegungsstatus=digitalRead(PIR_SENSOR); //Hier wird der Pin7 ausgelesen (Befehl:digitalRead). Das Ergebnis wird unter der Variable „bewegungsstatus“ mit dem Wert „HIGH“ für 5Volt oder „LOW“ für 0Volt gespeichert.

if (digitalRead(taster) == LOW)

//if (digitalRead(Radar_SENSOR)==HIGH)
{          
//Programmabschnitt des IF-Befehls öffnen.
mySwitch.send(5575953, 24);
sender.sendTriState("FFFF0FFF0F0F");  // Der 433mhz Sender versendet die Dezimalzahl „21696
delay (50); 

//  digitalWrite(PirLED, HIGH);
//  delay(5000);
//  digitalWrite(PirLED, LOW);
  
}

//else
//
//sender.sendTriState("FFFF0FFF0FF0");
//  {
//  digitalWrite(PirLED, LOW);
//  }
 // int s = digitalRead(PirPin);
 // digitalWrite(PirLED, s);
}
