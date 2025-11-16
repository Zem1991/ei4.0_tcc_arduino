// Include the Wi-Fi and Http libraries
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
// Required for some Wi-Fi modules/shields
#include <SPI.h>

// SSID of your network
char ssid[] = "SSID"; 
// Password of your WPA network (or empty for open networks)
char pass[] = "Password"; 

// Wi-Fi status variable
int status = WL_IDLE_STATUS;

// Pin for reading temperature input
const int sensorPin = A0;
// Server url where we publish each readout
const char* serverUrl = "http://localhost:5184/Temperature";

void setup() {
  Serial.begin(9600);
  connectToWiFi();
}

void loop() {
  float temperature = readTemperature();
  sendReading(temperature);
  delay(5000); // Send every 5 seconds
}

void connectToWiFi() {
  // Check for the presence of the Wi-Fi module/shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
  }
  else{
    // Attempt to connect to the Wi-Fi network
    while (status != WL_CONNECTED) {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      status = WiFi.begin(ssid, pass); // Connect using SSID and password
      delay(10000); // Wait 10 seconds for connection
    }
    // If connected successfully
    Serial.println("Connected to Wi-Fi!");
    printWiFiStatus(); // Print network details
  }
}

void printWiFiStatus() {
  // Print the SSID of the network you're connected to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // Print the IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  // Print the signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

float readTemperature() {
  int sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * (3.3 / 1023.0); // ESP8266 uses 3.3V
  float temperature = voltage * 100.0;
  Serial.print("Sensor readout: ");
  Serial.print(sensorValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.print(" mV | Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  return temperature;
}

void sendReading(float temperature) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverUrl);
    http.addHeader("Content-Type", "application/json");
    String payload = "{\"value\":" + String(temperature) + "}";
    int httpResponseCode = http.POST(payload);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    http.end();
  }
}