#define LED_1 2

class Led {
private:
  byte pin;

public:
  Led(byte pin) {
    this->pin = pin;
    init();
  }

  void init() {
    pinMode(pin, OUTPUT);
    off(0);
  }

  void on(int time) {
    digitalWrite(pin, HIGH);
    delay(time);
  }

  void off(int time) {
    digitalWrite(pin, LOW);
    delay(time);
  }
};

Led led1(LED_1);

void setup() {
  led1.init();
}

void loop() {
  led1.on(500);
  led1.off(500);
}