
#include <LedControl.h>
#include<EEPROM.h>
#include<string.h>
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"

SMSGSM sms;
char sms_text[100];
char phone_number[20];
boolean started=false;
char sms_position;

const int numDevices1 = 5;
const int numDevices2 = 5;
const int numDevices3 = 5;
const int numDevices4 = 5;

const long scrollDelay = 5;

unsigned long bufferLong [14] = {0};
unsigned long bufferLong2 [7] = {0};
unsigned long bufferLong11 [14] = {0};
unsigned long bufferLong12 [7] = {0};

LedControl lc1=LedControl(12,11,10,numDevices1);//12=1,11=13,10=12
LedControl lc2=LedControl(5,4,3,numDevices2); //5=1,4=13,3=12
LedControl lc3=LedControl(A0,A1,A2,numDevices3);
LedControl lc4=LedControl(A3,A4,A5,numDevices4);

int flag=1; //1 for scrolling, 0 for static

unsigned char text1[] ={"<1s1>  Ogggaa boogaa boogaa "};
unsigned char text2[]={"<1s2>Send SMS  "};
unsigned char text3[]={"<1s3>Send SMS "};


const unsigned char font5x7 [] PROGMEM = {
    B00000000,  //Space (Char 0x20)
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    3,//this number gives the empty space column amount between the characters

    B10000000,  //!
    B10000000,
    B10000000,
    B10000000,
    B00000000,
    B00000000,
    B10000000,
    2,

    B10100000,  //"
    B10100000,
    B10100000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    4,

    B01010000,  //#
    B01010000,
    B11111000,
    B01010000,
    B11111000,
    B01010000,
    B01010000,
    6,

    B00100000,  //$
    B01111000,
    B10100000,
    B01110000,
    B00101000,
    B11110000,
    B00100000,
    6,

    B11000000,  //%
    B11001000,
    B00010000,
    B00100000,
    B01000000,
    B10011000,
    B00011000,
    6,

    B01100000,  //&
    B10010000,
    B10100000,
    B01000000,
    B10101000,
    B10010000,
    B01101000,
    6,

    B11000000,  //'
    B01000000,
    B10000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    3,

    B00100000,  //(
    B01000000,
    B10000000,
    B10000000,
    B10000000,
    B01000000,
    B00100000,
    4,

    B10000000,  //)
    B01000000,
    B00100000,
    B00100000,
    B00100000,
    B01000000,
    B10000000,
    4,

    B00000000,  //*
    B00100000,
    B10101000,
    B01110000,
    B10101000,
    B00100000,
    B00000000,
    6,

    B00000000,  //+
    B00100000,
    B00100000,
    B11111000,
    B00100000,
    B00100000,
    B00000000,
    6,

    B00000000,  //,
    B00000000,
    B00000000,
    B00000000,
    B11000000,
    B01000000,
    B10000000,
    3,

    B00000000,  //-
    B00000000,
    B00000000,
    B11111000,
    B00000000,
    B00000000,
    B00000000,
    6,

    B00000000,  //.
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11000000,
    B11000000,
    3,

    B00000000,  ///
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B10000000,
    B00000000,
    6,

    B01110000,  //0
    B10001000,
    B10011000,
    B10101000,
    B11001000,
    B10001000,
    B01110000,
    6,

    B01000000,  //1
    B11000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B11100000,
    4,

    B01110000,  //2
    B10001000,
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B11111000,
    6,

    B11111000,  //3
    B00010000,
    B00100000,
    B00010000,
    B00001000,
    B10001000,
    B01110000,
    6,

    B00010000,  //4
    B00110000,
    B01010000,
    B10010000,
    B11111000,
    B00010000,
    B00010000,
    6,

    B11111000,  //5
    B10000000,
    B11110000,
    B00001000,
    B00001000,
    B10001000,
    B01110000,
    6,

    B00110000,  //6
    B01000000,
    B10000000,
    B11110000,
    B10001000,
    B10001000,
    B01110000,
    6,

    B11111000,  //7
    B10001000,
    B00001000,
    B00010000,
    B00100000,
    B00100000,
    B00100000,
    6,

    B01110000,  //8
    B10001000,
    B10001000,
    B01110000,
    B10001000,
    B10001000,
    B01110000,
    6,

    B01110000,  //9
    B10001000,
    B10001000,
    B01111000,
    B00001000,
    B00010000,
    B01100000,
    6,

    B00000000,  //:
    B11000000,
    B11000000,
    B00000000,
    B11000000,
    B11000000,
    B00000000,
    3,

    B00000000,  //;
    B11000000,
    B11000000,
    B00000000,
    B11000000,
    B01000000,
    B10000000,
    3,

    B00010000,  //<
    B00100000,
    B01000000,
    B10000000,
    B01000000,
    B00100000,
    B00010000,
    5,

    B00000000,  //=
    B00000000,
    B11111000,
    B00000000,
    B11111000,
    B00000000,
    B00000000,
    6,

    B10000000,  //>
    B01000000,
    B00100000,
    B00010000,
    B00100000,
    B01000000,
    B10000000,
    5,

    B01110000,  //?
    B10001000,
    B00001000,
    B00010000,
    B00100000,
    B00000000,
    B00100000,
    6,

    B01110000,  //@
    B10001000,
    B00001000,
    B01101000,
    B10101000,
    B10101000,
    B01110000,
    6,

    B01110000,  //A
    B10001000,
    B10001000,
    B10001000,
    B11111000,
    B10001000,
    B10001000,
    6,

    B11110000,  //B
    B10001000,
    B10001000,
    B11110000,
    B10001000,
    B10001000,
    B11110000,
    6,

    B01110000,  //C
    B10001000,
    B10000000,
    B10000000,
    B10000000,
    B10001000,
    B01110000,
    6,

    B11100000,  //D
    B10010000,
    B10001000,
    B10001000,
    B10001000,
    B10010000,
    B11100000,
    6,

    B11111000,  //E
    B10000000,
    B10000000,
    B11110000,
    B10000000,
    B10000000,
    B11111000,
    6,

    B11111000,  //F
    B10000000,
    B10000000,
    B11110000,
    B10000000,
    B10000000,
    B10000000,
    6,

    B01110000,  //G
    B10001000,
    B10000000,
    B10111000,
    B10001000,
    B10001000,
    B01111000,
    6,

    B10001000,  //H
    B10001000,
    B10001000,
    B11111000,
    B10001000,
    B10001000,
    B10001000,
    6,

    B11100000,  //I
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B11100000,
    4,

    B00111000,  //J
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B10010000,
    B01100000,
    6,

    B10001000,  //K
    B10010000,
    B10100000,
    B11000000,
    B10100000,
    B10010000,
    B10001000,
    6,

    B10000000,  //L
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B11111000,
    6,

    B10001000,  //M
    B11011000,
    B10101000,
    B10101000,
    B10001000,
    B10001000,
    B10001000,
    6,

    B10001000,  //N
    B10001000,
    B11001000,
    B10101000,
    B10011000,
    B10001000,
    B10001000,
    6,

    B01110000,  //O
    B10001000,
    B10001000,
    B10001000,
    B10001000,
    B10001000,
    B01110000,
    6,

    B11110000,  //P
    B10001000,
    B10001000,
    B11110000,
    B10000000,
    B10000000,
    B10000000,
    6,

    B01110000,  //Q
    B10001000,
    B10001000,
    B10001000,
    B10101000,
    B10010000,
    B01101000,
    6,

    B11110000,  //R
    B10001000,
    B10001000,
    B11110000,
    B10100000,
    B10010000,
    B10001000,
    6,

    B01111000,  //S
    B10000000,
    B10000000,
    B01110000,
    B00001000,
    B00001000,
    B11110000,
    6,

    B11111000,  //T
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    6,

    B10001000,  //U
    B10001000,
    B10001000,
    B10001000,
    B10001000,
    B10001000,
    B01110000,
    6,

    B10001000,  //V
    B10001000,
    B10001000,
    B10001000,
    B10001000,
    B01010000,
    B00100000,
    6,

    B10001000,  //W
    B10001000,
    B10001000,
    B10101000,
    B10101000,
    B10101000,
    B01010000,
    6,

    B10001000,  //X
    B10001000,
    B01010000,
    B00100000,
    B01010000,
    B10001000,
    B10001000,
    6,

    B10001000,  //Y
    B10001000,
    B10001000,
    B01010000,
    B00100000,
    B00100000,
    B00100000,
    6,

    B11111000,  //Z
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B10000000,
    B11111000,
    6,

    B11100000,  //[
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B11100000,
    4,

    B00000000,  //(Backward Slash)
    B10000000,
    B01000000,
    B00100000,
    B00010000,
    B00001000,
    B00000000,
    6,

    B11100000,  //]
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B11100000,
    4,

    B00100000,  //^
    B01010000,
    B10001000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    6,

    B00000000,  //_
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111000,
    6,

    B10000000,  //`
    B01000000,
    B00100000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    4,

    B00000000,  //a
    B00000000,
    B01110000,
    B00001000,
    B01111000,
    B10001000,
    B01111000,
    6,

    B10000000,  //b
    B10000000,
    B10110000,
    B11001000,
    B10001000,
    B10001000,
    B11110000,
    6,

    B00000000,  //c
    B00000000,
    B01110000,
    B10001000,
    B10000000,
    B10001000,
    B01110000,
    6,

    B00001000,  //d
    B00001000,
    B01101000,
    B10011000,
    B10001000,
    B10001000,
    B01111000,
    6,

    B00000000,  //e
    B00000000,
    B01110000,
    B10001000,
    B11111000,
    B10000000,
    B01110000,
    6,

    B00110000,  //f
    B01001000,
    B01000000,
    B11100000,
    B01000000,
    B01000000,
    B01000000,
    6,

    B00000000,  //g
    B01111000,
    B10001000,
    B10001000,
    B01111000,
    B00001000,
    B01110000,
    6,

    B10000000,  //h
    B10000000,
    B10110000,
    B11001000,
    B10001000,
    B10001000,
    B10001000,
    6,

    B01000000,  //i
    B00000000,
    B11000000,
    B01000000,
    B01000000,
    B01000000,
    B11100000,
    4,

    B00010000,  //j
    B00000000,
    B00110000,
    B00010000,
    B00010000,
    B10010000,
    B01100000,
    5,

    B10000000,  //k
    B10000000,
    B10010000,
    B10100000,
    B11000000,
    B10100000,
    B10010000,
    5,

    B11000000,  //l
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B11100000,
    4,

    B00000000,  //m
    B00000000,
    B11010000,
    B10101000,
    B10101000,
    B10001000,
    B10001000,
    6,

    B00000000,  //n
    B00000000,
    B10110000,
    B11001000,
    B10001000,
    B10001000,
    B10001000,
    6,

    B00000000,  //o
    B00000000,
    B01110000,
    B10001000,
    B10001000,
    B10001000,
    B01110000,
    6,

    B00000000,  //p
    B00000000,
    B11110000,
    B10001000,
    B11110000,
    B10000000,
    B10000000,
    6,

    B00000000,  //q
    B00000000,
    B01101000,
    B10011000,
    B01111000,
    B00001000,
    B00001000,
    6,

    B00000000,  //r
    B00000000,
    B10110000,
    B11001000,
    B10000000,
    B10000000,
    B10000000,
    6,

    B00000000,  //s
    B00000000,
    B01110000,
    B10000000,
    B01110000,
    B00001000,
    B11110000,
    6,

    B01000000,  //t
    B01000000,
    B11100000,
    B01000000,
    B01000000,
    B01001000,
    B00110000,
    6,

    B00000000,  //u
    B00000000,
    B10001000,
    B10001000,
    B10001000,
    B10011000,
    B01101000,
    6,

    B00000000,  //v
    B00000000,
    B10001000,
    B10001000,
    B10001000,
    B01010000,
    B00100000,
    6,

    B00000000,  //w
    B00000000,
    B10001000,
    B10101000,
    B10101000,
    B10101000,
    B01010000,
    6,

    B00000000,  //x
    B00000000,
    B10001000,
    B01010000,
    B00100000,
    B01010000,
    B10001000,
    6,

    B00000000,  //y
    B00000000,
    B10001000,
    B10001000,
    B01111000,
    B00001000,
    B01110000,
    6,

    B00000000,  //z
    B00000000,
    B11111000,
    B00010000,
    B00100000,
    B01000000,
    B11111000,
    6,

    B00100000,  //{
    B01000000,
    B01000000,
    B10000000,
    B01000000,
    B01000000,
    B00100000,
    4,

    B10000000,  //|
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    2,

    B10000000,  //}
    B01000000,
    B01000000,
    B00100000,
    B01000000,
    B01000000,
    B10000000,
    4,

    B00000000,  //~
    B00000000,
    B00000000,
    B01101000,
    B10010000,
    B00000000,
    B00000000,
    6,

    B01100000,  // (Char 0x7F)
    B10010000,
    B10010000,
    B01100000,
    B00000000,
    B00000000,
    B00000000,
    5,

    B00000000,  // smiley
    B01100000,
    B01100110,
    B00000000,
    B10000001,
    B01100110,
    B00011000,
    5
};

