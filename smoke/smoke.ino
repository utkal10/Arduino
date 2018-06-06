#include<MQ2.h>
int pin=A5;
float* value=0;
float lpg,co,smoke;

MQ2 gas(pin);

void setup(){
  Serial.begin(9600);
  gas.begin();
}

void loop(){
  value=gas.read(false);

  lpg=gas.readLPG();
  Serial.println("LPG:");
  Serial.println(lpg);
  co=gas.readCO();
  Serial.println("CO:");
  Serial.println(co);
  smoke=gas.readSmoke();
  Serial.println("Smoke:");
  Serial.println(smoke);

  delay(200);
}

