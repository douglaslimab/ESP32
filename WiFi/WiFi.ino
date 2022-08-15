#include <Arduino.h>
#include "WiFi.h"
// #include <WebServer.h>

#define WIFI_NETWORK "Douglas"
#define WIFI_PASSWORD "hzzs03322"
#define WIFI_TIMEOUT_MS 20000

void connectToWiFi(){
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  unsigned long startAttemptTime = millis();

  while(WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS){
    Serial.print(".");
    delay(100);
  }

  if(WiFi.status() != WL_CONNECTED){
    Serial.println(" Failed!");
  }else{
    Serial.print("Connected!");
    Serial.println(WiFi.localIP());
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  connectToWiFi();
}

void loop() {
  // put your main code here, to run repeatedly:

}
