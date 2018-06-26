#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
SMSGSM sms;

char smsbuffer[160];
char sms_text[100];
char phone_number[20];
boolean started=false;
char sms_position;
char text1[]={"Utkal"};


void setup()
{
  Serial.begin(9600);
  if(gsm.begin(4800)){
    started=true;
  }
}

void loop(){
  if(started)
  {
    sms_position=sms.IsSMSPresent(SMS_UNREAD);
    if (sms_position)
    {
      sms.GetSMS(sms_position,phone_number,sms_text,100);
      strcpy(text1,sms_text);
      Serial.println("inside");
    }
    Serial.println(text1);
  }
}
