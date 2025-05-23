#include "Config.h"
#include "MotorControl.h"
#include "MPU9250Compass.h"
#include "internalEEPROM.h"
#include "Buttons.h"

#define MOTOR1CW    1
#define MOTOR1CCW   2
#define MOTOR1STOP  3

int target_angle1 = 90;
int target_angle2 = 90;

//////////////////////////////////////////////

int angle_P ;
int angle_N ;
int tolerance= 5;
int degree_P; 
int degree_N;
int disp=4;


void setup()
{
  Serial.begin(9600);
  delay(2000);
  setupMotors();
  setupCompass();
  setupEEPROM();
  setupButtons();
  Serial.print("target angle1: ");
  Serial.println(target_angle1);
  Serial.print("target angle2: ");
  Serial.println(target_angle2);
  delay(5000);
}

void loop()
{
  if (digitalRead(11) == LOW) //Mode is manual now.
  {
    loopButtons();
  }
  else  //Mode is automatic now.
  {
    Control_of_Motor1();
    Control_of_Motor2();
    Serial.println("Automatic mode");

  }


}


void Control_of_Motor1()
{
  int anglee = MPU_Angle();
  int err=target_angle1-anglee; 
  Serial.print("Target angle::");
  Serial.println(target_angle1);
  Serial.print("Angle::");
  Serial.println(anglee);
  Serial.print("Error_MPU::");
  Serial.println(err);

  ////////////////////////////////////////////////////////////
  
   if (abs(err)>3)            // allow some margin 
  {     
         if (err >0)
        {
          Set_Motor1_CW();
          Serial.println("Motor 1 CW");
        }
        else 
        {
          Set_Motor1_CCW();
          Serial.println("Motor 1 CCW");
        }
  }
  else
  {
    Stop_Motor1();
    Serial.println("Motor 1 Stop");
  }
}

  //  static uint8_t action = 0;
  //  static uint8_t last_action = 0;
  //
  //  if (angle < target_angle1)
  //  {
  //    action = MOTOR1CW;
  //  }
  //  else if (angle > target_angle1)
  //  {
  //    action = MOTOR1CCW;
  //  }
  //  else
  //  {
  //    action = MOTOR1STOP;
  //  }
  //
  //  if (action != last_action)
  //  {
  //    if (action == MOTOR1CW)
  //    {
  //      last_action = action;
  //      Set_Motor1_CW();
  //      Serial.println("Motor 1 CW");
  //    }
  //    else if (action == MOTOR1CCW)
  //    {
  //      last_action = action;
  //      Set_Motor1_CCW();
  //      Serial.println("Motor 1 CCW");
  //    }
  //    else if (action == MOTOR1STOP)
  //    {
  //      last_action = action;
  //      Stop_Motor1();
  //      Serial.println("Motor 1 stop");
  //    }
  //  }



void Control_of_Motor2()
{
  int Angle = loopCompass();
  int er=target_angle2-Angle; 
  Serial.print("Target angle::");
  Serial.println(target_angle2);
  Serial.print("Angle::");
  Serial.println(Angle);
  Serial.print("Error_Compass::");
  Serial.println(er);

  

  if (abs(er)>1)            // allow some argin 
  {      
         if (er >0)
        {
          Set_Motor2_CW();
          Serial.println("Motor 2 CW");
        }
        else 
        {
          Set_Motor2_CCW();
          Serial.println("Motor 2 CCW");
        }
  }
  else
  {
    Stop_Motor2();
    Serial.println("Motor 2 Stop");
  }
}
