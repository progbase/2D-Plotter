#include <SoftwareSerial.h>
SoftwareSerial s(15, 14);
int data;

void setup() {
  s.begin(9600);
  Serial.begin(9600);
}
 
void loop() {
  if (s.available() > 0) {
    data = s.read();
    Serial.println(data);
  }
}