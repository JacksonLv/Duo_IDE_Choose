#if defined(ARDUINO) 
SYSTEM_MODE(MANUAL);//do not connect to cloud
#else
SYSTEM_MODE(AUTOMATIC);//connect to cloud
#endif

int sensorPin = A0;    // select the input pin for the potentiometer
int fanPin = D2;      // select the pin for the fan
uint32_t sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(fanPin, OUTPUT);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  // turn the fanPin on
  analogWrite(fanPin, (sensorValue)*256/4096);
}
