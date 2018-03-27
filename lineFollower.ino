#define BAUD_RATE 9600
#define SENSOR_COUNT 5
#define DIRECTION_THRESHOLD 200
#define WHITE_THRESHOLD 400
#define BLACK_THRESHOLD 150
#define SPEED_MAX 255
#define SPEED_MIN 0

//  int In3 = 8;
//  int In4 = 6;
//  int leftMotorPin = 5;
//
//  int In1 = 4;
//  int In2 = 2;
//  int RightMotorPin = 3;

/**SensorPins : left to right**/
int sensorPin[SENSOR_COUNT] = {A1, A2, A3, A4, A5};
int sensorVal[SENSOR_COUNT];
int ledPin[SENSOR_COUNT] = {2,3,4,5,6};
int leftLedPin = 8;
int rightLedPin = 9;
int remoteSensorPin = LED_BUILTIN;
int remoteSensorVal;
unsigned long lastTime;
unsigned long currentTime;
boolean(isOn);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  digitalWrite(LED_BUILTIN, LOW);
  isOn = false;
}

void loop() {
  remoteSensorVal = digitalRead(remoteSensorPin);
  if(powerSwitch()) {
    togglePower();
  }
//  if(buttonPressed()) {
  if(isOn) {
    // read sensors data
    for(int i = 0; i < SENSOR_COUNT; i++) {
      sensorVal[i] = analogRead(sensorPin[i]);
      Serial.print(sensorVal[i]); 
      Serial.print(","); 
    }
    Serial.println();
  //  blinker();
    int score = getScore();
    displayLeds();
    showDirection(score);
  //  steer(score);
  }
}

void displayLeds(){
  for(int i = 0; i < SENSOR_COUNT; i++) {
    if(sensorVal[i] > 400)
      digitalWrite(ledPin[i], HIGH);
    else
      digitalWrite(ledPin[i], LOW);
  }
}

void buttonPressed() {
  if(remoteSensorVal < 1) {
    lastTime = millis();
  }
  if(millis() - lastTime < 5)
    digitalWrite(7, HIGH);
  else
    digitalWrite(7, LOW);
}

boolean powerSwitch() {
  if(remoteSensorVal < 1) {
    currentTime = millis();
    if(currentTime - lastTime > 300) {
      lastTime = currentTime;
      isOn = !isOn;
      return true;
    }
  }
  return false;
}

void togglePower(){
  int ledState = digitalRead(7);
  if(isOn){
    isOn = false;
    digitalWrite(remoteSensorPin, LOW);
  }
  else {
    isOn = true;
    digitalWrite(remoteSensorPin,HIGH);
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

//void steer(int score){
//  double normalizedScore = (double) score / 1500;
//  analogWrite(leftMotorPin, SPEED_MAX);
//  analogWrite(rightMotorPin, SPEED_MAX);
//  if(score > DIRECTION_THRESHOLD){
//    analogWrite(rightMotorPin, SPEED_MAX * (1 - normalizedScore));
//  }else if(score < -DIRECTION_THRESHOLD){
//    analogWrite(leftMotorPin, SPEED_MAX * (1 + normalizedScore));
//  }
//}

void showDirection(int score){
  digitalWrite(leftLedPin, LOW);
  digitalWrite(rightLedPin, LOW);
  if(score > DIRECTION_THRESHOLD){
    digitalWrite(rightLedPin, HIGH);
  } else if(score < -DIRECTION_THRESHOLD){
    digitalWrite(leftLedPin, HIGH);
  }
  
}

