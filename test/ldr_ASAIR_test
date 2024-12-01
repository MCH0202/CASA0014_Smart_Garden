#include "Adafruit_Sensor.h"
#include "Adafruit_AM2320.h"
#include <WiFiNINA.h>   
#include <PubSubClient.h>
#include "arduino_secrets.h" 
#include <utility/wifi_drv.h>   // library to drive to RGB LED on the MKR1010

/*
**** please enter your sensitive data in the Secret tab/arduino_secrets.h
**** using format below

#define SECRET_SSID "ssid name"
#define SECRET_PASS "ssid password"
#define SECRET_MQTTUSER "user name - eg student"
#define SECRET_MQTTPASS "password";
 */

const char* ssid          = SECRET_SSID;
const char* password      = SECRET_PASS;
const char* mqtt_username = SECRET_MQTTUSER;
const char* mqtt_password = SECRET_MQTTPASS;
const char* mqtt_server = "mqtt.cetools.org";
const int mqtt_port = 1884;
int status = WL_IDLE_STATUS;     // the Wifi radio's status

//rheostat pin setting
int rhe = A2;

//ASAIR pin setting
int ASAIR = A3;

//ldr pin setting
int ldr = A1;

//ldr setting
int ldrValue;

//ASAIR setting
float tempC;
float humidity;
Adafruit_AM2320 sensor = Adafruit_AM2320();

//rheostat setting

int resistance;

//Chrono Lumina Light lux RGB setting
int R;
int G;
int B;

//Chrono Lumina Light temperature RGB setting
int R2;
int G2;
int B2;

//Chrono Lumina Light humidity RGB setting
int R3;
int G3;
int B3;

//Brightness setting
int brightness;

WiFiServer server(80);
WiFiClient wificlient;

WiFiClient mkrClient;
PubSubClient client(mkrClient);

// edit this for the light
char mqtt_topic_pixel[] = "student/CASA0014/light/17/pixel/";
char mqtt_topic_pixel1[] = "student/CASA0014/light/18/pixel/";
char mqtt_topic_pixel2[] = "student/CASA0014/light/19/pixel/";
char mqtt_topic_brightness[] = "student/CASA0014/light/17/brightness/";
char mqtt_topic_brightness1[] = "student/CASA0014/light/18/brightness/";
char mqtt_topic_brightness2[] = "student/CASA0014/light/19/brightness/";

void setup() {

  pinMode(rhe,INPUT);
  pinMode(ldr, INPUT);
  Serial.begin(115200);


  Serial.begin(115200);
  delay(1000);

  WiFi.setHostname("Muchen ucfnmh1");
  startWifi();
  client.setServer(mqtt_server, mqtt_port);
  Serial.println("setup complete");
}

void loop() {

  // we need to make sure the arduino is still connected to the MQTT broker
  // otherwise we will not receive any messages
  if (!client.connected()) {
    reconnectMQTT();
  }

  // we also need to make sure we are connected to the wifi
  // otherwise it will be impossible to connect to MQTT!
  if (WiFi.status() != WL_CONNECTED){
    startWifi();
  }

  // check for messages from the broker and ensuring that any outgoing messages are sent.
  client.loop();
  rheostatdetect();
  ldrdetect();
  sendmqtt_brightness();
  sendmqtt_lux();
  sendmqtt_temp();
  sendmqtt_humidity();
  Serial.println("sent a message");
  delay(5000);
  
}

