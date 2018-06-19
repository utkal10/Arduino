#include <SoftwareSerial.h>

SoftwareSerial GPRS(6,7);

unsigned char buffer[64];  // buffer array for data receive over serial port
int count=0;               // counter for buffer array

void setup()
{
  GPRS.begin(2400);
  Serial.begin(9600);
}

void loop()
{
  if (GPRS.available())
  {
    while(GPRS.available())
    {
      buffer[count++]=GPRS.read();
      if(count == 64)break;
    }
    Serial.write(buffer,count);
    clearBufferArray();
    count = 0;
  }
  if (Serial.available())
    GPRS.write(Serial.read());
}

void clearBufferArray()
{
  for (int i=0; i<count;i++)
  {
    buffer[i]=NULL;
  }
}