void save_as_priority(unsigned char * message,int sizexx){
  if(message[3]=='1'){
    for(int i=0;i<sizexx;i++){
      EEPROM.update(i,message[i]);
      text1[i]=message[i];
    }
    //flag=checkKerning(sizexx);
  }
  else if(message[3]='2'){
    for(int i=100;i<100+sizexx;i++){
      EEPROM.update(i,message[i-100]);
      text2[i-100]=message[i-100];
    }
  }
  else if(message[3]='3'){
    for(int i=200;i<200+sizexx;i++){
      EEPROM.update(i,message[i-200]);
      text3[i-200]=message[i-200];
    }
  }

}

void loop(){
  if(started)
  {
    sms_position=sms.IsSMSPresent(SMS_UNREAD);
    if (sms_position)
    {
      sms.GetSMS(sms_position,phone_number,sms_text,100);
      if(sms_text[3]=='1'){
        strcpy(text1,sms_text);
        save_as_priority(text1,sizeof(text1)/sizeof(text1[0]));
      }
      else if (sms_text[3]=='2'){
        strcpy(text2,sms_text);
        save_as_priority(text2,sizeof(text2)/sizeof(text2[0]));
      }
      else if (sms_text[3]=='3'){
        strcpy(text3,sms_text);
        save_as_priority(text3,sizeof(text3)/sizeof(text3[0]));
      }
    }
  }
  display_message(sizeof(text1)/sizeof(text1[0]),int(text1[3])-'0',text1[3]);
  display_message(sizeof(text2)/sizeof(text2[0]),int(text2[3])-'0',text2[3]);
  display_message(sizeof(text3)/sizeof(text3[0]),int(text3[3])-'0',text3[3]);
}


