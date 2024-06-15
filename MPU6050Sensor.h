#ifndef MPU6050SENSOR_H
#define MPU6050SENSOR_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

#define MPU_addr  0x68
int xAng, yAng;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
double z = 0;
#define minVal    265
#define maxVal    402

int MPU_Angle()
{
  int value = 0;
  if (!mpu.begin())
  {
    Serial.println("MPU6050 Module Not Found!!");
//    display.println(F("Module Error"));  // set info
//    display.display();
  }
  else
  {
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);

    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 14, true);
    AcX = Wire.read() << 8 | Wire.read();
    AcY = Wire.read() << 8 | Wire.read();
    xAng = map(AcX, minVal, maxVal, -90, 90);
    yAng = map(AcY, minVal, maxVal, -90, 90);
    z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
    z = z + 90;
    if (z > 360) z = z - 360;
    //    Serial.print(F("Current angle: "));
    //    Serial.println(z);
    value = round(z);
    value = abs(value);

    //thia section is for correcting the angle
    float corrected_angle = value - 180;

    // Normalize the angle to be within 0 to 360 degrees
    if (corrected_angle < 0)
    {
      corrected_angle += 360;
    }
    else if (corrected_angle >= 360)
    {
      corrected_angle -= 360;
    }
    value = corrected_angle;
    //    Serial.println(value);
  }
  return value;
}

#endif //MPU6050SENSOR_H
