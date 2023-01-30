#include <WiFi.h>
#include <WebSocketsServer.h>

const char* ssid = "VM47E4856";               //"Douglas";
const char* password = "7z4ycmhbRaMh";        //"hzzs03322";

#define LED 2

WebSocketsServer webSocket = WebSocketsServer(81);

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

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
  digitalWrite(LED, WiFi.status());
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
      // send message to client
      webSocket.sendTXT(num, "Connected");
      break;
    }
    case WStype_TEXT:
      Serial.printf("[%u] Received Text: %s\n", num, payload);
      // send message to client
      webSocket.sendTXT(num, "message here");
      break;
    case WStype_BIN:
      Serial.printf("[%u] Received Binary: ", num);
      Serial.write(payload, length);
      Serial.println();
      // send message to client
      webSocket.sendBIN(num, payload, length);
      break;
  }
}
