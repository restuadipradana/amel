#include <Password.h> 
#include <Keypad.h> 
#include <LiquidCrystal.h>
LiquidCrystal lcd(53,51,49,47,45,43);
String voice;
String msg;
Password password1 = Password(  "123" );
Password password2 = Password ( "456" );
Password password3 = Password ( "0" );

const int numRows = 4;                                   
const int numCols = 4;                                     
const char keymap[numRows][numCols] = { 
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
const int rowPins[numRows] = {23,25,27,29};               
const int colPins[numCols] = {31,33,35,37}; 

const int debounceTime = 20;
int ldr =A0;
int val=0;
int ledverifikasi =3;
int ledbuka =7;
int ledkunci=5;

int relayldr=6;
int relaybuzzer=9;
int relaysolenoid=8;

int sms_count=0;

void allon(){ 
}
void alloff(){
}

void setup(){
  Serial.begin(9600);
  Serial1.begin(9600); //sms
  Serial2.begin(9600); //bt
  lcd.begin(16, 2);
  
  pinMode(ledverifikasi, OUTPUT);
  pinMode(ledbuka, OUTPUT);
  pinMode(ledkunci, OUTPUT);
  pinMode(relaysolenoid, OUTPUT);
  pinMode(relayldr, OUTPUT);
  pinMode(relaybuzzer, OUTPUT);
  
  digitalWrite(relaysolenoid, HIGH);
  digitalWrite(relayldr, HIGH);
  digitalWrite(relaybuzzer, HIGH);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MASUKAN PASSWORD");
  lcd.setCursor(0,1);
  lcd.print("      ANDA      ");
  delay(200); 
  
  for (int row = 0; row < numRows; row++) {
    pinMode(rowPins[row],INPUT);                      
    digitalWrite(rowPins[row],HIGH);                 
  }
  for (int column = 0; column < numCols; column++) {
    pinMode(colPins[column],OUTPUT);                   
    digitalWrite(colPins[column],HIGH);               
  }
}

void loop(){

  char key = getKeys();
  if( key != 0) {                                      
   // Serial.print("Got key ");
      Serial.println(key);
      delay(10);
    
      switch (key) {
          case '#': 
          checkPassword1(); //ledbuka on, selenoid buka, ledkunci off
          checkPassword2(); //ledbuka on, selenoid buka, ledkunci off
          checkPassword3(); //ledbuka off, selenoid tutup, ledkunci on
          delay(10);
          password1.reset(); 
          password2.reset(); 
          password3.reset(); 
          delay(1); 
          break;   
          default: 
          password1.append(key); 
          password2.append(key); 
          password3.append(key); 
          delay(1);       
      }
  }
    ////////////////////////////////////////////////////////////////////
  while (Serial2.available()){ 
    delay(10); 
    char c = Serial2.read(); 
    if (c == '#') {break;} 
    voice += c; 
  }  
  if (voice.length() > 0) {
    Serial.println(voice); 
//-----------------------------------------------------------------------//    

  //----------AKTIFKAN SISTEM KEAMANAN----------// 
  if(voice == "SISTEM ON") {digitalWrite(relayldr, LOW);digitalWrite(ledbuka, HIGH);digitalWrite(ledkunci, LOW);} 
  else if(voice == "sistem on"){digitalWrite(relayldr, LOW);digitalWrite(ledbuka, HIGH);digitalWrite(ledkunci, LOW);} 
  else if(voice == "Sistem On"){digitalWrite(relayldr, LOW);digitalWrite(ledbuka, HIGH);digitalWrite(ledkunci, LOW);} 
   //----------MATIKAN SISTEM KEAMANAN----------// 
  else if(voice == "SYSTEM OF") {digitalWrite(relayldr, HIGH);digitalWrite(ledbuka, LOW);digitalWrite(ledkunci, HIGH);} 
  else if(voice == "System Of") {digitalWrite(relayldr, HIGH);digitalWrite(ledbuka, LOW);digitalWrite(ledkunci, HIGH);} 
  else if(voice == "system of") {digitalWrite(relayldr, HIGH);digitalWrite(ledbuka, LOW);digitalWrite(ledkunci, HIGH);} 

//-----------------------------------------------------------------------//  
  voice="";}
      ///////////////////////////////////////////////////////////////////////
      
       //###################################################
  
  val = analogRead(ldr);
  if(val>=100){ // 0=terang
    //Serial.println(val);
    delay(1000);
    digitalWrite(relaybuzzer, HIGH);//mati 
    sms_count=0; // Reactivating the SMS Alert Facility
  }else{
    digitalWrite(relaybuzzer, LOW); //nyala terang
    while(sms_count<2) //Number of SMS Alerts to be sent limited at 2
    {  
      KirimSMS(); // Function to send AT Commands to GSM module
    }
    //Serial.println(val);
  }
  delay(10);
  if (Serial1.available()>0){
    msg=Serial1.readString();
    Serial.print(msg);
    delay(10);
  }
  if(msg.indexOf("buka")>=0){ //sms buka 
    Solenoid();  
    msg = ""; 
  }

}
//#######################################

//###############################################
void checkPassword1(){
  if (password1.evaluate()){  
    digitalWrite(ledverifikasi, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  AKSES SUKSES  ");
    lcd.setCursor(0,1);
    lcd.print("  TERIMA KASIH  ");
    delay(2000); 
    digitalWrite(ledverifikasi, LOW);
    lcd.setCursor(0,0);
    lcd.print("MASUKAN PASSWORD");
    lcd.setCursor(0,1);
    lcd.print("      ANDA      ");
    delay(200); 
    Solenoid();
  }
}

void checkPassword2(){   
  if (password2.evaluate()){
    digitalWrite(ledverifikasi, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  AKSES SUKSES  ");
    lcd.setCursor(0,1);
    lcd.print("  TERIMA KASIH  ");
    delay(2000); 
    digitalWrite(ledverifikasi, LOW);
    lcd.setCursor(0,0);
    lcd.print("MASUKAN PASSWORD");
    lcd.setCursor(0,1);
    lcd.print("      ANDA      ");
    delay(200);
    digitalWrite(ledbuka, HIGH); 
    Solenoid();
  } 
}

void checkPassword3(){                   
  if (password3.evaluate()){
    digitalWrite(ledverifikasi, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  AKSES SUKSES  ");
    lcd.setCursor(0,1);
    lcd.print("  TERIMA KASIH  ");
    delay(2000); 
    digitalWrite(ledverifikasi, LOW);
    lcd.setCursor(0,0);
    lcd.print("MASUKAN PASSWORD");
    lcd.setCursor(0,1);
    lcd.print("      ANDA      ");
    delay(200);
    digitalWrite(ledbuka, LOW); //belum di edit
    digitalWrite(relaysolenoid, HIGH);
    digitalWrite(ledkunci, HIGH);
  }
}

void KirimSMS()
{
  Serial1.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  Serial1.println("AT+CMGS=\"+6287778515668\"\r"); // change to the phone number you using 
  delay(1000);
  Serial1.println("LOKER! TERBUKA");//the content of the message
  delay(200);
  Serial1.println((char)26);//the stopping character
  delay(1000);
  sms_count++;
}

void Solenoid()
{
  digitalWrite(ledbuka, HIGH); 
  digitalWrite(ledkunci, LOW);
  digitalWrite(relaysolenoid, LOW);
  delay(5000);
  digitalWrite(relaysolenoid, HIGH);
  digitalWrite(ledbuka, LOW); 
  digitalWrite(ledkunci, HIGH);
}

char getKeys() {
  char key = 0;                                          
  for(int column = 0; column < numCols; column++) {
    digitalWrite(colPins[column],LOW);                 
    for(int row = 0; row < numRows; row++) {           
      if(digitalRead(rowPins[row]) == LOW) {         
        delay(debounceTime);                       
        while(digitalRead(rowPins[row]) == LOW) ; 
        key = keymap[row][column];                 
      }
    }
    digitalWrite(colPins[column],HIGH);                
  }
  return key;                                            
}
