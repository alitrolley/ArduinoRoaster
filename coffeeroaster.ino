// Sample Arduino MAX6675 Arduino Sketch

#include "max6675.h"
#include <Servo.h>
#include <avr/pgmspace.h>

Servo myservo;  
int pos = 42;    // variable to store the servo position
float temp = 25;
int ktcSO = 10;
int ktcCS = 9;
int ktcCLK = 8;
float temperatures[200];
float tempBackBuffer[200];
String cmd;
char previousCmd[4] = "NULL";
char cmdBuff[400];
String helloString = "hello";

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

void setup() {
  Serial.begin(115200);
  // give the MAX a little time to settle
  delay(500);
  myservo.attach(11);
  myservo.write(pos);
}

void loop() {
  temp = ktc.readCelsius();
  temperatures[0] = 5;
  if (Serial.available() >= 0) {

    Serial.readBytesUntil(cmdBuff, "\n");
    Serial.flush();
    if(previousCmd == "TEMP")
    {
        
    }
    if(((String)cmdBuff).indexOf("CHAN") != -1)
    {
      previousCmd = "CHAN";
      Serial.println("# Active channels set to 1234");
      Serial.flush();
    }
    if (((String)cmdBuff).indexOf("READ") != -1)
    {
      previousCmd = "READ";
      Serial.println((String)temp + ',' + (String)temp + ',' + (String)temp + ',' + (String)temp);
      Serial.flush();
      delay(200);
    }
    if(((String)cmdBuff).indexOf("TEMP") != -1)
    {
      previousCmd = "TEMP";
      int indexOfCmd = ((String)cmdBuff).indexOf("TEMP")+4;
      
    }
  }
  //myservo.write(degreesToServoInput(temp));
}

int degreesToServoInput(int pos)
{
  int lowerBound = 42;
  int upperBound = 145;
  float coefficient = ((float)upperBound-(float)lowerBound)/180.0;
  
  if (pos <= 180 && pos >= 0)
  {
    return lowerBound + (int)((float)pos*coefficient);
  }
  else if(pos > 180)
  {
    return 180;
  }
  else
  {
    return 0;
  }
   
}

int servoOutputToDegrees(int output)
{
  int lowerBound = 42;
  int upperBound = 145;
  float coefficient = ((float)upperBound-(float)lowerBound)/180.0;
  
  int degreeValue = (int)round(((float)output-(float)lowerBound)/coefficient);
  String printString = "first component: ";
  return degreeValue;
}
