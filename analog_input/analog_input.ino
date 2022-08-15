void setup() {
  Serial.begin(9600);

  analogReadResolution(12);
}

void loop() {
  float analog_channel_0 = analogRead(2);
  Serial.printf("read: %f\n",analog_channel_0);
  delay(500);
}
