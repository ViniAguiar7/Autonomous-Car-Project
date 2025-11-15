// --- Ultrasonic Sensor Pins ---
const int trigFront = 2;
const int echoFront = 3;
const int trigLeft = 4;
const int echoLeft = 5;
const int trigRight = 6;
const int echoRight = 7;
const int trigBack = 12;
const int echoBack = 13;

// --- Motor Pins ---
const int motorL1 = 8;
const int motorL2 = 9;
const int motorR1 = 10;
const int motorR2 = 11;
const int speedL = 5;
const int speedR = 6;

// --- Button ---
const int modeButton = A0;
bool parkingMode = false;

// --- Variables ---
long distFront, distRight, distLeft, distBack;
bool isParked = false;

void setup() {
  Serial.begin(9600);

  // Sensor configuration
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);
  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);
  pinMode(trigBack, OUTPUT);
  pinMode(echoBack, INPUT);

  // Motor configuration
  pinMode(motorL1, OUTPUT);
  pinMode(motorL2, OUTPUT);
  pinMode(motorR1, OUTPUT);
  pinMode(motorR2, OUTPUT);
  pinMode(speedL, OUTPUT);
  pinMode(speedR, OUTPUT);

  // Button configuration, uses pull-up resistor
  pinMode(modeButton, INPUT_PULLUP);

  Serial.println("Autonomous Car Initialized!");
}

// Returns distance read by an ultrasonic sensor
long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 20000);
  long distance = duration * 0.034 / 2;

  if (distance == 0 || distance > 200) distance = 200;
  return distance;
}

void loop() {
  // --- Check button press ---
  if (digitalRead(modeButton) == LOW) {
    parkingMode = !parkingMode;
    isParked = false;
    stopMotors();
    Serial.println(parkingMode ? "PARKING MODE activated" : "AUTONOMOUS MODE activated");
    delay(600);
  }

  // --- Parking mode ---
  if (parkingMode) {
    if (!isParked) {
      Serial.println("Starting parking sequence...");
      autoPark();
      isParked = true;
      stopMotors();
    }
    return;
  }

  // --- Autonomous mode ---
  distFront = measureDistance(trigFront, echoFront);
  distRight = measureDistance(trigRight, echoRight);
  distLeft = measureDistance(trigLeft, echoLeft);
  distBack = measureDistance(trigBack, echoBack);

  Serial.print("F: "); Serial.print(distFront);
  Serial.print(" | R: "); Serial.print(distRight);
  Serial.print(" | L: "); Serial.print(distLeft);
  Serial.print(" | B: "); Serial.println(distBack);

  if (distFront > 15) {
    moveForward(200);
  } else {
    stopMotors();
    delay(200);
    if (distRight > distLeft) turnRight(400);
    else turnLeft(400);
  }

  delay(100);
}

// --- Automatic parking routine ---
void autoPark() {
  Serial.println("Parking...");
  turnRight(500);

  while (measureDistance(trigBack, echoBack) > 15) {
    reverse(180);
  }

  stopMotors();
  turnLeft(400);
  moveForward(200);
  delay(600);
  stopMotors();

  Serial.println("Parking completed!");
}

// --- Movement functions ---
void moveForward(int speed) {
  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
  analogWrite(speedL, speed);
  analogWrite(speedR, speed);
}

void reverse(int speed) {
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, HIGH);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, HIGH);
  analogWrite(speedL, speed);
  analogWrite(speedR, speed);
}

void turnRight(int time) {
  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, HIGH);
  analogWrite(speedL, 200);
  analogWrite(speedR, 200);
  delay(time);
  stopMotors();
}

void turnLeft(int time) {
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, HIGH);
  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
  analogWrite(speedL, 200);
  analogWrite(speedR, 200);
  delay(time);
  stopMotors();
}

void stopMotors() {
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, LOW);
  analogWrite(speedL, 0);
  analogWrite(speedR, 0);
}
