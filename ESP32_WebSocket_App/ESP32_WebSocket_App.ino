#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

const char* ssid = "VM47E4856";               //"Douglas";
const char* password = "7z4ycmhbRaMh";        //"hzzs03322";
const char webpageCode[] PROGMEM =
R"=====(
 <html>
  <head></head>
  <body>
    <button type="button" ONCLICK="button()">LED</button>
    <p id="btn" >OFF</p>
    <script>
      initWebSocket();
      function initWebSocket(){
        websock = new WebSocket('ws://'+window.location.hostname+':81/');
        websock.onmessage = function(evt){
          jsonOBJ = JSON.parse(evt.data);
          document.getElementById('btn').innerHTML = jsonOBJ.LEDonoff;
        }
      }
     function button() {
        btn = 'LEDonoff=ON';
        if(document.getElementById('btn').innerHTML == 'ON') {
          btn = 'LEDonoff=OFF';
        }
        websock.send(btn);
     }
    </script>
  </body>
</html>
)=====";

#define LED 2

String jsonTXT;
boolean LEDonoff = false;

WebServer server(80);
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

  server.on("/", webPage);
  server.begin();

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
  server.handleClient();
  digitalWrite(LED, WiFi.status());
  
  String LEDstatus = "OFF";
  if(LEDonoff == true) LEDstatus = "ON";

  jsonTXT = "{\"LEDonoff\":\""+LEDstatus+"\"}";
  webSocket.broadcastTXT(jsonTXT);
}

void webPage(){
  server.send(200, "text/html", webpageCode);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  String payloadString = (const char *)payload;
  Serial.print("payloadString= ");
  Serial.println(payloadString);
  
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
    case WStype_TEXT:{
//      Serial.printf("[%u] Received Text: %s\n", num, payload);
      // send message to client
      byte separator=payloadString.indexOf('=');
      String var = payloadString.substring(0,separator);
      Serial.print("var= ");
      Serial.println(var);
      String val = payloadString.substring(separator+1);
      Serial.print("val= ");
      Serial.println(val);
      Serial.println(" ");

      if(var == "LEDonoff") {
        LEDonoff = false;
        if(val == "ON") LEDonoff = true;
      }
      break;
    }
    case WStype_BIN:
      Serial.printf("[%u] Received Binary: ", num);
      Serial.write(payload, length);
      Serial.println();
      // send message to client
      webSocket.sendBIN(num, payload, length);
      break;
  }
}
