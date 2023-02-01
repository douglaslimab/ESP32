#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include "webpageCode.h"

const char* ssid = "VM47E4856";         //"Douglas";
const char* password = "7z4ycmhbRaMh";  //"hzzs03322";

#define LED 2

String jsonTXT, statusJson;
boolean LEDonoff = false;

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

#include "websocketEvent.h"
#include "serverEndPoints.h"

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi..");
    delay(1000);
  }

  Serial.println("Connected to WiFi");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", webPage);
  server.on("/status", status);
  server.begin();

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
  server.handleClient();
  digitalWrite(LED, WiFi.status());

  String LEDstatus = "OFF";
  if (LEDonoff == true) LEDstatus = "ON";

  jsonTXT = "{\"LEDonoff\":\"" + LEDstatus + "\"}";
  webSocket.broadcastTXT(jsonTXT);
}