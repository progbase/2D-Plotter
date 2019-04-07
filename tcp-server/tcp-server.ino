#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <WiFiClient.h>

const char *ssid = "JOPA";
const char *password = "qjuehn123";

const int rxPin = D2;
const int txPin = D3;

SoftwareSerial NodeMCU(rxPin, txPin);

WiFiServer server(23); // 192.168.4.1
WiFiClient client;

String msg = "";

String parseMessage(WiFiClient &client) {
    String str = "";
    while (client.connected()) {
        int ch = client.read();
        if (ch != -1) {
            char c = ch;
            str.concat(c);
        }
    }
    return str;
}

void printMessage(String &message) {
    Serial.print("---(");
    Serial.print(message.length());
    Serial.println(")-------------------------------------------");
    Serial.println(message);
    Serial.println("-------------------------------------------------");
}

void setup() {
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

void loop() {
    if (server.hasClient()) {
        digitalWrite(LED_BUILTIN, LOW);
        client = server.available();

        if (client.connected()) {
            Serial.println("\nConnected to client!");

            msg = parseMessage(client);
            NodeMCU.print(msg);

            printMessage(msg);

            client.stop();
            Serial.println("Disconnected from client!\n");
        }

        digitalWrite(LED_BUILTIN, HIGH);
    }
}
