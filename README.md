# Protocol_69
Wi-Fi and RFID Attack Management System
Overview
This project integrates multiple microcontrollers (ESP32, Pico W, and Arduino Nano) to create a versatile platform for performing various Wi-Fi and RFID attacks. The system features a web interface for easy control and monitoring, LED indicators for process status, and supports communication between the devices via I2C.

Features
Wi-Fi Attacks:

Wi-Fi Deauthentication: Disrupts the connection between a device and a Wi-Fi network, forcing it to disconnect. Useful for testing the robustness of network security.

Wi-Fi Sniffing: Captures and analyzes Wi-Fi packets being transmitted over a network. This helps in assessing the data being transferred and can reveal sensitive information.

WPA/WPA2 Cracking: Attempts to recover the pre-shared key (PSK) used for WPA/WPA2 encryption by exploiting weak passwords or using dictionary attacks.

Man-in-the-Middle (MitM) Attacks: Intercepts communication between two parties without their knowledge. This can allow an attacker to eavesdrop or alter the communication.

DNS Spoofing: Redirects users from legitimate websites to malicious ones by manipulating the DNS responses, often used to phish for sensitive information.

TCP/UDP Flooding (DoS): Overwhelms a target system with a flood of TCP or UDP packets, causing service disruption. Useful for testing the resilience of network infrastructure.

Wi-Fi Handshake Capture: Captures the handshake process during a device's connection to a Wi-Fi network. This data can later be used to crack the Wi-Fi password.

Wi-Fi Beacon Frame Flooding: Floods a network with beacon frames, causing confusion among devices and potentially disrupting network operations.

Bluetooth Scanning & Spoofing: Scans for Bluetooth devices and can impersonate them, allowing unauthorized access to paired devices.

Bluetooth Jamming: Sends interference signals to disrupt Bluetooth communications, causing devices to disconnect.

RFID Attacks:

RFID Sniffing: Captures RFID signals being transmitted, allowing an attacker to gather information from RFID-enabled devices.

RFID Cloning: Copies RFID signals from a legitimate card to create a duplicate, granting unauthorized access to restricted areas.

RFID Replay: Replays captured RFID signals to impersonate an authorized user and gain access.

RFID DoS (Flooding): Overwhelms an RFID system with repeated requests, causing it to become unresponsive.

USB HID Attack (Keyboard Emulation): Emulates a keyboard to send keystrokes to a computer, allowing unauthorized commands to be executed.

Hardware Required
Microcontrollers:

ESP32
Raspberry Pi Pico W
Arduino Nano
Other Components:

NRF24L01+PA+LNA Module
3 LEDs (for status indication)
Resistors (220Ω for LEDs)
Breadboard and jumper wires
Power source (USB power supply or battery)
Wiring Connections
1. ESP32 Connections
Pin	Connection
3.3V	Power the NRF24L01+ module
GND	Ground for NRF24L01+ module
GPIO 5 (CSN)	NRF24L01+ chip select (CSN)
GPIO 17 (CE)	NRF24L01+ chip enable (CE)
GPIO 21 (SDA)	I2C SDA (to Pico W and Nano)
GPIO 22 (SCL)	I2C SCL (to Pico W and Nano)
2. Pico W Connections
Pin	Connection
3.3V	Power from ESP32
GND	Ground from ESP32
GPIO 12 (SDA)	I2C SDA (to ESP32)
GPIO 13 (SCL)	I2C SCL (to ESP32)
GPIO 13 (LED)	Status LED
3. Arduino Nano Connections
Pin	Connection
5V	Power from USB or 5V source
GND	Ground
A4 (SDA)	I2C SDA (to ESP32)
A5 (SCL)	I2C SCL (to ESP32)
D8 (LED Red)	Attack status LED
D9 (LED Green)	Attack completion LED
4. NRF24L01 Connections
Pin	Connection
GND	Ground
VCC	3.3V
CE	GPIO 17 (ESP32)
CSN	GPIO 5 (ESP32)
SCK	GPIO 18 (ESP32)
MOSI	GPIO 23 (ESP32)
MISO	GPIO 19 (ESP32)
Software Required
Arduino IDE
Required libraries:
WiFi
Wire
ESPAsyncWebServer
SPI
nRF24L01 (for NRF module)
Setup Instructions
1. Prepare the Environment
Install the Arduino IDE if you haven’t already.
Install the necessary libraries through the Library Manager in Arduino IDE.
2. Code Configuration
Open each code file in the Arduino IDE.
Update the Wi-Fi credentials in each code:
cpp
Copy code
const char* ssid = "your-SSID"; // Change to your network SSID
const char* password = "your-PASSWORD"; // Change to your network password
Upload the code to each microcontroller:
Select the correct board from Tools > Board.
Choose the appropriate COM port and upload.
3. Power Up the System
Connect your boards to the power supply.
Start with powering the ESP32 first, followed by the Pico W and Arduino Nano.
4. Access the Web Interface
Use a web browser to navigate to the IP address assigned to the ESP32 (shown in the Serial Monitor).
Use the buttons to initiate attacks and view logs in real-time.
Usage Instructions
Web Interface: Access the ESP32’s web interface through your browser.
Executing Attacks: Click the appropriate buttons to start different attacks. LED indicators on the boards will reflect the status:
Red LED: Attack in progress
Green LED: Attack completed successfully
Contributing
Feel free to enhance the project by adding more attack functionalities or improving the web interface. Open an issue or submit a pull request on the GitHub repository.

Disclaimer
This project is for educational and ethical hacking purposes only. Do not use it against networks or devices without permission. Always follow ethical hacking guidelines and legal regulations.

License
This project is licensed under the MIT License. See the LICENSE file for more details.

