#ifndef BUTTONS_H
#define BUTTONS_H

#include "Config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "MotorControl.h"
#include "internalEEPROM.h"

volatile bool buttonPressed[] = {false, false, false, false, false};
extern int target_angle1;
extern int target_angle2;

// ISR for PCINT0_vect (handles D8 to D10)
ISR(PCINT0_vect)
{
  // Debounce delay
  static unsigned long lastInterruptTime0 = 0;
  unsigned long interruptTime0 = millis();

  if (interruptTime0 - lastInterruptTime0 > 200)
  { // 200 ms debounce time
    for (uint8_t i = 2; i < 5; i++)
    { // Checking D8 to D10
      if (digitalRead(buttonPins[i]) == LOW)
      { // Assuming active LOW
        buttonPressed[i] = true;
      }
    }
  }
  lastInterruptTime0 = interruptTime0;
}

// ISR for PCINT2_vect (handles D6 to D7)
ISR(PCINT2_vect)
{
  // Debounce delay
  static unsigned long lastInterruptTime2 = 0;
  unsigned long interruptTime2 = millis();

  if (interruptTime2 - lastInterruptTime2 > 200)
  { // 200 ms debounce time
    for (uint8_t i = 0; i < 2; i++)
    { // Checking D6 to D7
      if (digitalRead(buttonPins[i]) == LOW)
      { // Assuming active LOW
        buttonPressed[i] = true;
      }
    }
  }
  lastInterruptTime2 = interruptTime2;
}

void setupPinChangeInterrupts()
{
  // Enable pin change interrupt for PCINT0 and PCINT2 groups
  PCICR |= (1 << PCIE0) | (1 << PCIE2);

  // Enable pin change interrupt for D8 to D10 (PCINT0)
  PCMSK0 |= (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2);

  // Enable pin change interrupt for D6 to D7 (PCINT2)
  PCMSK2 |= (1 << PCINT22) | (1 << PCINT23);
}

void change_target_angle()
{
  target_angle1 = MPU_Angle();
  target_angle2 = loopCompass();
}

void setupButtons()
{
  Serial.println("buttons init start");
  // Set button pins as input with pull-up resistors
  for (uint8_t i = 0; i < 5; i++)
  {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  // Setup pin change interrupts
  setupPinChangeInterrupts();

  // Enable global interrupts
  sei();

  pinMode(11, INPUT_PULLUP);
  Serial.println("buttons init ended");
}

void loopButtons()
{
  if (buttonPressed[0]) //save the angle
  {
    saveCurrentAngles();
    buttonPressed[0] = false; // Reset flag
  }
  if (buttonPressed[1]) //save the angle
  {
    Set_Motor1_CW();
    //    change_target_angle();
    delay(200);
    buttonPressed[1] = false; // Reset flag
  }
  if (buttonPressed[2]) //save the angle
  {
    Set_Motor1_CCW();
    //    change_target_angle();
    delay(200);
    buttonPressed[2] = false; // Reset flag
  }
  if (buttonPressed[3]) //save the angle
  {
    Set_Motor2_CW();
    //    change_target_angle();
    delay(200);
    buttonPressed[3] = false; // Reset flag
  }
  if (buttonPressed[4]) //save the angle
  {
    Set_Motor2_CCW();
    //    change_target_angle();
    delay(200);
    buttonPressed[4] = false; // Reset flag
  }
  if(digitalRead(7) == HIGH && digitalRead(8) == HIGH)
  {
    Stop_Motor1();
  }
  if(digitalRead(9) == HIGH && digitalRead(10) == HIGH)
  {
    Stop_Motor2();
  }

}

#endif //BUTTONS_H
