# 🌱 Smart Plant Monitoring System

## A Spark of Inspiration
In the CASA0016 course, I developed an automated irrigation system designed to prevent prevent me from forgetting to water. I have to say that I really don't have a good memory, which leads to my potted plants at home often dying. The system automates irrigation by monitoring soil moisture and rainfall through sensors.
So far, it occurred to me that since I already have an automatic irrigation system to keep my houseplants alive, why not let them live a little better? So I had this idea of being able to see directly how well my plants are living.

## Project Objectives
The aim of this project is to develop an Arduino-based intelligent plant monitoring system to achieve real-time monitoring and visual feedback of plant growth environment. By integrating multiple sensors (LDR, temperature and humidity sensors), the system is able to collect the environmental parameters around the plants (including light intensity, air temperature and humidity) and transmit the data to the Chrono Lumina Light by using the MQTT protocol. the colour change of the light will reflect the plant's growing environment condition, which will help the user to better understand and improve the plant's growing conditions.

## Structure
### test folder              
#### ldr_rhe_test            
Test code (test LDR to detect light intensity and slide rheostat control brightness as well as publish RGB settings and brightness setting to mqtt)  
#### ldr_ASAIR_test  
Test code (test LDR, ASAIR Sensor to detect light intensity, temperature and humidity, publish RGB settings to mqtt)  
