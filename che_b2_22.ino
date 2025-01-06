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
#define IR_SENSOR_1 22  // Signal pin for IR Sensor 1 (Left)
#define IR_SENSOR_2 23  // Signal pin for IR Sensor 2 (Right)

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

  // Set IR sensor pins as input
  pinMode(IR_SENSOR_1, INPUT);
  pinMode(IR_SENSOR_2, INPUT);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read IR sensor values (Digital: HIGH = no line, LOW = line detected)
  int irValue1 = digitalRead(IR_SENSOR_1);  // Left sensor
  int irValue2 = digitalRead(IR_SENSOR_2);  // Right sensor

  // Print sensor values to serial monitor
  Serial.print("IR Sensor 1 (Left) Value: ");
  Serial.println(irValue1);
  Serial.print("IR Sensor 2 (Right) Value: ");
  Serial.println(irValue2);

  // Line following logic
  if (irValue1 == HIGH && irValue2 == HIGH) {
    moveForward();  // Both sensors on the line
  } else {
    stopMotors();  // Both sensors off the line, stop or adjust behavior
  }

  delay(100);  // Small delay between readings
}

// Function to move the Chelonia Bot forward
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

// Function to stop the Chelonia Bot
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
