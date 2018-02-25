#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

const char* ssid = "tech"; //Enter your wifi network SSID
const char* password ="12345678"; //Enter your wifi network password

const int SERVER_PORT=5000;
const int BAUD_RATE = 115200;
int i;
byte packetBuffer[1]={0};

WiFiUDP Udp;
IPAddress ip(192,168,43,54);
IPAddress ip1;

void connectWifi() 
{
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
  
  ip1 = WiFi.localIP();
  Serial.println("This Device IP Address is:");
  Serial.print(ip1);
  Serial.println("Connected to:");
  Serial.println(ip);
}


void setup() 
{
  Serial.begin(BAUD_RATE);
  pinMode(D0,INPUT);
  pinMode(D1,INPUT);
  connectWifi();
  Udp.beginPacket(ip,SERVER_PORT);
}

void loop()
{
  Udp.beginPacket(ip,SERVER_PORT);
  packetBuffer[0]=1;
  delay(2000);
  Udp.write(packetBuffer,1);
  Serial.print(packetBuffer[0]);  
  Serial.println();
  Udp.endPacket();
}
