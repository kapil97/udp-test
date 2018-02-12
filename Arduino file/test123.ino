#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

const char* ssid = "Kamli"; //Enter your wifi network SSID
const char* password ="87654321"; //Enter your wifi network password


const int SERVER_PORT = 5000;
const int BAUD_RATE = 115200;

byte incomingByte=0;

byte packetBuffer[512];

WiFiUDP Udp;
IPAddress ip;

void connectWifi() {
  Serial.println();
  Serial.println();
  Serial.print("Connecting to WIFI network");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Udp.begin(SERVER_PORT);
  ip = WiFi.localIP();
  Serial.println(ip);
}


void setup() {
  Serial.begin(BAUD_RATE);

  connectWifi();
}

void loop() {
  int noBytes = Udp.parsePacket();
  String received_command = "";
  if ( noBytes ) 
  {
    Serial.print(millis() / 1000);
    Serial.print(":Packet of ");
    Serial.print(noBytes);
    Serial.print(" received from ");
    Serial.print(Udp.remoteIP());
    Serial.print(":");
    Serial.println(Udp.remotePort());

    Udp.read(packetBuffer,noBytes);
    Serial.println();

    Serial.println(packetBuffer[0]);
    incomingByte = packetBuffer[0];
    Serial.println();
  }
  
}

