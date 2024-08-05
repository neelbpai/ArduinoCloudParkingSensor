#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the pins for the ultrasonic sensor
const int trigPin = 7;
const int echoPin = 6;

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int greenLedPin = 10;
const int redLedPin = 11;

// Variables to store the distance
long duration;
int distance;

// Variable to store the previous state
bool carParkedPrevState = false;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  // Initialize serial communication
  Serial.begin(9600);

  // Set trigPin as an OUTPUT
  pinMode(trigPin, OUTPUT);
  // Set echoPin as an INPUT
  pinMode(echoPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10 microsecond pulse to the trigPin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the duration of the pulse on echoPin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm
  distance = duration * 0.034 / 2;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Determine current state
  bool carParkedCurrentState = (distance < 7);

  // Update LCD only if the state has changed
  if (carParkedCurrentState != carParkedPrevState) {
    if (carParkedCurrentState) {
      Serial.println("Car is Parked");
      lcd.clear(); // Clear the LCD
      lcd.setCursor(0, 0);
      lcd.print("Car is Parked");
      digitalWrite(redLedPin, HIGH);
      digitalWrite(greenLedPin, LOW);
    } else {
      Serial.println("No car is Parked");
      lcd.clear(); // Clear the LCD
      lcd.setCursor(0, 0);
      lcd.print("No car is Parked");
      digitalWrite(redLedPin, LOW);
      digitalWrite(greenLedPin, HIGH);
    }

    // Update the previous state
    carParkedPrevState = carParkedCurrentState;
  }

  // Delay before the next reading
  delay(750);
}
