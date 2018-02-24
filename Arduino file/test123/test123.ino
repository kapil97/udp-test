#include <WiFiUdp.h>

#include <ESP8266WiFi.h>

const char* ssid = "tech"; //Enter your wifi network SSID
const char* password ="12345678"; //Enter your wifi network password

 int SERVER_PORT;
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
  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  connectWifi();
}

void movebot(int dir)
{
  if(dir==1)
  {
    Serial.println("Left Move Kia");
  }
  else if(dir==2)
  {
    Serial.println("Right Move Kia");
  }
}


void loop() 
{
 
    int i,val=0,k=1;
    int dir;
    int noBytes = Udp.parsePacket();
    int buff[10];
       if ( noBytes ) 
         {
            Serial.print(millis() / 1000);
            Serial.print(":Packet of ");
            Serial.print(noBytes);
            Serial.print(" received from ");
            Serial.print(Udp.remoteIP());
            Serial.print(":");
            Serial.println(Udp.remotePort());
            if(Udp.remotePort()==5000)
            {
              Udp.read(packetBuffer,noBytes);
              for(i=0;i<noBytes;i++)
                buff[i]=packetBuffer[i]-48;
              for(i=noBytes-1;i>=0;i--)
              {
                val+=k*buff[i];
                 k=k*10;
              }
            Serial.println(val);
            Serial.println();
           }
           else
           if(Udp.remotePort()==3000)
           {
              Udp.read(packetBuffer,noBytes);
                for(i=0;i<noBytes;i++)
                {
                  dir=packetBuffer[i];
                  movebot(dir);
                }
           }
          
      }
}
