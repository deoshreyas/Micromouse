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

const int FRONT_WALL_DETECTION_THRESHOLD = 1; // cm, detects walls 
const int SIDE_WALL_DETECTION_THRESHOLD = 5; // cm, detects left and right wall for straight movement

int turn_right_chance = 20; // initially, start with a 20% chance of turning right at intersection (decreases by 1% every time right turned)
 
NewPing front_sonar(FRONT_TRIG_PIN, FRONT_ECHO_PIN, FRONT_WALL_DETECTION_THRESHOLD);
NewPing left_sonar(LEFT_TRIG_PIN, LEFT_ECHO_PIN, SIDE_WALL_DETECTION_THRESHOLD);
NewPing right_sonar(RIGHT_TRIG_PIN, RIGHT_ECHO_PIN, SIDE_WALL_DETECTION_THRESHOLD);

void setup() {
  // Initialize motors
  analogWrite(MOTOR_ENA, 255); // Full speed
  analogWrite(MOTOR_ENB, 255); // Full speed

  stop();
}

void loop() {
  int front_dst = front_sonar.ping_cm();
  int left_dst = left_sonar.ping_cm();
  int right_dst = right_sonar.ping_cm();
  if (front_dst==0) { // Front is clear
    moveForward();
  } else if (left_dst==0 && right_dst==0) {
    int rand_val = random(1, 100); 
    bool should_turn_right = rand_val <=  turn_right_chance;
    if (should_turn_right) {
      turnRight();
      moveForward();
    }
  }
  } else if (left_dst==0) { // Left is clear
    turnLeft();
    moveForward();
  } else if (right_dst==0) { // Right is clear
    turnRight();
    moveForward();
  } else { // Turn left in case no other option is there
    turnLeft();
  }
  delay(100);
}

void moveForward() {
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, HIGH);
  digitalWrite(MOTOR_IN3, LOW);
  digitalWrite(MOTOR_IN4, HIGH);
}

void turnLeft() {
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  digitalWrite(MOTOR_IN3, LOW);
  digitalWrite(MOTOR_IN4, HIGH);
}

void turnRight() {
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, HIGH);
  digitalWrite(MOTOR_IN3, LOW);
  digitalWrite(MOTOR_IN4, LOW);
}

void stop() {
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  digitalWrite(MOTOR_IN3, LOW);
  digitalWrite(MOTOR_IN4, LOW);
}