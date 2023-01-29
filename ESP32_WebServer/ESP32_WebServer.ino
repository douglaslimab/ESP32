#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "VM47E4856";               //"Douglas";
const char* password = "7z4ycmhbRaMh";        //"hzzs03322";

WebServer server(80);

#define LED 2

void setup(){
  Serial.begin(115200);

  pinMode(LED, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting..");
    delay(1000);
  }

  Serial.println("Connected!!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", webpage);
  server.on("/analog", handleAnalogRead);
  server.begin();
}

void loop(){
  server.handleClient();
  if(WiFi.status()){
    digitalWrite(LED, HIGH);
  } else{
    digitalWrite(LED, LOW);
  }
}

void webpage(){
  server.send(200, "text/html", "<h1>Home</h1>");
}

void handleAnalogRead(){
  int analogChannel = analogRead(34);
  delay(5);
  String json = "{\"Channel 1\": " + String(analogChannel) + "}";
  server.send(200, "text/html", json);
//  server.send(200, "text/html", "{\"Channel 1\":\""+analogChannel+"\"}");
}