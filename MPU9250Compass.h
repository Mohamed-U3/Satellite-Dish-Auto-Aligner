#ifndef MPU9250COMPASS_H
#define MPU9250COMPASS_H

#include "MPU9250.h"

MPU9250 mpu9250;

void setupCompass()
{
  Serial.println(F("Compass Init start"));
  Wire.begin();
  delay(1000); // Reduced from 2000ms
  
  if (!mpu9250.setup(0x68)) {
    Serial.println(F("MPU connection failed"));
    while (1) delay(5000);
  }
  
  // Disable verbose mode to save memory
  mpu9250.verbose(false);
  
  // Quick calibration without verbose messages
  mpu9250.calibrateAccelGyro();
  mpu9250.calibrateMag();
  
  Serial.println(F("Compass Init ended"));
}

int loopCompass()
{
  if (mpu9250.update())
  {
    // Use integer math to save memory
    int mx_scaled = (int)(mpu9250.getMagX() * 1000);
    int my_scaled = (int)(mpu9250.getMagY() * 1000);
    
    // Calculate azimuth using integer approximation
    float azimuth_rad = atan2(my_scaled, mx_scaled);
    int azimuth = (int)(azimuth_rad * 57.2958); // 180/PI ≈ 57.2958
    
    if (azimuth < 0) azimuth += 360;
    
    Serial.print(F("A: "));
    Serial.println(azimuth);
    delay(2);
    return azimuth;
  }
  return -1;
}

#define minVal    265
#define maxVal    402

int MPU_Angle()
{  
  if (mpu9250.update())
  {
    // Get accelerometer values from MPU9250
    float AcX = mpu9250.getAccX();
    float AcY = mpu9250.getAccY();
    
    // Convert to integer for mapping (multiply by 1000 for precision)
    int16_t AcX_int = (int16_t)(AcX * 1000);
    int16_t AcY_int = (int16_t)(AcY * 1000);
    
    // Map using your existing calibration values
    int xAng = map(AcX_int, minVal, maxVal, -90, 90);
    int yAng = map(AcY_int, minVal, maxVal, -90, 90);
    
    // Calculate angle using your existing formula
    float z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
    z = z + 90;
    if (z > 360) z = z - 360;
    
    int value = (int)z;
    value = abs(value);
    
    // Apply your angle correction
    float corrected_angle = value - 180;
    
    if (corrected_angle < 0) {
      corrected_angle += 360;
    }
    else if (corrected_angle >= 360) {
      corrected_angle -= 360;
    }
    
    value = (int)corrected_angle;
    
    Serial.print(F("MPU angle: "));
    Serial.println(value);
    
    return value;
  }
  
  return 0; // Return 0 if update failed
}

#endif //MPU9250COMPASS_H
