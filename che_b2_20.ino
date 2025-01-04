// Pin Definitions
#define BUZZER_PIN 26       // Buzzer connected to digital pin 26
#define Fire_SENSOR_PIN A0  // Fire sensor connected to analog pin A1 (Pin 28 in analogRead() is A1)

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


// Threshold for detecting Fire
#define Fire_THRESHOLD 100

void setup() {
  Serial.begin(9600);           // Start serial communication
  pinMode(BUZZER_PIN, OUTPUT);  // Set buzzer pin as output

  // Set motor control pins as output
  pinMode(IN_11, OUTPUT);
  pinMode(IN_12, OUTPUT);
  pinMode(IN_13, OUTPUT);
  pinMode(IN_14, OUTPUT);
  pinMode(IN_21, OUTPUT);
  pinMode(IN_22, OUTPUT);
  pinMode(IN_23, OUTPUT);
  pinMode(IN_24, OUTPUT);
  pinMode(EN_1, OUTPUT);
  pinMode(EN_2, OUTPUT);
  pinMode(EN_3, OUTPUT);
  pinMode(EN_4, OUTPUT);

  // Initialize motors to stop
  stopMotors();

  Serial.println("Fire detecting robot initialized. Monitoring Fire levels...");
}

void loop() {
  int FireValue = analogRead(Fire_SENSOR_PIN);  // Read Fire sensor value
  Serial.print("Fire Sensor Value: ");
  Serial.println(FireValue);

  if (FireValue > Fire_THRESHOLD) {  // Check if Fire level exceeds threshold
    Serial.println("Fire Detected!");
    digitalWrite(BUZZER_PIN, HIGH);  // Activate buzzer
    stopMotors();                    // Stop the robot
  } else {
    digitalWrite(BUZZER_PIN, LOW);  // Deactivate buzzer
    Serial.println("No Fire Detected!");
    moveForward();  // Move the robot forward if no Fire detected
  }

  delay(1000);  // Delay for stability and to avoid too frequent readings
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
  analogWrite(EN_1, 200);
  analogWrite(EN_2, 200);
  analogWrite(EN_3, 200);
  analogWrite(EN_4, 200);
}

// Function to stop the robot
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
