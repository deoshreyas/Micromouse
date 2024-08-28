#include <NewPing.h>

#define FRONT_TRIG_PIN A1
#define FRONT_ECHO_PIN A4
/* #define LEFT_TRIG_PIN A0
#define LEFT_ECHO_PIN A3
#define RIGHT_TRIG_PIN A2
#define RIGHT_ECHO_PIN A5 */

#define MOTOR_IN1 2
#define MOTOR_IN2 3
#define MOTOR_IN3 4
#define MOTOR_IN4 5
#define MOTOR_ENA 10
#define MOTOR_ENB 11

const int OBJECT_DETECTION_THRESHOLD = 10; // cm

NewPing front_sonar(FRONT_TRIG_PIN, FRONT_ECHO_PIN, OBJECT_DETECTION_THRESHOLD);

void setup() {
  // Initialize motors
  analogWrite(MOTOR_ENA, 255); // Full speed
  analogWrite(MOTOR_ENB, 255); // Full speed

  stop();
}

void loop() {
  int front_dst = front_sonar.ping_cm();
  if (front_dst>0) {
    // Object detected
    stop();
    delay(200);
    turnLeft();
    delay(500);
    moveForward();
  } else {
    // Keep going 
    moveForward();
    delay(100);
  }
}

void moveForward() {
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  digitalWrite(MOTOR_IN3, HIGH);
  digitalWrite(MOTOR_IN4, LOW);
}

void turnLeft() {
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  digitalWrite(MOTOR_IN3, LOW);
  digitalWrite(MOTOR_IN4, LOW);
}

void stop() {
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  digitalWrite(MOTOR_IN3, LOW);
  digitalWrite(MOTOR_IN4, LOW);
}