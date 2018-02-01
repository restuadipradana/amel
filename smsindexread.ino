/*
9-RX
10-TX
*/


#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
String msg;


void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)

}

void loop()
{  
if (mySerial.available()>0)
  {
    msg=mySerial.readString();
    Serial.print(msg);
    delay(10);
  }
  if(msg.indexOf("ON")>=0){
    Serial.println("Relay set to ON");  
    msg = ""; }
  if(msg.indexOf("OFF")>=0){
    Serial.println("Relay set to OFF");  
    msg = ""; }
}


void ReceiveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(1000);
  if (mySerial.available()>0)
  {
    msg=mySerial.read();
    Serial.print(msg);
  }
}

