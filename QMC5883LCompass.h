#ifndef QMC5883LCOMPASS_H
#define QMC5883LCOMPASS_H

#include <QMC5883LCompass.h>

QMC5883LCompass compass;

void setupCompass()
{
  Serial.println("Compass Init start");
  compass.init();
  Serial.println("Compass Init ended");
}

int loopCompass()
{
  int a;
  // Read compass values
  compass.read();

  // Return Azimuth reading
  a = compass.getAzimuth();
  
  Serial.print("A: ");
  Serial.println(a);
  delay(2);

  return a;
}

#endif  //QMC5883LCOMPASS_H
