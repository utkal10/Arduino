unsigned char text1[]={"<ss1>melon  "};

void setup(){
  Serial.begin(9600);
}

void loop(){
  int x=int(text1[3])-'0';
  Serial.println(x+3);
  delay(2000);
  
}
