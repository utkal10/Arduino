#include <SoftwareSerial.h>
SoftwareSerial SIM900(6,7);
 
void setup()
{
  SIM900.begin(19200);
  SIM900power(); 
  delay(20000);  // give time to log on to network.
}
 
void SIM900power()
// software equivalent of pressing the GSM shield "power" button
{
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(5000);
}
 
void sendSMS()
{
  SIM900.print("AT+CMGF=1\r");                         // AT command to send SMS message
  delay(100);
  SIM900.println("AT + CMGS = \"+9779845906888\"");     // recipient's mobile number, in international format
  delay(100);
  SIM900.println("Hello ^^");        // message to send
  delay(100);
  SIM900.println((char)26);                       // End AT command with a ^Z, ASCII code 26
  delay(100);
  SIM900.println();
  delay(5000);                                     // give module time to send SMS
  SIM900power();                                   // turn off module
}
 
void loop()
{
  sendSMS();
  do {} while (1);
}
