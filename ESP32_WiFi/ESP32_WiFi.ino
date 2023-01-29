/*

  WiFi Connection

Description:
  Exemple to connect the ESP32 to WiFi;
  Set WiFi mode as station mode;
  Read IP Address;
  Scan Networks.

Board:
  ESP32 Dev Module

Created:        Updated:
  27/01/2023      27/01/2023

*/

#include <WiFi.h>

const char* ssid = "Douglas";
const char* password = "hzzs03322";

int serialPack[4];

#define LED 2

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);

  WiFi.mode(WIFI_STA);
  // initialize WiFi connection
  WiFi.begin(ssid, password);
  // set hostname
//  WiFi.hostname("Datalogger");

  //check WiFi Status
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // index available Networks
  int  numNetworks = WiFi.scanNetworks();

  for(int i = 0; i < numNetworks; i++){
    Serial.print(i);
    Serial.print(" - WiFi Network: ");
    Serial.println(WiFi.SSID(i));         // print WiFi Network
//    Serial.println(WiFi.RSSI(i));
//    Serial.println("");
  }
  delay(1000);

  if (Serial.available()) {
    for (int i = 0; i < 4; i++) {
      serialPack[i] = Serial.read();
      delay(5);
    }
  }
  int index = serialPack[0] - '0';
  Serial.println(WiFi.SSID(index));

  // scan Networks
  // connect to a known Network
  // 



  if(WiFi.status() == WL_CONNECTED){
    digitalWrite(LED, HIGH);
  } else{
    digitalWrite(LED,LOW);
  }

}