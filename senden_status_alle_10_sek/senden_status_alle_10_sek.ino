#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
RCSwitch sender = RCSwitch();

int tasterstatus=0;
int value=0;
const int RADAR_SENSOR = 7;
const int RadarLED = 12;

int bewegungsstatus ;
int i = 0;
int o=0; 
long Code;

uint32_t lastseen2 = 0;
uint32_t lastseen = 0;
uint32_t interval = 1000; 

void setup() {
   mySwitch.enableTransmit(2);
   Serial.begin(9600);
    pinMode (RADAR_SENSOR, INPUT);
    pinMode (RadarLED, OUTPUT);
 
}

void loop() {
value = digitalRead(RADAR_SENSOR);
digitalWrite(RadarLED, bewegungsstatus);

if (millis() - lastseen > interval) {
  ++i;
  lastseen = millis();
  
  Serial.println(" ");
  Serial.print("Zähler_i = ");Serial.println(i);
  Serial.print("PIR_bewegungsstatus="); Serial.println(bewegungsstatus);
  Serial.println(" ");
  
  if(i==15)                                // HIER SEKUNDEN BIS NEUSTART EINTRAGEN
  {i=0; bewegungsstatus = LOW; 
  Code=5575956;
 // lastseen = millis();
  Serial.println(" ");
  Serial.print("über 15s - NEUSTART /LED AUS");
  Serial.println(" ");
  
 }
}

if(digitalRead(RADAR_SENSOR) == HIGH){
  i=0; 
 // lastseen = millis();
  bewegungsstatus = HIGH; 
  Code=5575953;
  //delay(500);
//  Serial.println(" ");
// Serial.print("i = ");Serial.println(i);
//  Serial.println(" ");
 Serial.print("Bewegung_erkannt"); Serial.println(bewegungsstatus);
  } 










/*

if (millis() - lastseen2 > interval) {
  ++o;
  lastseen2 = millis();
  
  if(o==9){                                // HIER SEKUNDEN BIS NEUSTART EINTRAGEN
  o=0;  


  Serial.println(" ");
  Serial.print("Jede 9 Sek Senden!:Code ");
  Serial.print(Code);
  Serial.println(" ");
  mySwitch.send(Code, 24);
  delay(150);
  
 }
}


*/


}
