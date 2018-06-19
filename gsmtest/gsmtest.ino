#include<SoftwareSerial.h>
SoftwareSerial gsm(6,7);
unsigned char text[]={};
int count=0;
void setup(){
  gsm.begin(9600);
  Serial.begin(9600);
  delay(1000);
  gsm.println("AT+CMGF=1");
  delay(1000);
  delay(1000);
}

void loop(){
  char c;
  if(gsm.available()){
    while(c=gsm.read()){
      Serial.print(c);
      text[count++]=c;
    }
  }
}
