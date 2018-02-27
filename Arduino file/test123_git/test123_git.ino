#include <WiFiUdp.h>

#include <ESP8266WiFi.h>

const char* ssid = "tech"; //Enter your wifi network SSID
const char* password ="12345678"; //Enter your wifi network password

int SERVER_PORT=5000;

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

void motorhigh(){
   pinMode(D0,HIGH);
   pinMode(D1,HIGH);
   pinMode(D2,HIGH);
   pinMode(D3,HIGH);
}
void motorlow(){
   pinMode(D0,LOW);
   pinMode(D1,LOW);
   pinMode(D2,LOW);
   pinMode(D3,LOW);

}

void threshold(int value)
{
  if(value>3500&& value<=4500)
  {
    motorhigh();
    delay(3000);
    motorlow();
  }
  
  else if(value>4500&& value<=5500)\
  {
    motorhigh();
    delay(5000);
    motorlow();
  }
  else if(value>=5500)
  {
    motorhigh();
    delay(7000);
    motorlow();
  }
  else if(value<=3500)
  {
    motorhigh();
    delay(2000);
    motorlow();
  }
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
            Udp.read(packetBuffer,noBytes);
              
              for(i=0;i<noBytes;i++)
                buff[i]=packetBuffer[i]-48;
              
              for(i=noBytes-1;i>=0;i--)
              {
                val+=k*buff[i];
                 k=k*10;
              }
              
              if(val>0)
              {
                threshold(val);
                Serial.println(val);
                Serial.println();
              }
              
              else
              {
                val=val+48;
                movebot(val);
                Serial.println(val);
                Serial.println(); 
              }

          }
}