void display_message(int sizexx,int count,char prio)
{
    scrollMessage(sizexx,count,prio);
}

void setup(){
  Serial.begin(9600);
  if(gsm.begin(4800)){
    started=true;
  }
  for (int x=0; x<numDevices1; x++){
    lc1.shutdown(x,false);     
    lc1.setIntensity(x,10);    
    lc1.clearDisplay(x);        
    }
  for (int x=0; x<numDevices2;x++){
    lc2.shutdown(x,false);     
    lc2.setIntensity(x,10);      
    lc2.clearDisplay(x);       
    }
  for (int x=0; x<numDevices3;x++){
    lc3.shutdown(x,false);       
    lc3.setIntensity(x,10);      
    lc3.clearDisplay(x);     
    }
  for (int x=0; x<numDevices4;x++){
    lc4.shutdown(x,false);       
    lc4.setIntensity(x,10);       
    lc4.clearDisplay(x);         
    }

   save_as_priority(text1,sizeof(text1)/sizeof(text1[0]));
   save_as_priority(text2,sizeof(text2)/sizeof(text2[0]));
   save_as_priority(text3,sizeof(text3)/sizeof(text3[0]));
}


void scrollMessage(int sizexx,int count,char prio) {
   int counter=(count-1)*100;
    int myChar=0;
    for(int i=counter+5;i<counter+sizexx;i++){
      myChar=EEPROM.read(i);
      if(myChar!=0){
        loadBufferLong(myChar,prio);
      }
      else if(myChar==0){
        break;
      }
    }
    if(prio=='1'){
     printBufferLong2();
    }
}

