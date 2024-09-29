#include <Wire.h>

// LED Pins
const int ledRed = 8;   // Attack in-progress
const int ledGreen = 9; // Attack successful

void setup() {
    Serial.begin(115200);
    pinMode(ledRed, OUTPUT);
    pinMode(ledGreen, OUTPUT);
    digitalWrite(ledRed, LOW);  // Initially, LED is off
    digitalWrite(ledGreen, LOW); // Initially, LED is off

    // Start I2C
    Wire.begin(8); // I2C address for Nano
}

void loop() {
    Wire.onRequest(requestEvent); // Handle requests from ESP32
    delay(100); // Adjust delay as necessary
}

void requestEvent() {
    // Handle incoming commands from ESP32
    Wire.requestFrom(0x13, 1); // Request command from ESP32
    if (Wire.available()) {
        char command = Wire.read();
        handleCommand(command);
    }
}

void handleCommand(char command) {
    if (command == 'r') {
        Serial.println("Executing RFID Cloning...");
        digitalWrite(ledRed, HIGH); // LED on
        // Add your RFID cloning code here
        delay(5000); // Simulating attack duration
        digitalWrite(ledRed, LOW); // LED off
        digitalWrite(ledGreen, HIGH); // LED on
        delay(2000);
        digitalWrite(ledGreen, LOW); // LED off
        Serial.println("RFID Cloning completed.");
    }
    // Add more command handling as needed
}
