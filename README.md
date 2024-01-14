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

Schematic Diagram can be seen as follows
![image](https://github.com/dans142/GlucoseMeter/assets/59532748/76595511-be8f-4185-98a6-0ea17107390b)

List of essential components:
- ESP32
- LM317TO
- Socket Strip (from GlucoDr)
- LMC6484
- 10 nF Capacitors
- 100 nF Capacitors
- 150 ohm Resistors
- 220 ohm Resistors
- 10k ohm Resistors 

Additional Components
- TTGO ESP32
- SD Card Module
- Buttons
- NE555D

Pictures and Video Result of IoT Integration (In Indonesian)
![WhatsApp Image 2023-12-22 at 12 53 15_be59b58d](https://github.com/dans142/GlucoseMeter/assets/59532748/4483efc4-bdba-4524-8837-5cc99566e474)


https://github.com/dans142/GlucoseMeter/assets/59532748/20eb7f1f-ff05-40e6-b608-1e6e0e956aff



