#include <DHT.h>
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


// Temperature Sensor (DHT11) Pin Definitions
#define DHTPIN 25      // DHT sensor connected to digital pin 25
#define DHTTYPE DHT11  // DHT11 sensor type

DHT dht(DHTPIN, DHTTYPE);  // Initialize DHT sensor

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

  // DHT Sensor Setup
  dht.begin();

  Serial.begin(9600);  // Initialize serial communication
}

void loop() {

  moveForward();
  // Get Temperature and Humidity Readings
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
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
  delay(500);  // Adjust the delay for turn duration
  stopMotors();
}
