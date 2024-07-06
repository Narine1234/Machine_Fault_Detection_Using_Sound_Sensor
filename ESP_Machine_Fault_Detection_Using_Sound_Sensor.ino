#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Your Wifi";
const char* password = "Your Password";
const char* serverName = "http://<your_server_ip>:5000/update"; 
const int sensorPin = A0; 
int sensorValue = 0;

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT); 

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  sensorValue = analogRead(sensorPin); 

  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    String serverPath = String(serverName) + "?sensor=" + String(sensorValue);

    http.begin(client, serverPath.c_str()); 
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
  delay(1000); 
}
