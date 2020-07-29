#include <ESP8266WiFi.h>

String apiWritekey = "NVQ4PXWPC0P5M06X"; 
const char* ssid = "remi343"; //  wifi SSID name
const char* password = "password30" ;// wifi pasword
const int ledPin = 2;
const int ldrPin = A0;

 
const char* server = "api.thingspeak.com";

WiFiClient client;
 
void setup() {
   Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
 
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println();
}
 
void loop() {
  int ldrStatus = analogRead(ldrPin);

  if (ldrStatus < 910){
    digitalWrite(ledPin, LOW);
    }
    else{
      digitalWrite(ledPin, HIGH);
      }

delay(500);
  
  if (client.connect(server,80))
  {  
    String lData = apiWritekey;
           lData +="&field1=";
           lData += String(ldrStatus);
           lData += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(lData.length());
     client.print("\n\n");  // the 2 carriage returns indicate closing of Header fields & starting of data
     client.print(lData);
     Serial.print("the status is: ");
     Serial.print(ldrStatus);
     Serial.println(" uploaded to Thingspeak server....");
   
  }
   int p;
     if (ldrStatus < 920){
     p = 0;
    }
    else{
      p = 1;
      }
  if (client.connect(server,80))
  {  
    String pData = apiWritekey;
           pData +="&field2=";
           pData += String(p);
           pData += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(pData.length());
     client.print("\n\n");  // the 2 carriage returns indicate closing of Header fields & starting of data
     client.print(pData);
 
     Serial.print("the status is: ");
     Serial.print(p);
     Serial.println(" uploaded to Thingspeak server....");
  }
  client.stop();
 
  Serial.println("Waiting to upload next reading...");
  Serial.println();
  // thingspeak needs minimum 15 sec delay between updates
  
}
