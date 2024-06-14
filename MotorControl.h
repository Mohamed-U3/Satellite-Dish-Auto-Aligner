#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H


void setupMotors()
{
  // Set the Pins of the Motors to Output
  pinMode(MOTOR1_CW_PIN   ,OUTPUT);
  pinMode(MOTOR1_CCW_PIN  ,OUTPUT);
  pinMode(MOTOR2_CW_PIN   ,OUTPUT);
  pinMode(MOTOR2_CCW_PIN  ,OUTPUT);
  digitalWrite(MOTOR1_CW_PIN  ,LOW);
  digitalWrite(MOTOR1_CCW_PIN ,LOW);
  digitalWrite(MOTOR2_CW_PIN  ,LOW);
  digitalWrite(MOTOR2_CCW_PIN ,LOW);
}


void Set_Motor1_CW()
{
  digitalWrite(MOTOR1_CCW_PIN ,LOW);
  digitalWrite(MOTOR1_CW_PIN  ,HIGH);
}

void Set_Motor1_CCW()
{
  digitalWrite(MOTOR1_CW_PIN  ,LOW);
  digitalWrite(MOTOR1_CCW_PIN ,HIGH);
}

void Stop_Motor1()
{
  digitalWrite(MOTOR1_CW_PIN  ,LOW);
  digitalWrite(MOTOR1_CCW_PIN ,LOW);
}

void Set_Motor2_CW()
{
  digitalWrite(MOTOR2_CCW_PIN ,LOW);
  digitalWrite(MOTOR2_CW_PIN  ,HIGH);
}

void Set_Motor2_CCW()
{
  digitalWrite(MOTOR2_CW_PIN  ,LOW);
  digitalWrite(MOTOR2_CCW_PIN ,HIGH);
}

void Stop_Motor2()
{
  digitalWrite(MOTOR2_CW_PIN  ,LOW);
  digitalWrite(MOTOR2_CCW_PIN ,LOW);
}

#endif  //MOTORCONTROL_H
