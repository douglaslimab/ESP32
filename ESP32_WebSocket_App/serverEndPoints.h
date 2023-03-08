void webPage() {
  server.send(200, "text/html", webpageCode);
} 

void status(){
  String getTimestamp = "";
  String readSensor1 = String(analogRead(34));
  delay(5);
  String readSensor2 = String(analogRead(36));

  statusJson = "{\"Timestamp\":\""+getTimestamp+"\",";
  statusJson += "\"Sensor 1\":\""+readSensor1+"\",";
  statusJson += "\"Sensor 2\":\""+readSensor2+"\"}";

  server.send(200, "text/html", statusJson);
}
