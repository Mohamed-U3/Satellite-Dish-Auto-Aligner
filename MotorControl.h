#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H


void setupMotors()
{
  // Set the Pins of the Motors to Output
  pinMode(MOTOR1_CW   ,OUTPUT);
  pinMode(MOTOR1_CCW  ,OUTPUT);
  pinMode(MOTOR2_CW   ,OUTPUT);
  pinMode(MOTOR2_CCW  ,OUTPUT);
  digitalWrite(MOTOR1_CW  ,LOW);
  digitalWrite(MOTOR1_CCW ,LOW);
  digitalWrite(MOTOR2_CW  ,LOW);
  digitalWrite(MOTOR2_CCW ,LOW);
}


void Set_Motor1_CW()
{
  digitalWrite(MOTOR1_CCW ,LOW);
  digitalWrite(MOTOR1_CW  ,HIGH);
}

void Set_Motor1_CCW()
{
  digitalWrite(MOTOR1_CW  ,LOW);
  digitalWrite(MOTOR1_CCW ,HIGH);
}

void Stop_Motor1()
{
  digitalWrite(MOTOR1_CW  ,LOW);
  digitalWrite(MOTOR1_CCW ,LOW);
}

void Set_Motor2_CW()
{
  digitalWrite(MOTOR2_CCW ,LOW);
  digitalWrite(MOTOR2_CW  ,HIGH);
}

void Set_Motor2_CCW()
{
  digitalWrite(MOTOR2_CW  ,LOW);
  digitalWrite(MOTOR2_CCW ,HIGH);
}

void Stop_Motor2()
{
  digitalWrite(MOTOR2_CW  ,LOW);
  digitalWrite(MOTOR2_CCW ,LOW);
}

#endif  //MOTORCONTROL_H