void startWifi(){
    
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // Function for connecting to a WiFi network
  // is looking for UCL_IoT and a back up network (usually a home one!)
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    // loop through all the networks and if you find UCL_IoT or the backup - ssid1
    // then connect to wifi
    Serial.print("Trying to connect to: ");
    Serial.println(ssid);
    for (int i = 0; i < n; ++i){
      String availablessid = WiFi.SSID(i);
      // Primary network
      if (availablessid.equals(ssid)) {
        Serial.print("Connecting to ");
        Serial.println(ssid);
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
          delay(600);
          Serial.print(".");
        }
        if (WiFi.status() == WL_CONNECTED) {
          Serial.println("Connected to " + String(ssid));
          break; // Exit the loop if connected
        } else {
          Serial.println("Failed to connect to " + String(ssid));
        }
      } else {
        Serial.print(availablessid);
        Serial.println(" - this network is not in my list");
      }

    }
  }


  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void reconnectMQTT() {
  if (WiFi.status() != WL_CONNECTED){
    startWifi();
  } else {
    //Serial.println(WiFi.localIP());
  }

  // Loop until we're reconnected
  while (!client.connected()) {    // while not (!) connected....
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "LuminaSelector";
    clientId += String(random(0xffff), HEX);
    
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");
      // ... and subscribe to messages on broker
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
  // send a message to update the color
void sendmqtt_lux(){
  char mqtt_pixel_message[100];
  //edit content that will be sent to mqtt server later
  for (int i = 0; i < 12; i++) {
  sprintf(mqtt_pixel_message, "{\"pixelid\": %d, \"R\": %d, \"G\": %d, \"B\": %d, \"W\": 0}", i, R, G, B);
  
  Serial.println(mqtt_topic_pixel);
  Serial.println(mqtt_pixel_message);

  if (client.publish(mqtt_topic_pixel, mqtt_pixel_message)) {
    Serial.println("lux pixels published successfully");
  } else {
    Serial.println("Failed to publish lux pixel message");
  }
  delay(10);
  }
}

void sendmqtt_temp(){
  char mqtt_temp_message[100];
  for (int j = 0; j < 12; j++) {
  sprintf(mqtt_temp_message, "{\"pixelid\": %d, \"R\": %d, \"G\": %d, \"B\": %d, \"W\": 0}", j, R2, G2, B2);
  
  Serial.println(mqtt_topic_pixel1);
  Serial.println(mqtt_temp_message);

  if (client.publish(mqtt_topic_pixel1, mqtt_temp_message)) {
    Serial.println("temp pixels published successfully");
  } else {
    Serial.println("Failed to publish temp pixel message");
  }
  delay(10);
  }
}

void sendmqtt_humidity(){
  char mqtt_humidity_message[100];
  for (int k = 0; k < 12; k++) {
  sprintf(mqtt_humidity_message, "{\"pixelid\": %d, \"R\": %d, \"G\": %d, \"B\": %d, \"W\": 0}", k, R3, G3, B3);
  
  Serial.println(mqtt_topic_pixel2);
  Serial.println(mqtt_humidity_message);
  //pubish content created before and test if it works
  if (client.publish(mqtt_topic_pixel2, mqtt_humidity_message)) {
    Serial.println("humidity pixels published successfully");
  } else {
    Serial.println("Failed to publish humidity pixel message");
  }
  delay(10);
  }
}

void sendmqtt_brightness(){
  char mqtt_brightness_message[100];
  brightness = resistance;
  //edit brightness content
  sprintf(mqtt_brightness_message, "{\"brightness\": %d}", brightness);
  Serial.println(mqtt_topic_brightness);
  Serial.println(mqtt_brightness_message);
  //pubish content created before and test if it works
  if (client.publish(mqtt_topic_brightness, mqtt_brightness_message)) {
    Serial.print("brightness published successfully");
  } else{
    Serial.println("Failed to publish brightness message");
  }
}
//-----------------------------------------------------------------------------------------
//collect sensor data
void ldrdetect(){
  ldrValue =map(analogRead(ldr), 0, 1023, 100, 0);
  if (ldrValue < 30){
    R = 0; G = 0; B = 255;          // Low Light - blue
  }else if (ldrValue < 90) { 
    R = 0; G = 255; B = 0;          // Adequate light - green
  }else {                           
    R = 255; G = 0; B = 0;          // Excessive light - red
  }
}

void ASAIRmeasuring(){
  //get data from sensor
  float tempC = sensor.readTemperature();
  float humidity = sensor.readHumidity();
  //tempC RGB setting
  if (tempC < 15){
    R2 = 0; G2 = 0; B2 = 255;          // Low temp - blue
  }else if (tempC < 25) { 
    R2 = 0; G2 = 255; B2 = 0;          // Adequate tempC - green
  }else {                           
    R2 = 255; G2 = 0; B2 = 0;          // Excessive tempC - red
  }

  if (humidity < 40){
    R3 = 0; G3 = 0; B3 = 255;          // Low humidity - blue
  }else if (humidity < 60) { 
    R3 = 0; G3 = 255; B3 = 0;          // Adequate humidity - green
  }else {                           
    R3 = 255; G3 = 0; B3 = 0;          // Excessive humidity - red
  }
}

//slide rheostat data collect
void rheostatdetect(){
  int resis = analogRead(rhe);
  Serial.println(resis);
  resistance = map(analogRead(rhe), 0, 1023, 0, 119);
  Serial.println(resistance);
}
