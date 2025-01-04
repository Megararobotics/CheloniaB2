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


// IR Sensor Pin Definition
#define IR_SENSOR_PIN 22

void setup() {
  // Motor Pins Setup
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

  // Initialize Serial Communication
  Serial.begin(9600);
}

void loop() {
  // Read the value from the IR sensor
  int irValue = digitalRead(IR_SENSOR_PIN);

  // Print the IR sensor value to the Serial Monitor
  Serial.print("IR Sensor Value: ");
  Serial.println(irValue);

  // Check if the IR sensor value is below the threshold
  if (irValue == LOW) {
    // Obstacle detected: Stop the robot
    stopMotors();
    Serial.println("Obstacle Detected: Stopped");
  } else {
    // No obstacle detected: Move the robot forward
    moveForward();
    Serial.println("No Obstacle: Moving Forward");
  }

  delay(100);  // Short delay to allow sensor reading stability
}

// Function to move the robot forward
void moveForward() {
  // Front Right motor
  digitalWrite(IN_11, LOW);
  digitalWrite(IN_12, HIGH);
  // Front Left motor
  digitalWrite(IN_13, HIGH);
  digitalWrite(IN_14, LOW);
  // Back Right motor
  digitalWrite(IN_23, HIGH);
  digitalWrite(IN_24, LOW);
  // Back Left motor
  digitalWrite(IN_21, HIGH);
  digitalWrite(IN_22, LOW);

  // Set motor speeds (full speed in this case)
  analogWrite(EN_1, 255);
  analogWrite(EN_2, 255);
  analogWrite(EN_3, 255);
  analogWrite(EN_4, 255);
}

// Function to stop the robot
void stopMotors() {
  digitalWrite(IN_11, LOW);
  digitalWrite(IN_12, LOW);
  digitalWrite(IN_13, LOW);
  digitalWrite(IN_14, LOW);
  digitalWrite(IN_21, LOW);
  digitalWrite(IN_22, LOW);
  digitalWrite(IN_23, LOW);
  digitalWrite(IN_24, LOW);

  // Set motor speeds to zero
  analogWrite(EN_1, 0);
  analogWrite(EN_2, 0);
  analogWrite(EN_3, 0);
  analogWrite(EN_4, 0);
}
