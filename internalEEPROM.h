#ifndef EEPROMLIBRARY_H
#define EEPROMLIBRARY_H

#include <EEPROM.h>

//addresses for EEPROM
#define int_target_angle1_ADDRESS                            0
#define int_target_angle2_ADDRESS                        (int_target_angle1_ADDRESS                     + sizeof(int))

//#define signed_char_sensorOffset1_ADDRESS                 (float_SetPointDiff_ADDRESS                 + sizeof(float))
//#define signed_char_sensorOffset2_ADDRESS                 (signed_char_sensorOffset1_ADDRESS          + sizeof(signed char))
//
//#define unsigned_long_Com_1_OperationDelay_ADDRESS        (signed_char_sensorOffset2_ADDRESS          + sizeof(signed char))
//#define unsigned_long_Com_2_OperationDelay_ADDRESS        (unsigned_long_Com_1_OperationDelay_ADDRESS + sizeof(unsigned long))
//
#define FirstTime_ADDRESS                                 (int_target_angle2_ADDRESS + sizeof(unsigned long))

extern int target_angle1;
extern int target_angle2;

// Function to write a string to EEPROM
void writeStringToEEPROM(int address, const String& data)
{
  for (size_t i = 0; i < data.length(); i++)
  {
    EEPROM.write(address + i, data[i]);
  }
  // Null-terminate the string
  EEPROM.write(address + data.length(), '\0');
}

// Function to read a string from EEPROM
String readStringFromEEPROM(int address)
{
  String result;
  char character = EEPROM.read(address);
  while (character != '\0')
  {
    result += character;
    address++;
    character = EEPROM.read(address);
  }
  return result;
}

void setupEEPROM()
{
  String Readings = readStringFromEEPROM(FirstTime_ADDRESS);

  if (Readings != "The First Time")
  {
    writeStringToEEPROM(FirstTime_ADDRESS, "The First Time");

    EEPROM.put(int_target_angle1_ADDRESS, target_angle1);
    EEPROM.put(int_target_angle2_ADDRESS, target_angle2);
  }
  else
  {
    EEPROM.get(int_target_angle1_ADDRESS, target_angle1);
    EEPROM.get(int_target_angle2_ADDRESS, target_angle2);
  }
}

void saveCurrentAngles()
{
  EEPROM.put(int_target_angle1_ADDRESS, MPU_Angle());
  EEPROM.put(int_target_angle2_ADDRESS, loopCompass());
}

#endif  //EEPROMLIBRARY_H
