// C++ code
//

// Declare pins used
const byte LED_PIN_ON = 13;
const byte LED_PIN_OFF = 12;
const byte PHOTO_LED_PIN_ON = 8;
const byte PHOTO_LED_PIN_OFF = 7;
// Interrupt pins
const byte SENSOR_PIN = 2;
const byte PHOTO_PIN = 3;

//Set initial states
int state = 0;
int sensorValue = HIGH;
int state_photo = 0;
int sensorValue_photo = HIGH;


// Main setup loop
void setup()
{     
  Serial.begin(9600);
  pinMode(LED_PIN_ON, OUTPUT);
  pinMode(LED_PIN_OFF, OUTPUT);
  
  pinMode(PHOTO_LED_PIN_ON, OUTPUT);
  pinMode(PHOTO_LED_PIN_OFF, OUTPUT);
  
  pinMode(SENSOR_PIN, INPUT);  
  pinMode(PHOTO_PIN, INPUT); 
  
  
// declare which pin (input/output) will trigget the interrupts
  attachInterrupt(digitalPinToInterrupt(2), motion_sensed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), light_sensed, CHANGE);
}

// Empty void loop for interrupts
void loop(){}

void motion_sensed()
{  
// Take reading from sensor
  sensorValue = digitalRead(SENSOR_PIN);

// Declare state as the opposite
  sensorValue = !sensorValue;
  state = !state;
// Set pins
  digitalWrite(LED_PIN_OFF, !sensorValue);
  digitalWrite(LED_PIN_ON, sensorValue);
  
  digitalWrite(PHOTO_LED_PIN_OFF, !sensorValue);
  digitalWrite(PHOTO_LED_PIN_ON, sensorValue);
 
      // print status to serial console 
  Serial.print("Motion Sensor: ");
  Serial.println(sensorValue);
  Serial.print("Safe (G): ");
  Serial.println(digitalRead(LED_PIN_OFF));
  Serial.print("Caution (R): ");
  Serial.println(digitalRead(LED_PIN_ON));

}

void light_sensed()
{  
// Take reading from sensor
  sensorValue_photo = digitalRead(PHOTO_PIN);

// Declare state as teh opposite
  sensorValue_photo = !sensorValue_photo;
  state_photo = !state_photo;
// Set pins
  digitalWrite(PHOTO_LED_PIN_OFF, sensorValue_photo);
  digitalWrite(PHOTO_LED_PIN_ON, !sensorValue_photo);
 
      // print status to serial console 
  Serial.print("Photo Sensor: ");
  Serial.println(sensorValue_photo);
  Serial.print("Yellow (Y): ");
  Serial.println(digitalRead(PHOTO_LED_PIN_OFF));
  Serial.print("Blue (B): ");
  Serial.println(digitalRead(PHOTO_LED_PIN_ON));

}