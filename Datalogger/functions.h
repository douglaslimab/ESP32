void webpage()
{
  server.send(200,"text/html", webpageCode);
}
//=====================================================
//function process event: new data received from client
//=====================================================
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t welength)
{
  String payloadString = (const char *)payload;
  Serial.print("payloadString= ");
  Serial.println(payloadString);

  if(type == WStype_TEXT) //receive text from client
  {
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
    if(var == "send_btn") {
      send_btn = false;
      if(val == "ON") send_btn = true;
    }
    if(var == "run_btn") {
      run_btn = false;
      if(val == "ON") run_btn = true;
    }
  }
}

void serialData(){
  if (Serial.available()) {
    for (int i = 0; i < 4; i++) {
      serialPack[i] = Serial.read();
      delay(5);
    }
  }
}