// A program for a robot powered with two motors with ultrasonic sensor to avoid obstacle and light sensors to follow a beam of light
#define L_PWM 3
#define L_DIR 12
#define R_PWM 11
#define R_DIR 13
#define PWM_MAX 255
#define R_LIGHT_SENSOR A0
#define L_LIGHT_SENSOR A1
#define trigPin 4
#define echoPin 2
#define DIFFERENCE_MIN -200
#define DIFFERENCE_MAX 200

void setup() {
//configuration of H-bridge
pinMode(L_DIR, OUTPUT);
pinMode(R_DIR, OUTPUT);
pinMode(L_PWM, OUTPUT);
pinMode(R_PWM, OUTPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
Serial.begin(9600);
}

void loop() {
int leftRead = analogRead(L_LIGHT_SENSOR);
int rightRead = analogRead(R_LIGHT_SENSOR);
int difference = leftRead - rightRead;

// uncomment this code to check the read values
/* Serial.print("Left side: ");
Serial.print(leftRead);
Serial.print(" | ");
Serial.print("Right side: "); //
Serial.println(rightRead);*/

long duration, distance; // ultrasonic sensor settings
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;

if (distance < 10) { // command to back up if the obstacle is in a distance smaller tham 10 centimeters
    digitalWrite(L_DIR, 1);
    analogWrite(L_PWM, 150);
    digitalWrite(R_DIR, 1);
    analogWrite(R_PWM, 150);
    delay(800);
    digitalWrite(L_DIR, 1);
    analogWrite(L_PWM, 100);
    digitalWrite(R_DIR, 0);
    analogWrite(R_PWM, 150);
    delay(800);
  }
else {

  }
if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
else {
    Serial.print(distance);
    Serial.println(" cm");
  }
if (difference < DIFFERENCE_MIN) { //If the difference is smaller than minimal
    difference = DIFFERENCE_MIN; //Then set the minimum
} else if (difference > DIFFERENCE_MAX) { //If the difference is bigger than maximal
    difference = DIFFERENCE_MAX; //then set the maximum
  }

//Transfering sensor inputs into motor velocity
int speedChange = map(difference, DIFFERENCE_MIN, DIFFERENCE_MAX, -90, 90);
//Adding or reducing the measured difference to the base velocity
leftMotor(100 + speedChange);
rightMotor(100 - speedChange);
}

void leftMotor(int V) {
if (V > 0) { //if velocity is more than 0
    V = map(V, 0, 250, 0, PWM_MAX);
    digitalWrite(L_DIR, 0); // direction: forward
    analogWrite(L_PWM, V); // velocity setting
} else {
    V = abs(V); //function abs() give us V always (+)
    V = map(V, 0, 250, 0, PWM_MAX);
    digitalWrite(L_DIR, 1); // direction: backward
    analogWrite(L_PWM, V); // velocity setting
  }
}

void rightMotor(int V) {
if (V > 0) { //if velocity is more than 0
    V = map(V, 0, 255, 0, PWM_MAX);
    digitalWrite(R_DIR, 0); // direction: forward
    analogWrite(R_PWM, V); // velocity setting
} else {
    V = abs(V); //function abs() give us V always (+)
    V = map(V, 0, 255, 0, PWM_MAX);
    digitalWrite(R_DIR, 1); // direction: backward
    analogWrite(R_PWM, V); // velocity setting
  }
}

void stopMotors() {
analogWrite(L_PWM, 0); //Turning off the left motor
analogWrite(R_PWM, 0); //Turning off the right motor
}
