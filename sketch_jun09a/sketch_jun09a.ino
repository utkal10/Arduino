
#include<string.h>
#include<ctype.h>
#include<SoftwareSerial.h>

SoftwareSerial mySerial(6,7);
int flag=0;

void sendSMS(){
  mySerial.println("AT+CMGF=1");   
  delay(1000);  
  mySerial.println("AT+CMGS=\"+9779845906888\"\r"); 
  delay(1000);
  mySerial.println("hello");
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


void setup(){
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop(){
  if(flag==0){
    sendSMS();
    flag=1;
  }
}
