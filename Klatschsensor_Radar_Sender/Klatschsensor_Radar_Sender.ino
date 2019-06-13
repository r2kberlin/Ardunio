#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
RCSwitch sender = RCSwitch();
int soundSensor = 10;
int relay = 12;
int claps = 0;
long detectionSpanInitial = 0;
long detectionSpan = 0;
boolean lightState = false;
int test;
/*---------------------Radar*/
const int RADAR_SENSOR = 7;

int i = 0; 
uint32_t lastseen = 0;
uint32_t lastseen2 = 0;
uint32_t interval = 1000; 
uint32_t interval2 = 1000;
int bewegungsstatus;
 
void setup() {
  mySwitch.enableTransmit(2);
  Serial.begin(9600);
  pinMode(soundSensor, INPUT);
  pinMode(relay, OUTPUT);

  const int RADAR_SENSOR = 7;
}
 
void loop() {
digitalWrite(relay, test > 0 ? HIGH : LOW);
  int value = digitalRead(RADAR_SENSOR);
//---------------------------------------------------------------
  if (millis() - lastseen > interval) {
  ++i;
  lastseen = millis();
  bewegungsstatus=0;
  Serial.println(" ");
  Serial.print("Zähler_i = ");Serial.println(i);
//  Serial.print("PIR_bewegungsstatus="); Serial.println(bewegungsstatus);
//  Serial.print("Zähler_bewegungsstatus=");Serial.println(bewegungsstatus);
//  Serial.print("Spielt="); Serial.println(spielt);
  Serial.println(" ");
  
  
  if(i==7)                                // HIER SEKUNDEN BIS NEUSTART EINTRAGEN
  {i=0;  
  lastseen = millis();

  Serial.println(" ");
  Serial.print("über 15s - NEUSTART /LED AUS");
  Serial.println(" ");
  test = HIGH;
 // digitalWrite(PirLED, LOW); 
 }
}
 /*-------------------------------------------------------------*/
 if(value == HIGH){
 test = LOW;
  i=0;bewegungsstatus = 1; 
  lastseen = millis();
  delay(100);
//  Serial.println(" ");
 Serial.print("i = ");Serial.println(i);
//  Serial.println(" ");
 Serial.print("PIR_bewegungsstatus="); Serial.println(bewegungsstatus);
//  Serial.print("Spielt="); Serial.println(spielt);
 // digitalWrite(PirLED, HIGH);
  } 

  
if (millis() - lastseen2 > interval2) {
  ++i;
  lastseen2 = millis();
  if(i==7)                                // HIER SEKUNDEN BIS NEUSTART EINTRAGEN
  {i=0; 
    Serial.print("7sek, jetzt senden");
    if(bewegungsstatus==1){
      mySwitch.send(5575953, 24);
    }

     if(bewegungsstatus==0){
      mySwitch.send(5575956, 24);
    }
    
  lastseen2 = millis();
 }
 }
/*---------------------Klatschen----------------------------------------*/


  int sensorState = digitalRead(soundSensor);
 
  if (sensorState == 0)
  {
    if (claps == 0)
    {
      detectionSpanInitial = detectionSpan = millis();
      claps++;
       
    }
    else if (claps > 0 && millis()-detectionSpan >= 50)
    {
      detectionSpan = millis();
      claps++;
    }
  }
 
  if (millis()-detectionSpanInitial >= 300)
  {
    
    if (claps == 2)
    {
      Serial.print("Sensorwert = " );
      
      if (!lightState)
        {
          lightState = true;
          digitalWrite(relay, HIGH);
          mySwitch.send(5575953, 24);
        }
        else if (lightState)
        {
          lightState = false;
          digitalWrite(relay, LOW);
          mySwitch.send(5575956, 24);
        }
    }
    claps = 0;
  }
}
