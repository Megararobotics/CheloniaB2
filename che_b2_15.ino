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

// IR sensor pin definitions
#define LSP 22  // Left sensor pin
#define RSP 23  // Right sensor pin

// Ultrasonic sensor pin definitions
#define trigPin 16
#define echoPin 17

// Distance thresholds
#define MIN_DISTANCE 10  // Minimum distance to stop
#define MAX_DISTANCE 50  // Maximum distance for following

void setup() {
  // Set motor pins as outputs
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

  // Set sensor pins
  pinMode(LSP, INPUT);
  pinMode(RSP, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Measure distance using ultrasonic sensor
  long distance = measureDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  // Read IR sensor values
  int leftSensor = digitalRead(LSP);
  int rightSensor = digitalRead(RSP);
  Serial.print("LSD: ");
  Serial.println(leftSensor);
  Serial.print("RSD: ");
  Serial.println(rightSensor);

  // Robot movement logic
  if (distance < MIN_DISTANCE) {
    stopRobot();  // Stop if the object is too close
  } else if (leftSensor == 0 && rightSensor == 1) {
    turnLeft();  // Turn left if only the left sensor detects an object
  } else if (leftSensor == 1 && rightSensor == 0) {
    turnRight();  // Turn right if only the right sensor detects an object
  } else if (distance >= MIN_DISTANCE && distance <= MAX_DISTANCE) {
    moveForward();  // Move forward if within the specified distance range
  } else {
    stopRobot();  // Stop in all other cases
  }
  delay(100);  // Small delay between iterations
}

// Function to measure distance using ultrasonic sensor
long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration * 0.034) / 2;
  return distance;
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
  analogWrite(EN_1, 100);
  analogWrite(EN_2, 100);
  analogWrite(EN_3, 100);
  analogWrite(EN_4, 100);
}

// Function to stop the robot
void stopRobot() {
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
  analogWrite(EN_1, 100);
  analogWrite(EN_2, 100);
  analogWrite(EN_3, 100);
  analogWrite(EN_4, 100);
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
  analogWrite(EN_1, 100);
  analogWrite(EN_2, 100);
  analogWrite(EN_3, 100);
  analogWrite(EN_4, 100);
}
