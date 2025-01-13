# Plant Monitoring System 🌱 
(There is not much evidence of LEDS pictures since the Chrono Lumina unit has not worked since the last reset. However, Mqtt Explorer can indicate that the LEDS should be on.)
<img src="/result/device2.jpg" alt="device" style="zoom:10%;" />
## A Spark of Inspiration
In the CASA0016 course, I developed an automated irrigation system designed to prevent prevent me from forgetting to water. I have to say that I really don't have a good memory, which leads to my potted plants at home often dying. The system automates irrigation by monitoring soil moisture and rainfall through sensors.
So far, it occurred to me that since I already have an automatic irrigation system to keep my houseplants alive, why not let them live a little better? So I had this idea of being able to see directly how well my plants are living.

## Project Objectives
The aim of this project is to develop an Arduino-based intelligent plant monitoring system to achieve real-time monitoring and visual feedback of plant growth environment. By integrating multiple sensors (LDR, temperature and humidity sensors), the system is able to collect the environmental parameters around the plants (including light intensity, air temperature and humidity) and transmit the data to the Chrono Lumina Light by using the MQTT protocol. the colour change of the light will reflect the plant's growing environment condition, which will help the user to better understand and improve the plant's growing conditions.

## Visual Feedback
Real-time light, temperature and humidity detection and colour feedback  
Light intensity, temperature and humidity are monitored in real time mapped to RGB colours:  
-Low : blue  
-Good : green  
-Excessive : red  
Configure a sliding resistor to adjust the brightness of the light and publish it to the server via MQTT.

## Repository Structure
```plaintext
- CASA0014_Smart_Garden/
            - Src/
                        - PlantMonitor.ino //final version of code
            - result/
                        - device.jpg       //appearance of device
                        - device2.jpg      //appearance of device
                        - interactive.png  //physical part and cloud part relation
                        - result.png       //LEDS status changed from mqtt explorer
                        - result2.png       //LEDS status changed from mqtt explorer
                        - result3.png       //LEDS status changed from mqtt explorer
            - test/
                        - ldr_ASAIR_test.ino     //test code
                        - ldr_dht_ver2.ino       //test code
                        - ldr_mqtt_test.ino      //test code
                        - ldr_rhe_test.ino       //test code
            - README.md
```


### test folder
code for testing  
 **`ldr_rhe_test`**: test if ldr and slide rheostat works and check the value returned from them  
 **`ldr_mqtt_test`**: LDR to detect light intensity and slide rheostat control brightness as well as publish RGB settings and brightness setting to mqtt   
 **`ldr_ASAIR_test`**: LDR, ASAIR Sensor to detect light intensity, temperature and humidity, publish RGB settings to mqtt(false one, code is wrong, library is wrong)  
 **`ldr_dht_ver2`**: LDR, ASAIR Sensor to detect light intensity, temperature and humidity, publish RGB settings to mqtt(Final version for now)
 
## Requirements
### Hardware
- ASAIR AM2122 Temperature and Humidity Sensor
- Arduino MKR WiFi 1010
- light-dependent resistor(LDR)
- Potentiometer
- LED
- MQTT server
### Software
- **Arduino IDE**: Download and install from [Arduino's official website](https://www.arduino.cc/en/software).
- **Required Libraries**:
  - DHT Sensor Library
  - Adafruit Unified Sensor Library
  - WiFiNINA
  - PubSubClient
## System Overview

The Plant Monitor system collects environmental data using sensors and transmits it to an MQTT broker via WiFi. The Chrono Lumina LEDs provide real-time visual feedback based on sensor readings.

### **Workflow**:

1. **Data Collection**:
   - ASAIR AM2122 Temperature and Humidity Sensor collects temperature and humidity.
   - light-dependent resistor measures light intensity.

2. **Data Processing**:
   - The Arduino MKR WiFi 1010 processes sensor data and determines the appropriate LED feedback (color and brightness).

3. **Data Transmission**:
   - Sensor readings are sent to an MQTT broker (e.g., `mqtt.cetools.org`) using the MQTT protocol.

4. **Visualization**:
   - Data can be visualized through an MQTT client or the colour changing will be happened on LEDs.
  
<img src="/result/interactive.png" alt="result" style="zoom:10%;" />
## Installation and Setup
### Hardware setup
- **ASAIR AM2122 Temperature and Humidity Sensor**:
  - Connect `Data` to  pin D2 on the MKR WiFi 1010.
  - Connect `VCC` to the `5V` pin and `GND` to the `GND` pin.
- **light-dependent resistor**:
  - Connect one leg to A1 pin and the other to `GND` (with a 10k ohm pull-up resistor to `VCC`).
- **Potentiometer**:
  - Connect the OTA pin to A2 pin, and the outer pins to `VCC` and `GND`.
### Configure WiFi and MQTT

create a .h file to store your mqtt server information:

```arduino_secrets.h
#define SECRET_SSID "your_wifi_ssid"
#define SECRET_PASS "your_wifi_password"
#define SECRET_MQTTUSER "your_server_username"
#define SECRET_MQTTPASS "your_server_passport";
```
### Upload the Code

1. Open the Arduino IDE.
2. Select **Arduino MKR WiFi 1010** as the board.
3. Choose the correct port under **Tools > Port**.
4. Upload the `.ino` file to the board.

### Test the System

- Power on the device and observe LED feedback.
- Use an MQTT client (e.g., MQTT Explorer) to check the topics and the result should looks like figure below. (There is not much evidence of LEDS pictures since the Chrono Lumina unit has not worked since the last reset. However, Mqtt Explorer can indicate that the LEDS should be on.)
<img src="/result/result2.png" alt="result" style="zoom:1%;" />


