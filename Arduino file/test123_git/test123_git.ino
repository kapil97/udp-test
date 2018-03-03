#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
//agar slow ho rha hai to ye serial prints sab nikal do from void loop
int rightMotor2 = 0;    //  - right Motor -
int rightMotor1 = 4;    //  - right Motor +*/
int leftMotor2 =  5;    //  - left Motor - 
int leftMotor1 = 16;    //  - left Motor +

const char* ssid = "Oneplus"; //Enter your wifi network SSID
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
  pinMode(leftMotor1, OUTPUT); 
  pinMode(leftMotor2, OUTPUT);  
  pinMode(rightMotor1, OUTPUT);  
  pinMode(rightMotor2, OUTPUT);  
  /*digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,LOW);
  digitalWrite(rightMotor2,LOW);
   */connectWifi();
}

void moveForwards() {
  Serial.println("Forward");
  analogWrite(leftMotor1,512);
  analogWrite(leftMotor2,0);
  analogWrite(rightMotor1,512);
  analogWrite(rightMotor2,0);
}


void moveBackwards() {
  Serial.println("Backwards");
  analogWrite(leftMotor1,0);
  analogWrite(leftMotor2,512);
  analogWrite(rightMotor1,0);
  analogWrite(rightMotor2,512);
}

void turnRight() {
  Serial.println("Hard Right");
  analogWrite(leftMotor1,512);
  analogWrite(leftMotor2,0);
  analogWrite(rightMotor1,0);
  analogWrite(rightMotor2,512);
}

void turnLeft() {
  Serial.println("Hard Left");
  analogWrite(leftMotor1,0);
  analogWrite(leftMotor2,512);
  analogWrite(rightMotor1,512);
  analogWrite(rightMotor2,0);
}

void resetEngine() {
  Serial.println("reset e");
  analogWrite(leftMotor1,0);
  analogWrite(leftMotor2,0);
  analogWrite(rightMotor1,0);
  analogWrite(rightMotor2,0);
}

void threshold(int value)
{
  if(value>3500&& value<=4500)
  {
    moveForwards();
    delay(1000);
    resetEngine();
  }
  
  else if(value>4500&& value<=5500)\
  {
    moveForwards();
    delay(2000);
    resetEngine();
  }
  else if(value>=5500)
  {
   moveForwards();
    delay(3000);
    resetEngine();
  }
  else if(value<=3500)
  {
    moveForwards();
    delay(500);
    resetEngine();
  }
}

void movebot(int dir)
{
  if(dir==1)
  {
     turnLeft();
    Serial.println("Left Move Kia");
  }
  else if(dir==2)
  {
    turnRight();
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
                Serial.println("Value from App");
                Serial.println(val);
                Serial.println();
              }
              
              else
              {
                val=val+48;
                movebot(val);
                Serial.println("Val from Board");
                Serial.println(val);
                Serial.println(); 
              }

          }
}
