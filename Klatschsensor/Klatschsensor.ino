int soundSensor = 10;
int relay = 12;
int claps = 0;
long detectionSpanInitial = 0;
long detectionSpan = 0;
boolean lightState = false;
 
void setup() {
  Serial.begin(9600);
  pinMode(soundSensor, INPUT);
  pinMode(relay, OUTPUT);
}
 
void loop() {

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
        }
        else if (lightState)
        {
          lightState = false;
          digitalWrite(relay, LOW);
        }
    }
    claps = 0;
  }
}
