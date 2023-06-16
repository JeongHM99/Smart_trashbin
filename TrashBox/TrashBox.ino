#include <Servo.h> 
#include <HX711.h>
#include <SoftwareSerial.h>

#define calibration_factor0 -502600.0
#define calibration_factor1 -834400.0
#define calibration_factor2 -728000.0
#define calibration_factor3 -748300.0
#define DOUT0 5
#define DOUT1 7
#define DOUT2 9
#define DOUT3 A1
#define CLK0 4
#define CLK1 6
#define CLK2 8
#define CLK3 A0

SoftwareSerial mySerial(2,3); //TX,RX
String ssid = "Haemin";
String PASSWORD = "20183034";
String host = "gamhs44.ivyro.net"; 

HX711 scale0(DOUT0, CLK0);
HX711 scale1(DOUT1, CLK1);
HX711 scale2(DOUT2, CLK2);
HX711 scale3(DOUT3, CLK3);
Servo servo1; Servo servo2; Servo servo3; Servo servo4;

char incomingByte; 
int value = 0;
float weight0;
float weight1;
float weight2;
float weight3;
unsigned long time;

void connectWifi(){
  String join ="AT+CWJAP=\""+ssid+"\",\""+PASSWORD+"\"";
      
  mySerial.println(join);
  delay(10000);
  if(mySerial.find("WIFI GOT IP"))
  {
    Serial.print("WIFI connect\n");
  }else  
  {
   Serial.println("connect timeout\n");
  }
}

void httpclient(String char_input, String temp){
  mySerial.println("AT+CIPSTART=\"TCP\",\""+host+"\",80");
  delay(300);
  if(Serial.find("ERROR")) return;
  
  String url=char_input;
  String cmd=temp+url+" HTTP/1.0\r\n\r\n";
  mySerial.print("AT+CIPSEND=");
  mySerial.println(cmd.length());
  if(mySerial.find(">"))
  {
    Serial.print(">");
  }else
  {
    mySerial.println("AT+CIPCLOSE");
    Serial.println("connect timeout");
    delay(1000);
    return;
  }
       
  mySerial.println(cmd);
  Serial.println(cmd);
  delay(100);
  if(Serial.find("ERROR")) return;
  mySerial.println("AT+CIPCLOSE");
  delay(100);
}  

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600); // 와이파이 모듈 시작
  
  delay(700);
  
  scale0.set_scale(calibration_factor0);
  scale1.set_scale(calibration_factor1);
  scale2.set_scale(calibration_factor2);  
  scale3.set_scale(calibration_factor3);  
  scale0.tare();
  scale1.tare();
  scale2.tare();
  scale3.tare();

  connectWifi();
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == '0') {
      servo1.attach(10);
      weight0 = scale0.get_units();
      value = 120;
      servo1.write(value);
      delay(700);
      time = millis();
      while (scale0.get_units() - weight0 < 0.02 && millis() - time < 10000);
      delay(500);
      String str_output = String(scale0.get_units());
      String temp0 = "GET http://gamhs44.ivyro.net/process2.php?temp0=";
      value = 0;
      servo1.write(value);
      delay(500);
      servo1.detach();
      httpclient(str_output, temp0);
    }
    if (incomingByte == '1') {
      servo2.attach(11);
      weight1 = scale1.get_units();
      value = 120;
      servo2.write(value);
      delay(700);
      time = millis();
      while (scale1.get_units() - weight1 < 0.02 && millis() - time < 10000);
      delay(500);
      String str_output = String(scale1.get_units());
      String temp1 = "GET http://gamhs44.ivyro.net/process2.php?temp1=";
      value = 0;
      servo2.write(value);
      delay(500);
      servo2.detach();
      httpclient(str_output, temp1);
    }
    if (incomingByte == '2') {
      servo3.attach(12);
      weight2 = scale2.get_units();
      value = 120;
      servo3.write(value);
      delay(700);
      time = millis();
      while (scale2.get_units() - weight2 < 0.02 && millis() - time < 10000);
      delay(500);
      String str_output = String(scale2.get_units());
      String temp2 = "GET http://gamhs44.ivyro.net/process2.php?temp2=";
      value = 0;
      servo3.write(value);
      delay(500);
      servo3.detach();
      httpclient(str_output, temp2);
    }
    if (incomingByte == '3') {
      servo4.attach(13);
      weight3 = scale3.get_units();
      value = 120;
      servo4.write(value);
      delay(700);
      time = millis();
      while (scale3.get_units() - weight3 < 0.02 && millis() - time < 10000);
      delay(500);
      String str_output = String(scale3.get_units());
      String temp3 = "GET http://gamhs44.ivyro.net/process2.php?temp3=";
      value = 0;
      servo4.write(value);
      delay(500);
      servo4.detach();
      httpclient(str_output, temp3);
    }
    if (incomingByte == '4'){
      servo1.attach(10); servo2.attach(11); servo3.attach(12); servo4.attach(13);
      value = 0;
      servo1.write(value); servo2.write(value); servo3.write(value); servo4.write(value);
      delay(1000);
      servo1.detach(); servo2.detach(); servo3.detach(); servo4.detach();
    }
  }
} 