#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>

const char *ssid = "JOPA";
const char *password = "qjuehn123";

const int rxPin = D2;
const int txPin = D3;

SoftwareSerial NodeMCU(rxPin, txPin);

WiFiServer server(23); // 192.168.4.1

void setup()
{
  delay(1000);

  NodeMCU.begin(115200);
  Serial.begin(9600);

  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();

  Serial.print("Start TCP(telnet) server on ");
  Serial.println(myIP.toString());

  server.begin();
  server.setNoDelay(true);
}

void loop()
{
  if (server.hasClient())
  {
    digitalWrite(LED_BUILTIN, LOW);

    WiFiClient client = server.available();

    if (client.connected())
    {
      Serial.println("Connected to client!");

      String msg = "";
      while (client.connected())
      {
        int ch = client.read();
        if (ch != -1)
        {
          char c = ch;
          msg.concat(c);
        }
      }

      Serial.print(msg);
      NodeMCU.print(msg);

      Serial.println("\nDisconnected from client!");
      client.stop();
    }
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
