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
int leftLedPin = 7;
int rightLedPin = 8;
int remoteSensorPin = 13;
int remoteSensorVal;
unsigned long lastTime;
boolean(isOn);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(remoteSensorPin, INPUT);
  digitalWrite(LED_BUILTIN, LOW);
  lastTime = millis();
  isOn = true;
}

void loop() {
  remoteSensorVal = digitalRead(remoteSensorPin);
  Serial.println(remoteSensorVal);
//  buttonPressed();
  if(powerSwitch()) {
    togglePower();
  }
//  if(buttonPressed()) {
  if(isOn) {
//    for(int i = 0; i < SENSOR_COUNT; i++) {
//      sensorVal[i] = analogRead(sensorPin[i]);
//      Serial.print(sensorVal[i]); 
//      Serial.print(","); 
//    }
//    Serial.println();
    int score = getScore();
//    Serial.println(score);
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
  if(millis() - lastTime < 50){
    isOn = true;
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    isOn = false;
    digitalWrite(LED_BUILTIN, LOW);
  }
}

//void buttonPressed() {
////  Serial.println(remoteSensorVal);
//  if(remoteSensorVal < 1) {
//    isOn = true;
//    digitalWrite(LED_BUILTIN, HIGH);
//  } else {
//    isOn = false;
//    digitalWrite(LED_BUILTIN, LOW);
//  }
//}

boolean powerSwitch() {
  if(remoteSensorVal < 1) {
    if(millis() - lastTime > 300) {
      isOn = !isOn;
      return true;
    }
    lastTime = millis();
  }
  return false;
}

void togglePower(){
  if(isOn){
    isOn = true;
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
    isOn = false;
    digitalWrite(LED_BUILTIN,LOW);
  }
}

int getScore(){
  return (-2) * sensorVal[0] + (-1) * sensorVal[1] + sensorVal[3] + 2 * sensorVal[4];
}

//void blinker(){
//  digitalWrite(LED_BUILTIN, LOW);
//  delay(500);
//  digitalWrite(LED_BUILTIN, HIGH);
//  delay(500);
//}
//
////void steer(int score){
////  double normalizedScore = (double) score / 1500;
////  analogWrite(leftMotorPin, SPEED_MAX);
////  analogWrite(rightMotorPin, SPEED_MAX);
////  if(score > DIRECTION_THRESHOLD){
////    analogWrite(rightMotorPin, SPEED_MAX * (1 - normalizedScore));
////  }else if(score < -DIRECTION_THRESHOLD){
////    analogWrite(leftMotorPin, SPEED_MAX * (1 + normalizedScore));
////  }
////}
//
void showDirection(int score){
  digitalWrite(leftLedPin, LOW);
  digitalWrite(rightLedPin, LOW);
  if(score > DIRECTION_THRESHOLD){
    digitalWrite(rightLedPin, HIGH);
  } else if(score < -DIRECTION_THRESHOLD){
    digitalWrite(leftLedPin, HIGH);
  }
  
}

