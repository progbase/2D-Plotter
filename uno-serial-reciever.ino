#include <SoftwareSerial.h>

const int rxPin = 0;
const int txPin = 1;

SoftwareSerial ArduinoUNO(rxPin, txPin);

void setup() {
  ArduinoUNO.begin(115200);
  Serial.begin(9600);

  Serial.println("Started reading from NODE MCU");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (ArduinoUNO.available()) {
    Serial.print("Message: ");
    Serial.print(ArduinoUNO.readString());
    Serial.println("\n----------------------");
  }
  delay(300);
}
