#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

SoftwareSerial arduinoSerial(D4, D5); // RX, TX pins for communication with Arduino

const char *ssid = "Hii";        // Replace with your WiFi SSID
const char *password = "aaaaaaaa"; // Replace with your WiFi password

ESP8266WebServer server(80);

void setup() {
  Serial.begin(9600);
  arduinoSerial.begin(115200); 
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print the ESP8266's IP address
  Serial.println(WiFi.localIP());
  
  // Define web pages
  server.on("/", HTTP_GET, handleRoot);
  server.on("/forward", HTTP_GET, forward);
  server.on("/backward", HTTP_GET, backward);
  server.on("/left", HTTP_GET, left);
  server.on("/right", HTTP_GET, right);
  
  // Add new endpoints for speed levels
  server.on("/speed1", HTTP_GET, speed1);
  server.on("/speed2", HTTP_GET, speed2);
  server.on("/speed3", HTTP_GET, speed3);
  server.on("/speed4", HTTP_GET, speed4);

  // Start the server
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String webpage = "<html><head><title>RC Car Control</title>";
webpage += "<style>";
webpage += "body {";
webpage += "  background-color: white;"; // Set background color to white
webpage += "  text-align: center;";
webpage += "  user-select: none;";
webpage += "  touch-action: manipulation;";
webpage += "  -ms-touch-action: manipulation;";
webpage += "  touch-zooming: none;";
webpage += "  -ms-touch-zooming: none;";
webpage += "}";
webpage += "button { background-color: #f44336; color: #fff; border: none; padding: 20px 40px;";
webpage += "font-size: 24px; margin: 10px; cursor: pointer; border-radius: 25px; }"; // Set background color and rounded edges
webpage += "button:hover { background-color: #d32f2f; }"; // Hover color
webpage += "</style></head><body>";
webpage += "<h1 style='color: #222;'>RC Car Control</h1>";

// Buttons for horizontal orientation
webpage += "<div style='display: flex; flex-direction: row; justify-content: center;'>"; // Flexbox layout
webpage += "<div style='flex: 1;'><button onclick=\"sendCommand('forward')\">Forward</button></div>";
webpage += "<div style='flex: 1;'><button onclick=\"sendCommand('left')\">Left</button></div>";
webpage += "<div style='flex: 1;'><button onclick=\"sendCommand('right')\">Right</button></div>";
webpage += "<div style='flex: 1;'><button onclick=\"sendCommand('backward')\">Backward</button></div>";
webpage += "</div>"; // End of flexbox layout

// Buttons for speed levels
webpage += "<div style='display: flex; flex-direction: row; justify-content: center;'>";
webpage += "<div style='flex: 1;'><button onclick=\"sendSpeed(1)\">Speed 1</button></div>";
webpage += "<div style='flex: 1;'><button onclick=\"sendSpeed(2)\">Speed 2</button></div>";
webpage += "<div style='flex: 1;'><button onclick=\"sendSpeed(3)\">Speed 3</button></div>";
webpage += "<div style='flex: 1;'><button onclick=\"sendSpeed(4)\">Speed 4</button></div>";
webpage += "</div>"; // End of flexbox layout

webpage += "<script>";
webpage += "function sendCommand(command) {";
webpage += "var xhr = new XMLHttpRequest();";
webpage += "xhr.open('GET', '/' + command, true);";
webpage += "xhr.send();";
webpage += "}";

webpage += "function sendSpeed(speed) {";
webpage += "var xhr = new XMLHttpRequest();";
webpage += "xhr.open('GET', '/speed' + speed, true);";
webpage += "xhr.send();";
webpage += "}";
webpage += "</script>";
webpage += "</body></html>";

server.send(200, "text/html", webpage);

}

void forward() {
  Serial.println("F"); // Send 'F' for forward
  arduinoSerial.write("F");
  server.send(200, "text/plain", "Forward");
}

void backward() {
  Serial.println("B"); // Send 'B' for backward
  arduinoSerial.write("B");
  server.send(200, "text/plain", "Backward");
}

void left() {
  Serial.println("L"); // Send 'L' for left
  arduinoSerial.write("L");
  server.send(200, "text/plain", "Left");
}

void right() {
  Serial.println("R"); // Send 'R' for right
  arduinoSerial.write("R");
  server.send(200, "text/plain", "Right");
}

void speed1() {
  Serial.println("1");
  arduinoSerial.write("1");
  server.send(200, "text/plain", "Speed Level 1");
}

void speed2() {
  Serial.println("2");
  arduinoSerial.write("2");
  server.send(200, "text/plain", "Speed Level 2");
}

void speed3() {
  Serial.println("3");
  arduinoSerial.write("3");
  server.send(200, "text/plain", "Speed Level 3");
}

void speed4() {
  Serial.println("4");
  arduinoSerial.write("4");
  server.send(200, "text/plain", "Speed Level 4");
}