void loadBufferLong(int ascii,char prio){
    if (ascii >= 0x20 && ascii <=0x7f){
      if(prio=='1'){
        for (int a=0;a<7;a++){
            unsigned long c = pgm_read_byte_near(font5x7 + ((ascii - 0x20) * 8) + a);
            unsigned long x = bufferLong11 [a*2];
            x = x | c;
            bufferLong11 [a*2] = x;
        }
        byte count = pgm_read_byte_near(font5x7 +((ascii - 0x20) * 8) + 7);
        for (byte x=0; x<count;x++){
            rotateBufferLong2();
        }
    }
    else{
        for (int a=0;a<7;a++){
            unsigned long c = pgm_read_byte_near(font5x7 + ((ascii - 0x20) * 8) + a);
            unsigned long x = bufferLong [a*2];
            x = x | c;
            bufferLong [a*2] = x;
        }
        byte count = pgm_read_byte_near(font5x7 +((ascii - 0x20) * 8) + 7);
        for (byte x=0; x<count;x++){
            rotateBufferLong();
            printBufferLong();
            delay(scrollDelay);
        }
    }
    
    }
}


void rotateBufferLong(){
    for (int a=0;a<7;a++){
        unsigned long x = bufferLong [a*2];
        byte b = bitRead(x,31);
        x = x<<1;
        bufferLong [a*2] = x;
        x = bufferLong [a*2+1];
        x = x<<1;
        bitWrite(x,0,b);
        bufferLong [a*2+1] = x;
        x = bufferLong [a*2+1];
        b = bitRead(x,31);
        x = bufferLong2 [a];
        x = x<<1;
        bitWrite(x,0,b);
        bufferLong2 [a]=x;
    }
}

