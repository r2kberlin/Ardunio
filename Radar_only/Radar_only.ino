
int tasterstatus=0;
int value=0;
const int RADAR_SENSOR = 7;
const int RadarLED = 12;
    
void setup() {
  Serial.begin(9600);
 
  pinMode (RADAR_SENSOR, INPUT);
  pinMode (RadarLED, OUTPUT);
 
}
 
void loop() {
value = digitalRead(RADAR_SENSOR);
digitalWrite(RadarLED, value > 0 ? HIGH : LOW);
delay(100);
/*
tasterstatus=digitalRead(RADAR_SENSOR); //Hier wird der Pin7 ausgelesen (Befehl:digitalRead). Das Ergebnis wird unter der Variable „tasterstatus“ mit dem Wert „HIGH“ für 5Volt oder „LOW“ für 0Volt gespeichert.

if (tasterstatus == HIGH)//Verarbeitung: Wenn der taster gedrückt ist (Das Spannungssignal ist hoch)
{//Programmabschnitt des IF-Befehls öffnen.

mySwitch.send(5678, 24); // Der 433mhz Sender versendet die Dezimalzahl „5678“
delay (50); // 50 Millisekunden Pause
} //Programmabschnitt des IF-Befehls schließen.

else //...ansonsten...
{ //Programmabschnitt des else-Befehls öffnen.
mySwitch.send(1234, 24); // Der 433mhz Sender versendet die Dezimalzahl „1234“
} //Programmabschnitt des else-Befehls schließen.

//  int s = digitalRead(PirPin);
//  digitalWrite(PirLED, s);
*/
}
