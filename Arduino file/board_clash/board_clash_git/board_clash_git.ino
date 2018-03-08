#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

const char* ssid = "cd"; //Enter your wifi network SSID
const char* password ="nivedita"; //Enter your wifi network password

const int SERVER_PORT=5000;
const int BAUD_RATE = 115200;
int i;
byte packetBuffer[1]={0};

WiFiUDP Udp;
IPAddress ip(192,168,43,129);
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
  Serial.println("WiFi connected");
  Serial.println("This Device IP Address is:");
  Serial.print(ip1);
  Serial.println("Connected to:");
  Serial.println(ip);
  
   
}


void setup() 
{
  Serial.begin(BAUD_RATE);
  pinMode(D3,INPUT_PULLUP);
  pinMode(D4,INPUT_PULLUP);
  connectWifi();
  //Udp.beginPacket(ip,SERVER_PORT);
}

void loop()
{
  packetBuffer[0]=0;
  Udp.beginPacket(ip,SERVER_PORT);
  
  if(digitalRead(D3)==LOW)
  {
  packetBuffer[0]=1;
  Serial.println("D3 pressed");
  }
  
  else if(digitalRead(D4)==LOW)
  {
   packetBuffer[0]=2;
   Serial.println("D4 pressed");
  }
  else 
  { packetBuffer[0]=0;
    Serial.println("No Value");
  }
  
  
  Udp.write(packetBuffer,1);
  Serial.print(packetBuffer[0]);  
  Serial.println();
  delay(150);
  Udp.endPacket();
}
