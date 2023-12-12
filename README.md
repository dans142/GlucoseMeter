# GlucoseMeter
A modification of a developed Glucose meter code made in Arduio IDE. 
The original code was made by Tanita Grace and all credits are reserved to her.

--------------------------------------------------------------------------------------------------------------------------------------------

**About the Original code,**
- The code uses the **window average** method to find the average voltage measured by the analog input of the ESP32. 
- The data taking is done once and instantly, every time the ESP32 is powered.
- The system implements Amazon Web Services in order to keep data in a dedicated database. (Commented in the Arduino Code)

**About the Modified Code,**
- The code implements a **running average** method that constantly takes measurement from the analog pin of the ESP32.
- Data taking is done continously.
- The modified code also implements an MQTT function, which is replaced as of now with a locally hosted server by the ESP32 using SPIFFS.
