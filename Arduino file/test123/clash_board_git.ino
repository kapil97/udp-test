#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

const char* ssid = "kamli"; //Enter your wifi network SSID
const char* password = "87654321"; //Enter your wifi network password

const int SERVER_PORT = 1111;
const int BAUD_RATE = 115200;
byte packetBuffer[512];

WiFiUDP Udp;
IPAddress ip;

void connectWifi() {
  Serial.println();
  Serial.println();
  Serial.print("Connecting to WIFI network");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 Serial.println("WiFi connected");
  Udp.begin(SERVER_PORT);
  ip = WiFi.localIP();
  Serial.println(ip);
}



void setup() {
pinMode(2,INPUT_PULLUP); //left
pinMode(3,INPUT_PULLUP);//right
//pinMode(4,INPUT_PULLUP);//down
pinMode(5,INPUT_PULLUP);//up
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
connectWifi();
Serial.begin(9600);

}

void loop() {

  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
  if(digitalRead(2)==LOW){
    Serial.println("l"); 
    digitalWrite(10,LOW);
  }
  else if(digitalRead(3)==LOW){
    Serial.println("r");
    digitalWrite(11,LOW);
  }
   /*else if(digitalRead(4)==LOW){
    digitalWrite(12,LOW);
  }*/
   else if(digitalRead(5)==LOW){
    Serial.println("u");
    digitalWrite(13,LOW);  
  }else
  {Serial.println("OFF");}
 
 
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
    
  delay(30);
  // put your main code here, to run repeatedly:

}
