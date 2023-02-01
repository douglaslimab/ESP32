void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  String payloadString = (const char*)payload;
  Serial.print("payloadString= ");
  Serial.println(payloadString);

  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        // send message to client
        webSocket.sendTXT(num, "Connected");
        break;
      }
    case WStype_TEXT:
      {
        //      Serial.printf("[%u] Received Text: %s\n", num, payload);
        // send message to client
        byte separator = payloadString.indexOf('=');
        String var = payloadString.substring(0, separator);
        String val = payloadString.substring(separator + 1);

        if (var == "LEDonoff") {
          LEDonoff = false;
          if (val == "ON") LEDonoff = true;
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