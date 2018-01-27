#include <Password.h> 
#include <Keypad.h> 
#include <LiquidCrystal.h>
LiquidCrystal lcd(53,51,49,47,45,43);
String voice;
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
int ledbuka =4;
int ledkunci=5;

int relayldr=6;
int relaybuzzer=12;
int relaysolenoid=13;


void allon(){ 
}
void alloff(){
}
void setup(){
  Serial.begin(9600);
 lcd.begin(16, 2);

 int ledverifikasi =13;
int ledbuka =12;
int ledkunci=11;
int solenoid=10;

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

  char key = getKey();
    if( key != 0) {                                      
     // Serial.print("Got key ");
        Serial.println(key);
        delay(10);
      
        switch (key) {
            case '#': 
            checkPassword1(); 
            checkPassword2(); 
            checkPassword3();
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
   while (Serial.available()){ 
  delay(10); 
  char c = Serial.read(); 
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
if(val>=100){
 // Serial.println(val);
  delay(1000);
    digitalWrite(relaybuzzer, HIGH);
    
}else{
    digitalWrite(relaybuzzer, LOW);
   //   Serial.println(val);
  }
  delay(1000);
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
        digitalWrite(ledbuka, HIGH);
    digitalWrite(relaysolenoid, LOW);
    digitalWrite(ledkunci, LOW);
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
    digitalWrite(relaysolenoid, LOW);
    digitalWrite(ledkunci, LOW);
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
          digitalWrite(ledbuka, LOW);
    digitalWrite(relaysolenoid, HIGH);
    digitalWrite(ledkunci, HIGH);
      }
      

   }
char getKey() {
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





