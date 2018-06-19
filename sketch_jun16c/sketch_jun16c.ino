#include <SoftwareSerial.h>
#include <string.h>

char incoming_char = 0;
SoftwareSerial cell(7,6);

void setup()
{
  Serial.begin(9600);
  cell.begin(9600);
 
  Serial.print("Starting modem communication...");
  delay(12000);
  Serial.print("OK\nIntroduce your AT commands:\n");
}

void loop()
{
  if(cell.available() > 0)
  {
    incoming_char=cell.read();
    if((incoming_char >= ' ') && (incoming_char <= 'z'))
      Serial.print(incoming_char);
    else
    {
      Serial.print("%");
      Serial.print((int)incoming_char);
      Serial.print("%");
      if(incoming_char==10)
        Serial.println();
    }
  }

  if(Serial.available() > 0)
  {
    incoming_char = Serial.read();
    cell.print(incoming_char);
  }
}
