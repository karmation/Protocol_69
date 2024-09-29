#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPI.h>
#include <RF24.h>
#include <Wire.h>

// NRF24L01 Pin definitions
#define CE_PIN  26
#define CSN_PIN 27
RF24 radio(CE_PIN, CSN_PIN);

// Network credentials
const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

// Web server on port 80
AsyncWebServer server(80);

// LED Pins
const int ledRed = 14; // Attack in-progress
const int ledGreen = 12; // Attack successful
const int ledBlue = 13; // Idle/Ready

// NRF24L01 addresses
byte address[][6] = {"1Node", "2Node"};

// HTML content for the control panel
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP32 Control Panel</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { text-align: center; background-color: #f4f4f4; color: #333; font-family: Arial; }
    h1 { margin-top: 20px; }
    .button { padding: 15px 30px; margin: 10px; font-size: 18px; background-color: #007BFF; color: white; border: none; border-radius: 5px; cursor: pointer; }
    .button:hover { background-color: #0056b3; }
    .log { margin-top: 20px; padding: 10px; border: 1px solid #ccc; background-color: #fff; height: 300px; overflow-y: auto; text-align: left; white-space: pre-wrap; }
  </style>
</head>
<body>
  <h1>ESP32 Attack Control Panel</h1>
  <div>
    <button class="button" onclick="sendCommand('deauth')">Wi-Fi Deauth</button>
    <button class="button" onclick="sendCommand('sniff')">Wi-Fi Sniffing</button>
    <button class="button" onclick="sendCommand('bluetooth')">Bluetooth Attack</button>
    <button class="button" onclick="sendCommand('rfid')">RFID Cloning</button>
    <button class="button" onclick="sendCommand('ir')">IR Replay</button>
    <button class="button" onclick="clearLogs()">Clear Logs</button>
  </div>
  <div class="log" id="logArea">Logs will appear here...</div>

  <script>
    function sendCommand(command) {
      fetch('/command?cmd=' + command)
        .then(response => response.text())
        .then(data => {
          document.getElementById('logArea').innerText += 'Command Executed: ' + command + '\\n' + data + '\\n';
        })
        .catch(error => {
          document.getElementById('logArea').innerText += 'Error: ' + error + '\\n';
        });
    }

    function clearLogs() {
      document.getElementById('logArea').innerText = 'Logs will appear here...';
    }
  </script>
</body>
</html>
)rawliteral";

// Handle incoming commands from web interface
String processCommand(String command) {
  String response = "Received command: " + command + "\n";

  if (command == "deauth") {
    response += "Starting Wi-Fi Deauth...\n";
    // Trigger Pico W via I2C or NRF for Deauth
    startAttack(ledRed, ledGreen, "deauth");
  } else if (command == "sniff") {
    response += "Starting Wi-Fi Sniffing...\n";
    startAttack(ledRed, ledGreen, "sniff");
  } else if (command == "bluetooth") {
    response += "Starting Bluetooth Attack...\n";
    startAttack(ledRed, ledGreen, "bluetooth");
  } else if (command == "rfid") {
    response += "Starting RFID Cloning...\n";
    startAttack(ledRed, ledGreen, "rfid");
  } else if (command == "ir") {
    response += "Starting IR Replay...\n";
    startAttack(ledRed, ledGreen, "ir");
  } else {
    response += "Unknown command.\n";
  }

  return response;
}

void startAttack(int ledRed, int ledGreen, String attackType) {
  digitalWrite(ledRed, HIGH);  // Attack in progress
  delay(5000);  // Simulate attack time

  // Send attack command to Pico W or Nano
  if (attackType == "deauth" || attackType == "sniff") {
    Wire.beginTransmission(0x12);  // Send command to Pico W
    Wire.write(attackType.c_str());
    Wire.endTransmission();
  } else if (attackType == "rfid" || attackType == "ir") {
    Wire.beginTransmission(0x13);  // Send command to Nano
    Wire.write(attackType.c_str());
    Wire.endTransmission();
  }

  digitalWrite(ledRed, LOW);   // Turn off in-progress LED
  digitalWrite(ledGreen, HIGH);  // Attack successful
  delay(2000);
  digitalWrite(ledGreen, LOW);   // Reset
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");

  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);

  digitalWrite(ledBlue, HIGH);  // Ready status

  // Set up NRF24L01+ communication
  radio.begin();
  radio.openWritingPipe(address[1]);
  radio.openReadingPipe(1, address[0]);
  radio.startListening();

  // Set up I2C communication with Pico W and Nano
  Wire.begin(21, 22);  // I2C pins (SDA, SCL)

  // Start web server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/command", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("cmd")) {
      String command = request->getParam("cmd")->value();
      String response = processCommand(command);
      request->send(200, "text/plain", response);
    } else {
      request->send(400, "text/plain", "Bad Request");
    }
  });

  server.begin();
}

void loop() {
  // No code required here, the server handles everything
}
