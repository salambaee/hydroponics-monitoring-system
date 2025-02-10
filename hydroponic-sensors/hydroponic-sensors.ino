/* ESP8266WiFI.h used to connect the ESP8266 module to WiFi network */
#include <ESP8266WiFi.h>

/* Enables HTTPS connections */
#include <WiFiClientSecure.h>

/* Provides HTTP communication capabilities */
#include <ESP8266HTTPClient.h>

/* Facilities creating and parsing JSON objects */
#include <ArduinoJson.h>

//#include <DHT.h>

//#define DHTPIN D2
//#define DHTTYPE DHT11

/* WIFI_SSID and WIFI_PASSWORD store the SSID and password for the WiFi network to connect */
#define WIFI_SSID "SALAMRIZQIYANGMULIA"
#define WIFI_PASSWORD "maswifine"
/* FIREBASE_HOST and FIREBASE_PATH specify the Firebase database URL and path to store the sensor data */
const String FIREBASE_HOST = "https://data-sensor-cbfc4-default-rtdb.firebaseio.com";
const String FIREBASE_PATH = "/sensor.json";

//DHT dht(DHTPIN, DHTTYPE);

/* Creates a secure WiFi client for HTTPS communication */
WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  //dht.begin();

  /* Starts the connection to the specified WiFi network */
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");

  /* A while loop continuously checks the connection status. Dots are printed to the serial monitor until the ESP8266 is connected
  to the WiFi. One connected, the local IP Address is displayed.*/
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi Connected !");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  client.setInsecure();
}

void loop() {
  /* The actual sensor reading code is commented out
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Instead, random values are used for demonstration.*/
  int t = random(0,35);
  int h = random(0,35);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = FIREBASE_HOST + FIREBASE_PATH;
    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["suhu"] = t;
    jsonDoc["kelembapan"] = h;

    String jsonString;
    serializeJson(jsonDoc, jsonString);

    int httpResponseCode = http.PUT(jsonString);

    if (httpResponseCode > 0) {
      Serial.print("Respons from HTTP : ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error : ");
      Serial.println(http.errorToString(httpResponseCode).c_str());
    }

    http.end();
  } else {
    Serial.println("WiFi not connected !");
  }

  delay(10000);
}
