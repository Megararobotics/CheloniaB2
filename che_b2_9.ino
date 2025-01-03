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


// Sensor and Buzzer Pin Definitions
#define trigPin 16    // Ultrasonic sensor Trig pin
#define echoPin 17    // Ultrasonic sensor Echo pin
#define buzzerPin 26  // Buzzer pin

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

  // Set sensor and buzzer pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initialize Serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Measure distance using the ultrasonic sensor
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;  // Convert the time to distance in centimeters

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 20 && distance > 0) {  // If the obstacle is detected within 20 cm
    stopMovement();                     // Stop the robot
    buzzBuzzer(100);                    // Activate buzzer with 100ms beep
  } else {
    moveForward();  // Otherwise, keep moving forward
  }

  delay(200);  // Delay between distance measurements
}

void moveForward() {
  // Front Right Motor
  digitalWrite(IN_11, LOW);
  digitalWrite(IN_12, HIGH);
  // Front Left Motor
  digitalWrite(IN_13, HIGH);
  digitalWrite(IN_14, LOW);
  // Back Right Motor
  digitalWrite(IN_23, HIGH);
  digitalWrite(IN_24, LOW);
  // Back Left Motor
  digitalWrite(IN_21, HIGH);
  digitalWrite(IN_22, LOW);

  // Enable all motors
  digitalWrite(EN_1, HIGH);
  digitalWrite(EN_2, HIGH);
  digitalWrite(EN_3, HIGH);
  digitalWrite(EN_4, HIGH);
}

void stopMovement() {
  // Stop all motors
  digitalWrite(IN_11, LOW);
  digitalWrite(IN_12, LOW);
  digitalWrite(IN_13, LOW);
  digitalWrite(IN_14, LOW);
  digitalWrite(IN_23, LOW);
  digitalWrite(IN_24, LOW);
  digitalWrite(IN_21, LOW);
  digitalWrite(IN_22, LOW);

  // Disable all motors
  digitalWrite(EN_1, LOW);
  digitalWrite(EN_2, LOW);
  digitalWrite(EN_3, LOW);
  digitalWrite(EN_4, LOW);
}

void buzzBuzzer(int duration) {
  digitalWrite(buzzerPin, HIGH);
  delay(duration);
  digitalWrite(buzzerPin, LOW);
  delay(duration);
}
