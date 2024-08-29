#include <NewPing.h>

#define FRONT_TRIG_PIN A4
#define FRONT_ECHO_PIN A1
#define LEFT_TRIG_PIN A3
#define LEFT_ECHO_PIN A0
#define RIGHT_TRIG_PIN A5
#define RIGHT_ECHO_PIN A2

#define MOTOR_IN1 2
#define MOTOR_IN2 3
#define MOTOR_IN3 4
#define MOTOR_IN4 5
#define MOTOR_ENA 10
#define MOTOR_ENB 11

const int FRONT_WALL_DETECTION_THRESHOLD = 13; // cm, detects walls 
const int SIDE_WALL_DETECTION_THRESHOLD = 7; // cm, detects left and right wall for straight movement

NewPing front_sonar(FRONT_TRIG_PIN, FRONT_ECHO_PIN, FRONT_WALL_DETECTION_THRESHOLD);
NewPing left_sonar(LEFT_TRIG_PIN, LEFT_ECHO_PIN, SIDE_WALL_DETECTION_THRESHOLD);
NewPing right_sonar(RIGHT_TRIG_PIN, RIGHT_ECHO_PIN, SIDE_WALL_DETECTION_THRESHOLD);

void setup() {
  // Initialize motors
  analogWrite(MOTOR_ENA, 150); // Less speed while moving
  analogWrite(MOTOR_ENB, 150); // Less speed while moving
  // TODO: Increase speed while turning

  stop();
}

void loop() {
  int front_dst = front_sonar.ping_cm();
  int left_dst = left_sonar.ping_cm();
  int right_dst = right_sonar.ping_cm();
  if (front_dst==0) { // Front is clear
    moveForward();
    delay(100);
  } else if (left_dst==0) { // Left is clear
    turnLeft();
    delay(250);
    moveForward();
  } else if (right_dst==0) { // Right is clear
    turnRight();
    delay(250);
    moveForward();
  } else { // Turn left in case no other option is there
    turnLeft();
    delay(250);
    moveForward();
  }
  delay(100);
  // Move away if too close to walls 
  if (left_dst==1) {
    turnRight();
    delay(50);
  } else if (right_dst==1) {
    turnLeft();
    delay(50);
  }
}

void moveForward() {
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, HIGH);
  digitalWrite(MOTOR_IN3, LOW);
  digitalWrite(MOTOR_IN4, HIGH);
}

/* NOTE: While turning, I am reversing the direction of the wheel on the 
side being turned to. I believe this will aid in faster and more 
efficient turns. */

void turnLeft() {
  analogWrite(MOTOR_ENA, 255);
  analogWrite(MOTOR_ENB, 255); 
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  digitalWrite(MOTOR_IN3, LOW);
  digitalWrite(MOTOR_IN4, HIGH);
}

void turnRight() {
  analogWrite(MOTOR_ENA, 255);
  analogWrite(MOTOR_ENB, 255); 
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, HIGH);
  digitalWrite(MOTOR_IN3, HIGH);
  digitalWrite(MOTOR_IN4, LOW);
}

void stop() {
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  digitalWrite(MOTOR_IN3, LOW);
  digitalWrite(MOTOR_IN4, LOW);
}