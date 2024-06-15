#include "Config.h"
#include "MotorControl.h"
#include "MPU6050Sensor.h"
#include "QMC5883LCompass.h"
#include "internalEEPROM.h"
#include "Buttons.h"

int target_angle1 = 180;
int target_angle2 = 180;

void setup()
{
  Serial.begin(9600);
  delay(2000);
  setupMotors();
  setupCompass();
  setupEEPROM();
  setupButtons();
}

void loop()
{
  Control_of_Motor1();
  Control_of_Motor2();
  loopButtons();
}


void Control_of_Motor1()
{
  int angle = MPU_Angle();
  if(angle < target_angle1)
  {
    Set_Motor1_CW();
  }
  else if (angle > target_angle1)
  {
    Set_Motor1_CCW();
  }
  else
  {
    Stop_Motor1();
  }  
}


void Control_of_Motor2()
{
  int angle = loopCompass();
  if(angle < target_angle2)
  {
    Set_Motor2_CW();
  }
  else if (angle > target_angle2)
  {
    Set_Motor2_CCW();
  }
  else
  {
    Stop_Motor2();
  }  
}
