#include <SoftwareSerial.h>

const int rxPin = D2;
const int txPin = D3;

SoftwareSerial NodeMCU(rxPin, txPin);

void setup()
{
  NodeMCU.begin(115200);
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);
}

void loop()
{
  NodeMCU.print("101010011");

  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);

  delay(4000);
}
