#include <WiFi.h>
#include <WebServer.h>

// Your WiFi Credentials
const char* ssid = "3am";
const char* password = "qaz12345678";

// The LED Pin from your breadboard
const int ledPin = 23;

// Create a web server on port 80 (standard HTTP port)
WebServer server(80);

// HTML web page code with simple styling for the buttons
void handleRoot() {
 String html = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
 html += "<style>body{text-align:center; font-family:Arial, sans-serif; margin-top:50px; background-color:#f4f4f9;}";
 html += ".btn{display:inline-block; padding:20px 40px; font-size:24px; color:white; text-decoration:none; margin:15px; border-radius:8px; font-weight:bold;}";
 html += ".on{background-color:#4CAF50;} .off{background-color:#f44336;}</style></head><body>";
 html += "<h1>ESP32 Control Center</h1>";
 html += "<p><a href='/on' class='btn on'>TURN LED ON</a></p>";
 html += "<p><a href='/off' class='btn off'>TURN LED OFF</a></p>";
 html += "</body></html>";
  server.send(200, "text/html", html);
}

// Action when you click "TURN LED ON"
void handleLEDOn() {
 digitalWrite(ledPin, HIGH);
 server.sendHeader("Location", "/"); // Redirects back to the main page instantly
 server.send(303);
}

// Action when you click "TURN LED OFF"
void handleLEDOff() {
 digitalWrite(ledPin, LOW);
 server.sendHeader("Location", "/"); // Redirects back to the main page instantly
 server.send(303);
}

void setup() {
 // Start the serial communication to find our IP address
 Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
 digitalWrite(ledPin, LOW); // Start with LED turned off

 // Connect to your WiFi
 WiFi.begin(ssid, password);
 Serial.print("Connecting to WiFi");
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }
  // Print connection details
 Serial.println("");
 Serial.println("WiFi Connected successfully!");
 Serial.print("Your ESP32 IP Address is: ");
 Serial.println(WiFi.localIP()); // <-- THIS IS WHAT YOU TYPE IN YOUR BROWSER

 // Define what happens when visiting the links
 server.on("/", handleRoot);
 server.on("/on", handleLEDOn);
 server.on("/off", handleLEDOff);

 // Start the server
 server.begin();
}

void loop() {
 server.handleClient(); // Keep listening for browser clicks
}
