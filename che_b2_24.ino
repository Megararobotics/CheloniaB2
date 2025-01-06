#include <NewPing.h>

// Define the motor control pins based on your setup
#define IN_11 2  // L298N #1, IN4 for IN4 for Back Left motor
#define IN_12 3  // L298N #1, IN3 for IN3 for Back Left motor
#define IN_13 4  // L298N #1, IN2 for Back Right motor
#define IN_14 5  // L298N #1, IN1 for Back Right motor
#define EN_1 9   // Enable pin for L298N #1 (Back motors)
#define EN_2 10  // Enable pin for L298N #1 (Back motors)

#define IN_21 13  // L298N #2, IN4 for Front Right motor
#define IN_22 7   // L298N #2, IN3 for Front Right motor
#define IN_23 8   // L298N #2, IN2 for Front Left motor
#define IN_24 12  // L298N #2, IN1 for Front Left motor
#define EN_3 6    // Enable pin for L298N #2 (Front motors)
#define EN_4 11   // Enable pin for L298N #2 (Front motors)


// Define ultrasonic sensor pins
#define LEFT_TRIG_PIN 18
#define LEFT_ECHO_PIN 19
#define FRONT_TRIG_PIN 16
#define FRONT_ECHO_PIN 17
#define RIGHT_TRIG_PIN 14
#define RIGHT_ECHO_PIN 15

// Define distance thresholds
#define FRONT_THRESHOLD 20  // cm
#define SIDE_THRESHOLD 15   // cm

// Define maximum distance for the ultrasonic sensor
#define MAX_DISTANCE 200  // cm

// Create NewPing objects for the ultrasonic sensors
NewPing leftSensor(LEFT_TRIG_PIN, LEFT_ECHO_PIN, MAX_DISTANCE);
NewPing frontSensor(FRONT_TRIG_PIN, FRONT_ECHO_PIN, MAX_DISTANCE);
NewPing rightSensor(RIGHT_TRIG_PIN, RIGHT_ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);  // Start serial communication

  // Initialize motor control pins
  pinMode(IN_11, OUTPUT);
  pinMode(IN_12, OUTPUT);
  pinMode(IN_13, OUTPUT);
  pinMode(IN_14, OUTPUT);
  pinMode(EN_1, OUTPUT);
  pinMode(EN_2, OUTPUT);
  pinMode(IN_21, OUTPUT);
  pinMode(IN_22, OUTPUT);
  pinMode(IN_23, OUTPUT);
  pinMode(IN_24, OUTPUT);
  pinMode(EN_3, OUTPUT);
  pinMode(EN_4, OUTPUT);

  Serial.println("Maze Solving Robot Initialized.");
}

void loop() {
  delay(50);  // Small delay to allow sensors to stabilize

  // Read distances from ultrasonic sensors
  unsigned int leftDistance = leftSensor.ping_cm();
  unsigned int frontDistance = frontSensor.ping_cm();
  unsigned int rightDistance = rightSensor.ping_cm();

  // Print distances to the serial monitor
  Serial.print("Left: ");
  Serial.print(leftDistance);
  Serial.print(" cm, Front: ");
  Serial.print(frontDistance);
  Serial.print(" cm, Right: ");
  Serial.print(rightDistance);
  Serial.println(" cm");

  if (frontDistance < FRONT_THRESHOLD) {  // Obstacle detected in front
    if (leftDistance > rightDistance) {
      turnLeft();  // Otherwise, turn left
      Serial.println("Moving left");
    } else {
      turnRight();  // Prefer to turn right if left side is clearer
      Serial.println("Moving right");
    }
  } else {
    moveForward();  // Move forward if no obstacle detected in front
    Serial.println("Moving Forward");
  }
}

// Function to move the robot forward
void moveForward() {
  digitalWrite(IN_11, LOW);
  digitalWrite(IN_12, HIGH);
  digitalWrite(IN_13, HIGH);
  digitalWrite(IN_14, LOW);
  digitalWrite(IN_24, LOW);
  digitalWrite(IN_23, HIGH);
  digitalWrite(IN_22, LOW);
  digitalWrite(IN_21, HIGH);
  analogWrite(EN_1, 150);
  analogWrite(EN_2, 150);
  analogWrite(EN_3, 150);
  analogWrite(EN_4, 150);
}

// Function to turn the robot left
void turnLeft() {
  digitalWrite(IN_11, HIGH);
  digitalWrite(IN_12, LOW);
  digitalWrite(IN_13, HIGH);
  digitalWrite(IN_14, LOW);
  digitalWrite(IN_24, LOW);
  digitalWrite(IN_23, HIGH);
  digitalWrite(IN_22, HIGH);
  digitalWrite(IN_21, LOW);
  analogWrite(EN_1, 60);
  analogWrite(EN_2, 60);
  analogWrite(EN_3, 60);
  analogWrite(EN_4, 60);
  delay(500);  // Turn for 0.5 seconds
  stopMotors();
}

// Function to turn the robot right
void turnRight() {
  digitalWrite(IN_11, LOW);
  digitalWrite(IN_12, HIGH);
  digitalWrite(IN_13, LOW);
  digitalWrite(IN_14, HIGH);
  digitalWrite(IN_24, HIGH);
  digitalWrite(IN_23, LOW);
  digitalWrite(IN_22, LOW);
  digitalWrite(IN_21, HIGH);
  analogWrite(EN_1, 60);
  analogWrite(EN_2, 60);
  analogWrite(EN_3, 60);
  analogWrite(EN_4, 60);
  delay(500);  // Turn for 0.5 seconds
  stopMotors();
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(IN_11, LOW);
  digitalWrite(IN_12, LOW);
  digitalWrite(IN_13, LOW);
  digitalWrite(IN_14, LOW);
  digitalWrite(IN_24, LOW);
  digitalWrite(IN_23, LOW);
  digitalWrite(IN_22, LOW);
  digitalWrite(IN_21, LOW);
  analogWrite(EN_1, 0);
  analogWrite(EN_2, 0);
  analogWrite(EN_3, 0);
  analogWrite(EN_4, 0);
}
