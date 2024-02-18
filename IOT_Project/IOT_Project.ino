#include <Servo.h>

Servo servo1;
Servo servo2;

const int S0 = 2;
const int S1 = 3;
const int S2 = 4;
const int S3 = 5;
const int out = 6;

// Các ngưỡng để xác định màu sắc
int redMinR = 40, redMaxR =120;
int redMinG = 200, redMaxG = 250;
int redMinB = 130, redMaxB = 200;

int greenMinR = 160, greenMaxR = 260;
int greenMinG = 100, greenMaxG = 160;
int greenMinB = 120, greenMaxB = 140;

int yellowMinR = 30, yellowMaxR = 60;
int yellowMinG = 110, yellowMaxG = 140;
int yellowMinB = 120, yellowMaxB = 140;

unsigned long previousTime = 0;
const long interval = 2000; // 2s

void setup() {
  servo1.attach(9);
  servo2.attach(10);

  Serial.begin(9600);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(out, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
}

void loop() {
  unsigned long currentTime = millis();

  int redR = getRedValue();
  int greenR = getGreenValue();
  int blueR = getBlueValue();

  Serial.print("Red: ");
  Serial.print(redR);
  Serial.print(" Green: ");
  Serial.print(greenR);
  Serial.print(" Blue: ");
  Serial.println(blueR);

  delay(100);

  if (isRed(redR, greenR, blueR)) {
    Serial.println("Red Detected");
    servo1.write(110);
    delay(3000);
    servo1.write(180);
    previousTime = currentTime;
  } else if (isYellow(redR, greenR, blueR)) {
    Serial.println("Yellow Detected");
    servo2.write(180);
    delay(3000);
    servo2.write(110);
    previousTime = currentTime;
  } else if (isGreen(redR, greenR, blueR)) {
    Serial.println("Green Detected");
    servo1.write(180);
    servo2.write(110);
    previousTime = currentTime;
  }
  

  if (currentTime - previousTime >= interval) {
    // Tiếp tục phát hiện màu sau 2 giây
    previousTime = currentTime; // Reset
  }
}

int getRedValue() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  return pulseIn(out, LOW);
}

int getGreenValue() {
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  return pulseIn(out, LOW);
}

int getBlueValue() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  return pulseIn(out, LOW);
}

bool isRed(int red, int green, int blue) {
  return (red >= redMinR && red <= redMaxR) &&
         (green >= redMinG && green <= redMaxG) &&
         (blue >= redMinB && blue <= redMaxB);
}

bool isGreen(int red, int green, int blue) {
  return (red >= greenMinR && red <= greenMaxR) &&
         (green >= greenMinG && green <= greenMaxG) &&
         (blue >= greenMinB && blue <= greenMaxB);
}

bool isYellow(int red, int green, int blue) {
  return (red >= yellowMinR && red <= yellowMaxR) &&
         (green >= yellowMinG && green <= yellowMaxG) &&
         (blue >= yellowMinB && blue <= yellowMaxB);
}