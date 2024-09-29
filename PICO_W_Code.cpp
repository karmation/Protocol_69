#include <WiFi.h>
#include <Wire.h>

// Network credentials
const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

// LED Pin
const int ledStatus = 13; // LED to indicate status (process ongoing)

void setup() {
    Serial.begin(115200);
    pinMode(ledStatus, OUTPUT);
    digitalWrite(ledStatus, LOW); // Initially, LED is off

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to Wi-Fi...");
    }
    Serial.println("Connected to Wi-Fi");

    // Start I2C
    Wire.begin(12, 13); // SDA, SCL
}

void loop() {
    Wire.requestFrom(0x12, 1); // Request command from ESP32
    if (Wire.available()) {
        char command = Wire.read();
        handleCommand(command);
    }
}

void handleCommand(char command) {
    if (command == 'd') {
        Serial.println("Executing Wi-Fi Deauthentication...");
        digitalWrite(ledStatus, HIGH); // LED on
        // Add your deauth code here
        delay(5000); // Simulating attack duration
        digitalWrite(ledStatus, LOW); // LED off
        Serial.println("Deauth completed.");
    }
    else if (command == 's') {
        Serial.println("Executing Wi-Fi Sniffing...");
        digitalWrite(ledStatus, HIGH); // LED on
        // Add your sniffing code here
        delay(5000); // Simulating attack duration
        digitalWrite(ledStatus, LOW); // LED off
        Serial.println("Sniffing completed.");
    }
    // Add more command handling as needed
}
