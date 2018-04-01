#define BAUD_RATE 9600
#define SENSOR_COUNT 4
#define DIRECTION_THRESHOLD 200
#define WHITE_THRESHOLD 400
#define BLACK_THRESHOLD 150
#define SPEED_MAX 1024
#define SPEED_MIN 0

//  int In3 = 8;
//  int In4 = 6;
//
//  int In1 = 4;
//  int In2 = 2;

/**SensorPins : left to right**/
int sensorPin[] = {A1, A2, A4, A5};
int sensorVal[SENSOR_COUNT];
int ledPin[] = {2,3,4,5,6};
int leftLedPin = 7;
int rightLedPin = 8;
int remoteSensorPin = 12;
int remoteSensorVal;
int leftMotorPin = A3;
int rightMotorPin = A0;
unsigned long lastTime;
boolean(isOn);
int score;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD_RATE);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(remoteSensorPin, INPUT);
  digitalWrite(LED_BUILTIN, LOW);
  lastTime = millis();
  isOn = true;
  randomSeed(1);
}

void loop() {
  remoteSensorVal = digitalRead(remoteSensorPin);
//  powerHold();
  powerToggle();
  powerLed();
  if(isOn) {
    for(int i = 0; i < SENSOR_COUNT; i++) {
      sensorVal[i] = analogRead(sensorPin[i]);
    }
    randomizeSensorValues();
//    printSensorValues();
    score = getScore();
    Serial.println(score);
//    Serial.println(score);
    displayLeds();
    showDirection();
    steer();
    Serial.print(analogRead(leftMotorPin));
    Serial.print(","); 
    Serial.print(analogRead(rightMotorPin));
    Serial.println();
  }
}

void displayLeds(){
  for(int i = 0; i < SENSOR_COUNT; i++) {
    if(sensorVal[i] >= 0)
      digitalWrite(ledPin[i], HIGH);
    else
      digitalWrite(ledPin[i], LOW);
  }
}

void printSensorValues() {  
    for(int i = 0; i < SENSOR_COUNT; i++) {
      Serial.print(sensorVal[i]); 
      Serial.print(","); 
    }
    Serial.println();
}

void randomizeSensorValues() {  
    for(int i = 0; i < SENSOR_COUNT; i++) {
      sensorVal[i] = random(1024);
    }
}

void powerHold() {
  if(remoteSensorVal < 1) {
    lastTime = millis();
  }
  if(millis() - lastTime < 60){
    isOn = true;
  } else {
    isOn = false;
  }
}

void powerToggle() {
  if(remoteSensorVal < 1) {
    if(millis() - lastTime > 80) {
      isOn = !isOn;
    }
    lastTime = millis();
  }
}

void powerLed(){
  if(isOn){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    for(int i = 0; i < SENSOR_COUNT; i++) {
      digitalWrite(ledPin[i], LOW);
    }
    digitalWrite(leftLedPin, LOW);
    digitalWrite(rightLedPin, LOW);
  }
}

int getScore(){
  return (-2) * sensorVal[0] + (-1) * sensorVal[1] + sensorVal[3] + 2 * sensorVal[4];
}

void blinker(){
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
}

void steer(){
  double normalizedScore = (double) score / 1024 / 3;
  if(score > DIRECTION_THRESHOLD){
    analogWrite(rightMotorPin, SPEED_MAX * (1 - normalizedScore));
    analogWrite(leftMotorPin, SPEED_MAX);
  }else if(score < -DIRECTION_THRESHOLD){
    analogWrite(leftMotorPin, SPEED_MAX * (1 + normalizedScore));
    analogWrite(rightMotorPin, SPEED_MAX);
  }
}

void showDirection(){
  digitalWrite(leftLedPin, LOW);
  digitalWrite(rightLedPin, LOW);
  if(score > DIRECTION_THRESHOLD){
    digitalWrite(rightLedPin, HIGH);
  } else if(score < -DIRECTION_THRESHOLD){
    digitalWrite(leftLedPin, HIGH);
  }
  
}

