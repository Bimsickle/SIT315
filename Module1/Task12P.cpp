// C++ code
//

const byte LED_PIN_ON = 13;
const byte LED_PIN_OFF = 12;
const byte SENSOR_PIN = 2;

int state = 0;
int sensorValue = HIGH;

void setup()
{     
  Serial.begin(9600);
  pinMode(LED_PIN_ON, OUTPUT);
  pinMode(LED_PIN_OFF, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);  
  
  attachInterrupt(digitalPinToInterrupt(2), motion_sensed, CHANGE);
}

void loop(){}

void motion_sensed()
{  
  sensorValue = digitalRead(SENSOR_PIN);
  sensorValue = !sensorValue;
  state = !state;
  digitalWrite(LED_PIN_OFF, !sensorValue);
  digitalWrite(LED_PIN_ON, sensorValue);
  
  Serial.print("Sensor: ");
  Serial.println(sensorValue);
  Serial.print("Safe (G): ");
  Serial.println(digitalRead(LED_PIN_OFF));
  Serial.print("Caution (R): ");
  Serial.println(digitalRead(LED_PIN_ON));

}
