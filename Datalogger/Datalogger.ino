#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <ESP32Time.h>

ESP32Time rtc(3600);

const char* ssid = "Douglas";
const char* password = "hzzs03322";

#define LED 2

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

boolean LEDtoggle = false;
boolean LEDonoff = false;
boolean send_btn = false;
boolean run_btn = false;
int led_interval = 10;

String JSONtxt;
int serialPack[4];

int array_length = 255;
String time_list[255];
int ch1_list[255];
int ch2_list[255];
int pointer = 0;

unsigned long currentMillis;
long previousMillis = 0;
long previousMillis2 = 0;
long previousMillis3 = 0;
float loopTime = 10;

#include "html_page.h"
#include "functions.h"

void setup()
{
  Serial.begin(9600);

  rtc.setTime(30, 16, 9, 18, 8, 2022);

  pinMode(LED, OUTPUT);
  
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", webpage);

  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop()
{
  webSocket.loop();
  server.handleClient();

  String LEDstatus = "OFF";
  if(LEDonoff == true) LEDstatus = "ON";
  String runstatus = "OFF";
  if(run_btn == true) runstatus = "ON";
  String sendstatus = "OFF";
  if(send_btn == true) sendstatus = "ON";

  JSONtxt = "{\"LEDonoff\":\""+LEDstatus+"\",\"run_btn\":\""+runstatus+"\",\"send_btn\":\""+sendstatus+"\"}";
  webSocket.broadcastTXT(JSONtxt);

  
  currentMillis = millis();

  serialData();
  // LED status ------------------------------------------------------------------------
  if (currentMillis - previousMillis >= led_interval) {
    previousMillis = currentMillis;

    // blinking LED means board connected
    LEDtoggle = !LEDtoggle;
    digitalWrite(LED, LEDtoggle);
  }

  //---------------------------------------------------------------------------
  if (currentMillis - previousMillis2 >= 1000) {
    previousMillis2 = currentMillis;

    // run data log
    if(serialPack[0] == 'r'||run_btn){
      led_interval = 500;
      time_list[pointer] = rtc.getTime();
      ch1_list[pointer] = analogRead(34);
      delay(2);
      ch2_list[pointer] = analogRead(36);
    
      Serial.print(time_list[pointer]);
      Serial.print(", ");
      Serial.print(ch1_list[pointer]);
      Serial.print(", ");
      Serial.println(ch2_list[pointer]);
      
      pointer++;
      if(pointer == array_length) pointer = 0;
    }

    // clear array
    if(serialPack[0] == 'c'){

      ch1_list[pointer] = 0;
      ch2_list[pointer] = 0;
      
      pointer++;
      if(pointer == array_length) pointer = 0;
    }
  }

  //-------------------------------------------------------------------------------------
  if (currentMillis - previousMillis3 >= 1000) {
    previousMillis3 = currentMillis;

    // print data
    if(serialPack[0] == 'p'||send_btn){
      led_interval = 10;
      for(int i = 0; i <= pointer ; i++){
        Serial.print(time_list[i]);
        Serial.print(", ");
        Serial.print(ch1_list[i]);
        Serial.print(", ");
        Serial.println(ch2_list[i]);
      }
      pointer = 0;
    }
  }
}