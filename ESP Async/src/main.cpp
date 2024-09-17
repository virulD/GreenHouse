#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// DHT11 settings
#define DHTPIN 4       // Pin where the DHT11 is connected
#define DHTTYPE DHT11  // DHT 11
DHT dht(DHTPIN, DHTTYPE);

// Create an AsyncWebServer object on port 80
AsyncWebServer server(80);

// Variables to store temperature and humidity values
float temperature;
float humidity;

// Function to get sensor readings
void readDHT() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // Check if any reads failed and exit early
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
}

void setup() {
  // Start Serial communication
  Serial.begin(115200);

  // Initialize the DHT11 sensor
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Serve JSON data at "/data"
  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request) {
    String json = "{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}";
    request->send(200, "application/json", json);
  });

  // Start the server
  server.begin();
}

void loop() {
  // Update sensor readings every 2 seconds
  readDHT();
  delay(2000);
}
