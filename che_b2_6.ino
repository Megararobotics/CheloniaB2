#include <MPU6050_light.h>
#include <Wire.h>
//#include <SoftwareSerial.h>

// Initialize the IMU
MPU6050 mpu(Wire);

// Bluetooth module connected to pins 1 (TX) and 0 (RX)
//SoftwareSerial BTSerial(1, 0);

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

void setup() {
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets();
  // Calibrate the gyro, hold the robot still during calibration

  // Initialize motor control pins as outputs
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

  //BTSerial.begin(9600);  // Initialize Bluetooth Serial communication
  Serial.begin(9600);  // Initialize Serial communication for debugging
}

void loop() {
  mpu.update();  // Update IMU data

  // Move forward
  digitalWrite(IN_11, LOW);
  digitalWrite(IN_12, HIGH);
  digitalWrite(IN_13, HIGH);
  digitalWrite(IN_14, LOW);
  digitalWrite(IN_21, HIGH);
  digitalWrite(IN_22, LOW);
  digitalWrite(IN_23, HIGH);
  digitalWrite(IN_24, LOW);

  // Enable all motors
  analogWrite(EN_1, 255);  // Full speed for front motors
  analogWrite(EN_2, 255);  // Full speed for front motors
  analogWrite(EN_3, 255);  // Full speed for back motors
  analogWrite(EN_4, 255);  // Full speed for back motors

  // Send IMU data to Bluetooth Serial Monitor app
  Serial.print("Angle X: ");
  Serial.print(mpu.getAngleX());
  Serial.print(" | Angle Y: ");
  Serial.print(mpu.getAngleY());
  Serial.print(" | Angle Z: ");
  Serial.println(mpu.getAngleZ());

  delay(100);  // Short delay to stabilize readings
}
