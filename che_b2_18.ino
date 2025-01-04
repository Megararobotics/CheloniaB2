#include <PID_v1.h>

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


#define FRONT_TRIG 16  // Front ultrasonic sensor trigger pin
#define FRONT_ECHO 17  // Front ultrasonic sensor echo pin
#define LEFT_TRIG 18   // Left ultrasonic sensor trigger pin
#define LEFT_ECHO 19   // Left ultrasonic sensor echo pin

double setpoint = 10;  // Desired distance from the wall (in cm)
double input, output;
double Kp = 2.0, Ki = 0.5, Kd = 1.0;  // PID tuning parameters

PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

long duration;
int distanceFront, distanceLeft;

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
  Serial.println("Robot stopped.");
}

// Function to move the robot forward
void forward() {
  digitalWrite(IN_11, LOW);
  digitalWrite(IN_12, HIGH);
  digitalWrite(IN_13, HIGH);
  digitalWrite(IN_14, LOW);
  digitalWrite(IN_24, LOW);
  digitalWrite(IN_23, HIGH);
  digitalWrite(IN_22, LOW);
  digitalWrite(IN_21, HIGH);
  analogWrite(EN_1, 60 + output);
  analogWrite(EN_2, 60 + output);
  analogWrite(EN_3, 60 - output);
  analogWrite(EN_4, 60 - output);
  Serial.print("Moving forward. PID output: ");
  Serial.println(output);
}

// Function to move the robot slightly right
void right() {
  digitalWrite(IN_11, LOW);
  digitalWrite(IN_12, HIGH);
  digitalWrite(IN_13, LOW);
  digitalWrite(IN_14, HIGH);
  digitalWrite(IN_24, HIGH);
  digitalWrite(IN_23, LOW);
  digitalWrite(IN_22, LOW);
  digitalWrite(IN_21, HIGH);
  analogWrite(EN_1, 60);
  analogWrite(EN_2, 60);
  analogWrite(EN_3, 60);
  analogWrite(EN_4, 60);
  Serial.println("Adjusting to the right.");
}

// Function to move the robot slightly left
void left() {
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
  Serial.println("Adjusting to the left.");
}

// Function to measure distance using an ultrasonic sensor
int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;  // Convert time to distance (cm)
}

void setup() {
  Serial.begin(9600);

  // Motor pin setup
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

  // Ultrasonic sensor pin setup
  pinMode(FRONT_TRIG, OUTPUT);
  pinMode(FRONT_ECHO, INPUT);
  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);

  // PID setup
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-60, 60);  // Adjust output to control speed variation
}

void loop() {
  distanceFront = getDistance(FRONT_TRIG, FRONT_ECHO);
  distanceLeft = getDistance(LEFT_TRIG, LEFT_ECHO);

  // Print distances
  Serial.print("Front distance: ");
  Serial.print(distanceFront);
  Serial.println(" cm");
  Serial.print("Left distance (Wall Detection): ");
  Serial.print(distanceLeft);
  Serial.println(" cm");

  input = distanceLeft;  // Input for PID is the distance from the wall
  myPID.Compute();       // Calculate the output (speed correction)

  // Wall following and obstacle avoidance logic
  if (distanceFront < 15) {  // If there's an obstacle within 15 cm in the front
    Serial.println("Obstacle detected! Stopping.");
    stopRobot();
  } else {
    if (distanceLeft < setpoint - 5) {  // Too close to the left wall
      Serial.println("Too close to the left wall, adjusting right.");
      right();  // Use right() function to steer away from the left wall
      // } else if (distanceLeft > setpoint + 5) {  // Too far from the left wall
      //   Serial.println("Too far from the left wall, adjusting left.");
      //   left();  // Use left() function to steer closer to the left wall
    } else {
      forward();  // Move forward if no obstacles and within desired distance from the left wall
    }
  }

  delay(200);  // Adjust delay as needed
}
