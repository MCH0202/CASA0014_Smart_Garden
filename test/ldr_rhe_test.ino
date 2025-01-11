//rheostat pin setting
int rhe = A2;

//ldr pin setting
int ldr = A1;

//ldr setting
int ldr = A1;
int ldrValue;

//rheostat setting

int resistance;

//Chrono Lumina Light RGB setting
int R;
int G;
int B;

//Brightness setting
int brightness;

void setup() {
  // put your setup code here, to run once:
  pinMode(rhe,INPUT);
  pinMode(ldr, INPUT);
  Serial.begin(115200);
}

void loop() {
  rheostatdetect();
  delay(2000);
  ldrdetect();
  delay(2000);
  messageprint();
  delay(2000);

}

void rheostatdetect(){
  int resis = analogRead(rhe);
  Serial.println(resis);
  resistance = map(analogRead(rhe), 0, 1023, 0, 119);
  Serial.println(resistance);
}

void ldrdetect(){
  ldrValue =map(analogRead(ldr), 0, 1023, 100, 0);
  if (ldrValue < 30){
    R = 0; G = 0; B = 255;          // Low Light - blue
  }else if (ldrValue < 70) { 
    R = 0; G = 255; B = 0;          // Adequate light - green
  }else {                           
    R = 255; G = 0; B = 0;          // Excessive light - red
  }
  Serial.println(ldrValue);
  Serial.print(R);
  Serial.print(" ");
  Serial.print(G);
  Serial.print(" ");
  Serial.println(B);
}

void messageprint(){

  char mqtt_message[600];
  String message = "{\"allLEDs\": [";

  for (int i = 0; i < 12; i++) {
    message += "{\"pixelid\": " + String(i) + 
               ", \"R\": " + String(R) + 
               ", \"G\": " + String(G) + 
               ", \"B\": " + String(B) + 
               ", \"W\": 0}";
    if (i < 11) message += ", ";
  }
  message += "]}";

  Serial.println(message);
  brightness = resistance;
  String brightnessmsg = "{\"brightness\":" + String(brightness) + "}";
  Serial.println(brightnessmsg);
}
