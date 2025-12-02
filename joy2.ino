#include <Servo.h>

// set ardiuno port with motor 
#define SERVO_PIN_1 9
#define SERVO_PIN_2 10
#define SERVO_PIN_3 11
#define SERVO_PIN_4 12

// set ardiuno port with joystick
#define JOY1_X_PIN A0
#define JOY1_Y_PIN A1
#define JOY2_X_PIN A2
#define JOY2_Y_PIN A3

// name servo motor 
Servo myServo1;
Servo myServo2;
Servo myServo3;
Servo myServo4;

// set original positio to 0
int currentPosition1 = 0;
int currentPosition2 = 0;
int currentPosition3 = 0;
int currentPosition4 = 0;

// set minimum & maximum angle 0 & 180
const int minPosition = 0;
const int maxPosition = 180;

// Speed settings (1 means 1 degree per update, 2 means 2 degrees, etc.)
int speed1 = 5; // Speed for Servo 1 (slow)
int speed2 = 5; // Speed for Servo 2 (normal)
int speed3 = 6; // Speed for Servo 3 (slow)
int speed4 = 6; // Speed for Servo 4 (normal)

void setup() {
  Serial.begin(9600);
  
  myServo1.attach(SERVO_PIN_1);
  myServo2.attach(SERVO_PIN_2);
  myServo3.attach(SERVO_PIN_3);
  myServo4.attach(SERVO_PIN_4);

  myServo1.write(currentPosition1);
  myServo2.write(currentPosition2);
  myServo3.write(currentPosition3);
  myServo4.write(currentPosition4);
}

void loop() {
  int joy1X = analogRead(JOY1_X_PIN);
  int joy1Y = analogRead(JOY1_Y_PIN);
  int joy2X = analogRead(JOY2_X_PIN);
  int joy2Y = analogRead(JOY2_Y_PIN);

  int targetPosition1 = map(joy1Y, 0, 1023, minPosition, maxPosition);
  int targetPosition2 = map(joy1X, 0, 1023, minPosition, maxPosition);
  int targetPosition3 = map(joy2Y, 0, 1023, minPosition, maxPosition);
  int targetPosition4 = map(joy2X, 0, 1023, minPosition, maxPosition);

  currentPosition1 = moveToTarget(currentPosition1, targetPosition1, speed1);
  currentPosition2 = moveToTarget(currentPosition2, targetPosition2, speed2);
  currentPosition3 = moveToTarget(currentPosition3, targetPosition3, speed3);
  currentPosition4 = moveToTarget(currentPosition4, targetPosition4, speed4);

  myServo1.write(currentPosition1);
  myServo2.write(currentPosition2);
  myServo3.write(currentPosition3);
  myServo4.write(currentPosition4);

  Serial.print("Servo 1: ");
  Serial.print(currentPosition1);
  Serial.print(" | Servo 2: ");
  Serial.print(currentPosition2);
  Serial.print(" | Servo 3: ");
  Serial.print(currentPosition3);
  Serial.print(" | Servo 4: ");
  Serial.println(currentPosition4);

  delay(50);
}

// Function to gradually move to the target position
int moveToTarget(int currentPosition, int targetPosition, int speed) {
  if (currentPosition < targetPosition) {
    currentPosition += speed; // Move up to the speed
    if (currentPosition > targetPosition) currentPosition = targetPosition; // Clamp to target
  } else if (currentPosition > targetPosition) {
    currentPosition -= speed; // Move down to the speed
    if (currentPosition < targetPosition) currentPosition = targetPosition; // Clamp to target
  }
  return currentPosition;
}