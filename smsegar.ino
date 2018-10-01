#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 8);
String msg;
int relay = 5;

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  pinMode(relay, OUTPUT);
  digitalWrite(relay,HIGH);
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
    digitalWrite(relay,LOW);
    KirimHidup();
    Serial.println("LAMPU ON");  
    msg = ""; }
  if(msg.indexOf("OFF")>=0){
    Serial.println("Relay set to OFF");  
    digitalWrite(relay,HIGH);
    KirimMati();
    Serial.println("LAMPU OFF");
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

void KirimHidup(){
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"089637283042\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("LAMPU HIDUP");// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
 
void KirimMati(){
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"089637283042\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("LAMPU MATI");// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
