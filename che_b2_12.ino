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


// Ultrasonic sensor pins
const int trigPin = 16;
const int echoPin = 17;

void setup() {
  // Set motor pins as output
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

  // Set ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Measure distance
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;  // Calculate distance in cm

  // Print distance to serial
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Control motor speed based on distance
  if (distance >= 80) {
    moveForward(255);  // Full speed
  } else if (distance >= 50 && distance < 80) {
    moveForward(175);  // Medium speed
  } else if (distance >= 10 && distance < 50) {
    moveForward(100);  // Slow speed
  } else if (distance < 10) {
    stopMotors();  // Stop
  }

  delay(100);  // Small delay between measurements
}

// Function to move the Chelonia Bot forward
void moveForward(int speed) {
  analogWrite(EN_1, speed);
  analogWrite(EN_2, speed);
  analogWrite(EN_3, speed);
  analogWrite(EN_4, speed);

  digitalWrite(IN_11, LOW);
  digitalWrite(IN_12, HIGH);
  digitalWrite(IN_13, HIGH);
  digitalWrite(IN_14, LOW);
  digitalWrite(IN_21, HIGH);
  digitalWrite(IN_22, LOW);
  digitalWrite(IN_23, HIGH);
  digitalWrite(IN_24, LOW);
}

// Function to stop the Chelonia Bot
void stopMotors() {
  analogWrite(EN_1, 0);
  analogWrite(EN_2, 0);
  analogWrite(EN_3, 0);
  analogWrite(EN_4, 0);
}
