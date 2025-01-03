
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


// Speed variable
int speedValue = 0;

void setup() {
  // Initialize motor pins
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

  // Start serial communication
  Serial.begin(9600);

  // Stop motors initially
  stopMotors();
}

void loop() {
  if (Serial.available() > 0) {
    // Read the incoming speed value
    speedValue = Serial.parseInt();

    // If speedValue is greater than 0, move forward
    if (speedValue > 0) {
      moveForward(speedValue);
    } else {
      stopMotors();
    }
  }
}

// Function to move the robot forward
void moveForward(int speed) {
  // Front Right Motor
  analogWrite(EN_1, speed);
  digitalWrite(IN_11, LOW);
  digitalWrite(IN_12, HIGH);

  // Front Left Motor
  analogWrite(EN_2, speed);
  digitalWrite(IN_13, HIGH);
  digitalWrite(IN_14, LOW);

  // Back Left Motor
  analogWrite(EN_3, speed);
  digitalWrite(IN_21, HIGH);
  digitalWrite(IN_22, LOW);

  // Back Right Motor
  analogWrite(EN_4, speed);
  digitalWrite(IN_23, HIGH);
  digitalWrite(IN_24, LOW);
}

// Function to stop the robot
void stopMotors() {
  // Stop Front Right Motor
  analogWrite(EN_1, 0);
  digitalWrite(IN_11, LOW);
  digitalWrite(IN_12, LOW);

  // Stop Front Left Motor
  analogWrite(EN_2, 0);
  digitalWrite(IN_13, LOW);
  digitalWrite(IN_14, LOW);

  // Stop Back Left Motor
  analogWrite(EN_3, 0);
  digitalWrite(IN_21, LOW);
  digitalWrite(IN_22, LOW);

  // Stop Back Right Motor
  analogWrite(EN_4, 0);
  digitalWrite(IN_23, LOW);
  digitalWrite(IN_24, LOW);
}