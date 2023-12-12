// Glucometer ESP32 Code
// by: Tanita Grace
// 2023

const int pin = 33;// Analog pin
int pinValue;// do not change
float voltage =0;// do not change
float voltageInput[] = {};
int sampleCounter = 0 ;
float avrgVoltage = 0.0;
#define window_size 10
float window[window_size] = {0};
float glucose=0;
int i;

//#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
//#include <ArduinoJson.h>
#include "WiFi.h"
#define AWS_IOT_PUBLISH_TOPIC "publishme" //IoT Topic

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

//void connectAWS()
//{
//WiFi.mode(WIFI_STA);
//WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//Serial.println("Connecting to Wi-Fi");
//
//while (WiFi.status() != WL_CONNECTED)
//{
//delay(500);
//Serial.print(".");
//}

// Configure WiFiClientSecure to use the AWS IoT device credentials
//net.setCACert(AWS_CERT_CA);
//net.setCertificate(AWS_CERT_CRT);
//net.setPrivateKey(AWS_CERT_PRIVATE);

// Connect to the MQTT broker on the AWS endpoint we defined earlier
//client.setServer(AWS_IOT_ENDPOINT, 8883);
//Serial.println("Connecting to AWS IOT");
//
//while (!client.connect(THINGNAME))
//{
//Serial.print(".");
//delay(100);
//}
//
//if (!client.connected())
//{
//Serial.println("AWS IoT Timeout!");
//return;
//}
//
//Serial.println("AWS IoT Connected!");
//}

//void publishMessage()
//{
//StaticJsonDocument<200> doc;
//String myStr;
//myStr = String(glucose);
//doc["glucose"] = myStr;
//char jsonBuffer[512];
//if (glucose!=0){
//serializeJson(doc, jsonBuffer); // print to client
//client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
//}
//}


void push(float val){
int i = 0;
for (i=1; i<window_size; i++){
window[i-1] = window[i];
}
window[window_size-1] = val;
}

float take_avg(){
float sum =0;
int i = 0;
for(i=0; i<window_size; i++){
sum += window[i];
}
return sum/window_size;
}

void setup() {
// initialize serial communication at 115200 bits per second:
Serial.begin(115200);
//connectAWS();
}

void loop() {
// read the input on analog pin potPin:
pinValue = analogRead(pin);
voltage = (3.3/4095.0) * pinValue;
push(voltage);

if(voltage > 2.45){
sampleCounter++;
if (sampleCounter<32){
voltageInput[sampleCounter] = take_avg(); //every float sample occupied 4 memory locations
Serial.println(voltageInput[sampleCounter]);
delay(200);

//Serial.println(sampleCounter);
//sampleCounter++;
if (sampleCounter == 31) //20 samples are collected
{
for (i = 20; i<sampleCounter; i++)
{
avrgVoltage += voltageInput[i]; //all 20 samples are added
}
avrgVoltage = avrgVoltage / 11;
glucose = (avrgVoltage - 2.405073)/(0.0010523);
//publishMessage();
client.loop();
Serial.print("Average=");
Serial.println(avrgVoltage,7);
Serial.print("glucose=");
Serial.println(glucose);
Serial.println("================================================");
}
}
}
}
