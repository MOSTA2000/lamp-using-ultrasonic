// Define pins
const int trigPin = 9;
const int echoPin = 10;
const int redLedPin = 7;
const int greenLedPin = 6;
const int relayPin = 8; // Define the pin connected to the relay

// Define constants
const int maxDistance = 100; // Maximum distance in centimeters
const int minDistance = 5;   // Minimum distance in centimeters

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(relayPin, OUTPUT); // Set relay pin as output
}

void loop() {
  int distance = measureDistance(trigPin, echoPin, redLedPin, greenLedPin, minDistance, maxDistance);
  // You can do something with the measured distance here if needed
}

int measureDistance(int trigPin, int echoPin, int redLedPin, int greenLedPin, int minDistance, int maxDistance) {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  
  // Short delay before reading the echo pulse
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);
  
  // Read the echo pulse
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance in centimeters
  int distance = duration * 0.034 / 2;
  
  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Check distance and control LEDs
  if (distance >= minDistance && distance <= maxDistance) {
    // Within range
    digitalWrite(redLedPin, LOW);    // Turn off red LED
    delay(100); // Delay between turning off red and turning on green
    digitalWrite(greenLedPin, HIGH); // Turn on green LED
    
    // Turn on relay
    digitalWrite(relayPin, HIGH);
  } else {
    // Out of range
    digitalWrite(redLedPin, HIGH);   // Turn on red LED
    digitalWrite(greenLedPin, LOW);  // Turn off green LED
    
    // Turn off relay
    digitalWrite(relayPin, LOW);
  }
  
  // Short delay for stability
  delay(100);
  
  return distance;
}