void rotateBufferLong2(){
    for (int a=0;a<7;a++){
        unsigned long x = bufferLong11 [a*2];
        byte b = bitRead(x,31);
        x = x<<1;
        bufferLong11 [a*2] = x;
        x = bufferLong11 [a*2+1];
        x = x<<1;
        bitWrite(x,0,b);
        bufferLong11 [a*2+1] = x;
        x = bufferLong11 [a*2+1];
        b = bitRead(x,31);
        x = bufferLong12 [a];
        x = x<<1;
        bitWrite(x,0,b);
        bufferLong12 [a]=x;
    }
}

void printBufferLong(){
  for (int a=0;a<7;a++){
    unsigned long x = bufferLong [a*2+1];
    byte y = x;
    lc1.setRow(3,a,y);
    y = (x>>8);
    lc1.setRow(4,a,y);
    y = (x>>16);
    lc2.setRow(0,a,y);
    y = (x>>24);
    lc2.setRow(1,a,y);
    x = bufferLong2 [a];
    y = x;
    lc2.setRow(2,a,y);
    y = (x>>8);
    lc2.setRow(3,a,y);
    y = (x>>16);
    lc2.setRow(4,a,y);
    x = bufferLong [a*2];
    y = (x>>24);
    lc1.setRow(2,a,y);
    y = (x>>16);
    lc1.setRow(1,a,y);
    y = (x>>8);
    lc1.setRow(0,a,y);
  }
}

void printBufferLong2(){
  for (int a=0;a<7;a++){
    unsigned long x = bufferLong11 [a*2+1];
    byte y = x;
    lc3.setRow(3,a,y);
    y = (x>>8);
    lc3.setRow(4,a,y);
    y = (x>>16);
    lc4.setRow(0,a,y);
    y = (x>>24);
    lc4.setRow(1,a,y);
    x = bufferLong12 [a];
    y = x;
    lc4.setRow(2,a,y);
    y = (x>>8);
    lc4.setRow(3,a,y);
    y = (x>>16);
    lc4.setRow(4,a,y);
    x = bufferLong11 [a*2];
    y = (x>>24);
    lc3.setRow(2,a,y);
    y = (x>>16);
    lc3.setRow(1,a,y);
    y = (x>>8);
    lc3.setRow(0,a,y);
  }
}

int checkKerning(int sizexx){
  int myChar=0;
  int count=0;
  for(int i=5;i<sizexx;i++){
    myChar=EEPROM.read(i);
    count = count + pgm_read_byte_near(font5x7 +((myChar - 0x20) * 8) + 7);
  }
  if(count<=155){
    return 1;    //static
  }
  else{
    return 0;
  } 
}
