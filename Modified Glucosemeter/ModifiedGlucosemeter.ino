// IKUTIN INI IMPORTANT
// https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/

#ifdef ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>
#else
  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <FS.h>
#endif

#include <PubSubClient.h>
#include <Wire.h>
#include "RunningAverage.h"

RunningAverage Voltage(3);
WiFiClient espClient;
PubSubClient client(espClient);



const int pin = 33;                     // Analo    g pin
int pinValue;                     // do not chang
float volt = 0.0;                 // do not change
float glucose = 0;
int samples = 0;
float avg1 = 0;
float avg2 = 0.0;
float avgdiff = 0.0;

const int strip = 16;             // Strip Input Pin
int stripState = 0;

//Wifi Credentials
//Used to test WIFI Connection
const char* ssid = "SGU-LAB";
const char* password = "SGUnumber1";

AsyncWebServer server(80);

// MQTT Broker Connection, Uncomment to implement 
//const char* mqtt_server = "91.121.93.94";     // test.mosquitto.org

void setup_wifi() 
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

String GlucoseLevel()
{
  volt = (3.3 / 4095.0) * analogRead(pin);
  Voltage.addValue(volt);
  
  if (samples % 3 == 0)
  {
    Serial.println("\nCNT\tV\tavg1\tavg2\tavgdiff");
  }
  samples++;

  avg1 = Voltage.getAverage();

  Serial.print(samples);
  Serial.print('\t');
  Serial.print(volt, 1);
  Serial.print('\t');
  Serial.print(avg1, 2);
  Serial.print('\t');
  Serial.print(avg2, 2);

  avgdiff = avg1 - avg2;
  Serial.print('\t');
  Serial.print(avgdiff, 2);
  avg2 = avg1;

  Serial.println();

  if (avgdiff < 0.1 && avgdiff > -0.1 && volt > 2.45)
      {
        glucose = (avg1 - 2.405073)/(0.0010523);  // Calibrate Here!!!
        Serial.println("================================================");
        Serial.print("Average = ");
        Serial.println(avg1);
        Serial.print("Glucose = ");
        Serial.println(glucose);
        Serial.println("================================================");
        delay(1000);
        Serial.println("Data Taken");
        Serial.println("---------------");
      }
  return String (glucose);
}

void setup() 
{
  Serial.begin(115200);
  //pinMode(strip, INPUT);
  Voltage.clear();

  bool status; 
  if(!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  setup_wifi();             // Connect to Wifi

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/GlucoseLevel", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", GlucoseLevel().c_str());
  });
    // Start server
  server.begin();
}


void loop() 
{
  GlucoseLevel();
}
