#define BAUD_RATE 9600
#define SENSOR_COUNT 5

/**SensorPins : left to right**/
int sensorPin[SENSOR_COUNT] = {A1, A2, A3, A4, A5};
int sensorVal[SENSOR_COUNT];
int ledPin[SENSOR_COUNT] = {2,3,4,5,6};
int leftLedPin = 8;
int rightLedPin = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD_RATE);
  for(int i = 0; i < SENSOR_COUNT; i++) {
    pinMode(sensorPin[i],OUTPUT);
  }
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(leftLedPin, OUTPUT);
  pinMode(rightLedPin, OUTPUT);
}

void loop() {

//  for(int i = 0; i < SENSOR_COUNT; 
  
  // read sensors data
  for(int i = 0; i < SENSOR_COUNT; i++) {
    sensorVal[i] = analogRead(sensorPin[i]);
  }
//  blinker();
  displayLeds();
  showDirection();
  
//  Serial.println(analogRead(A1)); 
  Serial.println(analogRead(A2));
//  Serial.println(analogRead(A3));
//  Serial.println(analogRead(A4));
//  Serial.println(analogRead(A5));
}

void displayLeds(){
  for(int i = 0; i < SENSOR_COUNT; i++) {
    if(sensorVal[i] > 300)
      digitalWrite(ledPin[i], HIGH);
    else
      digitalWrite(ledPin[i], LOW);
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

void showDirection(){
  int score = getScore();
  digitalWrite(leftLedPin, LOW);
  digitalWrite(rightLedPin, LOW);
  if(score > 1000){
    digitalWrite(rightLedPin, HIGH);
  } else if(score < -1000){
    digitalWrite(leftLedPin, HIGH);
  }
  
}

