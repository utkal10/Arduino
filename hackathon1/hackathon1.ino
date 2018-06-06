#include<MQ2.h>
#include<string.h>
#include<ctype.h>
#include<SoftwareSerial.h>

SoftwareSerial mySerial(9,10);

int RXPin=15;
int TXPin=14;
int smokePin=A5;
float* smokeValue=0;
float smoke;
int smokeFlag=0;
MQ2 gas(smokePin);
char GPSData[60]="";
float longitude=0;
float latitude=0;
int byteGPS=-1;
char GPR[7]="$GPRMC";
int cont=0;
int bien=0;
int conta=0;
int indices[13];

int readSmoke(){
  smoke=gas.readSmoke();
  if (smoke>=3){
    return 1;
  }
  else{
    return 0;
  }
  delay(1000);
}

void getGPS(){
  byteGPS=Serial.read();
  if (byteGPS==-1){
    delay(100);
  }else{
    GPSData[conta]=byteGPS;
    conta++;
    Serial.write(byteGPS);
    if (byteGPS==13){
      cont=0;
      bien=0;
      for (int i=1;i<7;i++){
        if (GPSData[i]==GPR[i-1]){
          bien++;
        }
      }
      if(bien==6){
        for (int i=0;i<60;i++){
          if(GPSData[i]==','){
            indices[cont]=i;
            cont++;
          }
          if (GPSData[i]=='*'){
            indices[12]=i;
            cont++;
          }
        }
        latitude=27.600610;
        longitude=85.42923;
      
      }
      conta=0;
      for (int i=0;i<60;i++){
        GPSData[i]=' ';
      }
    }
  }
}

void sendSMS(float lati,float longi){
  mySerial.println("AT+CMGF=1");   
  delay(1000);  
  mySerial.println("AT+CMGS=\"+9779809482020\"\r"); 
  delay(1000);
  mySerial.println(lati);
  delay(1000);
  mySerial.println(longi);
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  
}

void getGPS2(){
  latitude=27.600610;
  longitude=85.42923;
}

void setup(){
  int i=0;
  Serial.begin(9600);
  mySerial.begin(9600);
  gas.begin();
  for(i=0;i<60;i++){
    GPSData[i]=' ';
  }
}

void loop(){
  getGPS2();
  smokeFlag=readSmoke();
  if (smokeFlag==1){
    if (mySerial.available()>0){
    sendSMS(longitude,latitude);}
  }
}

