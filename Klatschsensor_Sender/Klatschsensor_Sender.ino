#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
RCSwitch sender = RCSwitch();
int soundSensor = 10;
int relay = 12;
int claps = 0;
long detectionSpanInitial = 0;
long detectionSpan = 0;
boolean lightState = false;


int i = 0; 
uint32_t lastseen = 0;
uint32_t interval = 1000;  
 
void setup() {
  mySwitch.enableTransmit(2);
  Serial.begin(9600);
  pinMode(soundSensor, INPUT);
  pinMode(relay, OUTPUT);
}
 
void loop() {
//---------------------------------------------------------------
  if (millis() - lastseen > interval) {
  ++i;
  lastseen = millis();
  
  Serial.println(" ");
  Serial.print("Zähler_i = ");Serial.println(i);
//  Serial.print("PIR_bewegungsstatus="); Serial.println(bewegungsstatus);
//  Serial.print("Zähler_bewegungsstatus=");Serial.println(bewegungsstatus);
//  Serial.print("Spielt="); Serial.println(spielt);
  Serial.println(" ");
  
  if(i==15)                                // HIER SEKUNDEN BIS NEUSTART EINTRAGEN
  {i=0;  
  lastseen = millis();

  Serial.println(" ");
  Serial.print("über 15s - NEUSTART /LED AUS");
  Serial.println(" ");
  
 // digitalWrite(PirLED, LOW); 
 }
}
 /*-------------------------------------------------------------*/
 if(claps == 2){
  i=0;int bewegungsstatus = 1; 
  lastseen = millis();
  delay(100);
//  Serial.println(" ");
 Serial.print("i = ");Serial.println(i);
//  Serial.println(" ");
 Serial.print("PIR_bewegungsstatus="); Serial.println(bewegungsstatus);
//  Serial.print("Spielt="); Serial.println(spielt);
 // digitalWrite(PirLED, HIGH);
  } 

/*-------------------------------------------------------------*/


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
