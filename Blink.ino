#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#define OPENING 1
#define CLOSING 0
Servo servo; 
int rotationCount = 0;
bool isMotorRunning = false;

char auth[] = "YOi_dIQ8tTwnVT2CBWS_1JvliQn9URej";
char ssid[] = "OPPO A53";
char pass[] = "shazain1";

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  servo.attach(D1); // NodeMCU D1 pin
  
 }
 void loop()
{
  Blynk.run();
  
}

BLYNK_WRITE(V1)
{
   int servoSpeed = param.asInt();
  if (servoSpeed > 0 && !isMotorRunning)
  {
    rotationCount = 0;
    isMotorRunning = true;
    rotateMotor();
  }
}

BLYNK_WRITE(V3)
{
servo.write(param.asInt());
//servo.write(0);
//servo.writeMicroseconds(2000);

}


void rotateMotor()
{
  if (rotationCount < 3)
  {
    // Rotate the motor
    servo.write(180); // Adjust the angle as per your motor's requirement
    delay(1000);      // Adjust the delay as per your motor's speed
    servo.write(0);
    delay(1000);

    rotationCount++;
    rotateMotor();
  }
  else
  {
    // Stop the motor
    servo.write(90);
    isMotorRunning = false;
  }
}

