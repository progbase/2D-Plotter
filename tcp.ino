#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <SoftwareSerial.h>

const char *ssid = "JOPA";
const char *password = "qjuehn123";

WiFiServer server(23); //   192.168.4.1

SoftwareSerial s(D6, D5);

void setup() {
  delay(1000);
  Serial.begin(9600);
  s.begin(9600);

  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();

  Serial.print("Start TCP server on ");
  Serial.println(myIP.toString());

  server.begin(); // start telnet server
  server.setNoDelay(true);
}

void loop() {
  if(server.hasClient()){
    digitalWrite(LED_BUILTIN, LOW);

    WiFiClient client = server.available();

    if (client.connected()) {
      Serial.println("Con client");
    
      while(client.connected()) {
        int ch = client.read();
        if (ch != -1) {
          char c = ch;
          Serial.print(c);
          s.write(ch);
//          Serial.write(ch);
          
        }
        
        // Serial.write();
      }
  
      Serial.println(" Discon client");
      client.stop();
    }
  } else{
    digitalWrite(LED_BUILTIN, HIGH);
  }
} 
