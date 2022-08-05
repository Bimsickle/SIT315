// C++ code
//

// Declare pins used
const byte LED_PIN_ON = 13;
const byte LED_PIN_OFF = 12;
const byte PHOTO_LED_PIN_ON = 8;
const byte PHOTO_LED_PIN_OFF = 7;
const byte LED = 4;
const byte LED_TIMER = 9;
// Interrupt pins
const byte SENSOR_PIN = 2;
const byte PHOTO_PIN = 3;

//Set initial states
int state = 0;
int sensorValue = HIGH;
int state_photo = 0;
int sensorValue_photo = HIGH;
int sensor_state = 0;
int sensor = HIGH;
int ledState = 0;


// Main setup loop
void setup()
{     
  Serial.begin(9600);
  
  pinMode(LED_PIN_ON, OUTPUT);
  pinMode(LED_PIN_OFF, OUTPUT);
  
  pinMode(PHOTO_LED_PIN_ON, OUTPUT);
  pinMode(PHOTO_LED_PIN_OFF, OUTPUT);
  
  pinMode(LED, OUTPUT);
  pinMode(LED_TIMER, OUTPUT);
  
  pinMode(SENSOR_PIN, INPUT);  
  pinMode(PHOTO_PIN, INPUT); 
  
  // PCICR interrupts
  PCICR |= B00000100;
  PCMSK2 |= B00100000; //D5 Pin

  
  // Set LED
  digitalWrite(LED_PIN_OFF, sensorValue);
  digitalWrite(LED_PIN_ON, !sensorValue);
  digitalWrite(PHOTO_LED_PIN_OFF, sensorValue_photo);
  digitalWrite(PHOTO_LED_PIN_ON, !sensorValue_photo);
  digitalWrite(LED, 1);
  
// declare which pin (input/output) will trigget the interrupts
  attachInterrupt(digitalPinToInterrupt(2), motion_sensed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), light_sensed, CHANGE);
  
  double seconds = 4;
  startTimer(seconds);
  
}

// Empty void loop for interrupts
void loop(){}

void startTimer(double seconds)
{
  
  // Timer interrupt
  noInterrupts();
  
  double timer_length = 15624*seconds;
  
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  //Set timer compare
  OCR1A = timer_length;
  // Prescaler 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  // CTC
  TCCR1B |= (1 << WGM12);
  interrupts();
}

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

ISR (PCINT2_vect)
{
  Serial.print("Detected): ");
  
  // Take reading from sensor
  sensor = digitalRead(PIND & B00100000);

  // Declare state as the opposite
  sensor = !sensor;
  ledState = !ledState;
  // Set pins
  digitalWrite(LED, ledState);
 
  // print status to serial console 
  Serial.print("Motion Sensor 2: ");
  Serial.println(sensor);
  Serial.print("(Third interrupt): ");
  Serial.println(digitalRead(LED));  
  }

ISR(TIMER1_COMPA_vect) 
{  
  Serial.println("Timer Light: ");
  Serial.print(millis());
  Serial.println("");
  digitalWrite(LED_TIMER, digitalRead(LED_TIMER) ^1);
}

 