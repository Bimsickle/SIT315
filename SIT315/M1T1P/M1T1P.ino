// C++ code
//

const byte LED_PIN_ON = 13;
const byte LED_PIN_OFF = 12;
const byte SENSOR_PIN = A4;

int state = 0;
int sensorValue = HIGH;

void setup()
{     
  Serial.begin(9600);
  pinMode(LED_PIN_ON, OUTPUT);
  pinMode(LED_PIN_OFF, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);    
}



void loop()
{  
  sensorValue = digitalRead(SENSOR_PIN);   
  
  if (sensorValue == HIGH ){
    digitalWrite(LED_PIN_OFF, HIGH);
    digitalWrite(LED_PIN_ON, LOW);
   
    if (state == LOW){
    Serial.println("I see you!");
    Serial.println(millis());   
      
  	digitalWrite(LED_PIN_OFF, HIGH);
    digitalWrite(LED_PIN_ON, LOW);
    state = HIGH; 
      
    Serial.print("Sensor: ");
    Serial.println(sensorValue);
    Serial.print("Safe (G): ");
    Serial.println(digitalRead(LED_PIN_OFF));
    Serial.print("Caution (R): ");
    Serial.println(digitalRead(LED_PIN_ON));
    }
  }
  else{
    digitalWrite(LED_PIN_ON, HIGH);
    digitalWrite(LED_PIN_OFF, LOW);
    
    if (state == HIGH){
    Serial.println("Incognito mode Activated!");
    Serial.println(millis());      
      
  	digitalWrite(LED_PIN_ON, LOW);
    digitalWrite(LED_PIN_OFF, HIGH);
    state = LOW; 
        
    Serial.print("Sensor: ");
    Serial.println(sensorValue);
    Serial.print("Safe (G): ");
    Serial.println(digitalRead(LED_PIN_OFF));
    Serial.print("Caution (R): ");
    Serial.println(digitalRead(LED_PIN_ON));
    }
  }
}
