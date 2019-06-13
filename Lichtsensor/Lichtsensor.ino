int eingang= A7; 
int LED = 12; 
int sensorWert = 0; 

void setup()//Hier beginnt das Setup.
{
Serial.begin(9600); 
pinMode (LED, OUTPUT); 
//Der analoge Pin muss nicht definiert werden.
}

void loop()
{
sensorWert=analogRead(eingang); 
Serial.print("Sensorwert = " ); Serial.println(sensorWert); 

if (sensorWert > 105 ) //Wenn der Sensorwert über 512 beträgt….
{
digitalWrite(LED, HIGH); //…soll die LED leuchten…
}

else 
{
digitalWrite(LED, LOW); //….soll sie nicht leuchten.
}
delay (50);
}
