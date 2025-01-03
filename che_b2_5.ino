#define TRIG_1 14  // Trigger pin for Front Downward-Facing Ultrasonic Sensor
#define ECHO_1 15  // Echo pin for Front Downward-Facing Ultrasonic Sensor
#define TRIG_2 16  // Trigger pin for Right Downward-Facing Ultrasonic Sensor
#define ECHO_2 17  // Echo pin for Right Downward-Facing Ultrasonic Sensor
#define TRIG_3 18  // Trigger pin for Left Downward-Facing Ultrasonic Sensor
#define ECHO_3 19  // Echo pin for Left Downward-Facing Ultrasonic Sensor

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


#define SAFE_DISTANCE 10  // Distance in cm to consider as safe from the ground

long duration;
int distance1, distance2, distance3;

void setup() {
  pinMode(TRIG_1, OUTPUT);
  pinMode(ECHO_1, INPUT);
  pinMode(TRIG_2, OUTPUT);
  pinMode(ECHO_2, INPUT);
  pinMode(TRIG_3, OUTPUT);
  pinMode(ECHO_3, INPUT);

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

  Serial.begin(9600);
}

void loop() {
  distance1 = getDistance(TRIG_1, ECHO_1);
  distance2 = getDistance(TRIG_2, ECHO_2);
  distance3 = getDistance(TRIG_3, ECHO_3);

  // Print distances to the Serial Monitor
  Serial.print("Distance 1 (Front): ");
  Serial.print(distance1);
  Serial.println(" cm");

  Serial.print("Distance 2 (Right): ");
  Serial.print(distance2);
  Serial.println(" cm");

  Serial.print("Distance 3 (Left): ");
  Serial.print(distance3);
  Serial.println(" cm");

  // If any sensor detects a distance greater than SAFE_DISTANCE, stop the robot
  if (distance1 > SAFE_DISTANCE || distance2 > SAFE_DISTANCE || distance3 > SAFE_DISTANCE) {
    moveForward();
    Serial.println("Moving forward...");

  } else {
    stopMotors();
    Serial.println("Stair detected! Stopping...");
  }

  delay(100);  // Delay for sensor reading stability
}

int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;  // Calculating distance in cm
}

void moveForward() {
  // Moving forward by setting the appropriate pins high
  digitalWrite(IN_11, LOW);
  digitalWrite(IN_12, HIGH);
  digitalWrite(IN_13, HIGH);
  digitalWrite(IN_14, LOW);
  analogWrite(EN_1, 255);
  analogWrite(EN_2, 255);

  digitalWrite(IN_21, HIGH);
  digitalWrite(IN_22, LOW);
  digitalWrite(IN_23, HIGH);
  digitalWrite(IN_24, LOW);
  analogWrite(EN_3, 255);
  analogWrite(EN_4, 255);
}

void stopMotors() {
  // Stopping the motors by setting all pins low
  digitalWrite(IN_11, LOW);
  digitalWrite(IN_12, LOW);
  digitalWrite(IN_13, LOW);
  digitalWrite(IN_14, LOW);
  analogWrite(EN_1, 0);
  analogWrite(EN_2, 0);

  digitalWrite(IN_21, LOW);
  digitalWrite(IN_22, LOW);
  digitalWrite(IN_23, LOW);
  digitalWrite(IN_24, LOW);
  analogWrite(EN_3, 0);
  analogWrite(EN_4, 0);
}
