#include<binary.h>
#include<LedControl.h>



void setup() {
  Serial.begin(9600);

}

void loop() {
  unsigned long x=71616;
  unsigned long c=B11111000;
  x=x>>8;
  Serial.println(x,BIN);
  delay(3000);
  
  
}
