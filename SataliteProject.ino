#include "Config.h"
#include "MotorControl.h"
#include "MPU6050Sensor.h"

int target_angle = 180;

void setup()
{
  Serial.begin(9600);
  setupMotors();
}

void loop()
{
  int angle = MPU_Angle();
  if(angle < target_angle)
  {
    Set_Motor1_CW();
  }
  else if (angle > target_angle)
  {
    Set_Motor1_CCW();
  }
  else
  {
    Stop_Motor1();
  }  
}
