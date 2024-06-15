#ifndef BUTTONS_H
#define BUTTONS_H

#include "Config.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile bool buttonPressed[] = {false, false, false, false, false};

// ISR for PCINT0_vect (handles D8 to D10)
ISR(PCINT0_vect)
{
  // Debounce delay
  static unsigned long lastInterruptTime0 = 0;
  unsigned long interruptTime0 = millis();

  if (interruptTime0 - lastInterruptTime0 > 200)
  { // 200 ms debounce time
    for (int i = 2; i < 5; i++)
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
    for (int i = 0; i < 2; i++)
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

void setupButtons()
{
  // Set button pins as input with pull-up resistors
  for (int i = 0; i < 5; i++)
  {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  // Setup pin change interrupts
  setupPinChangeInterrupts();

  // Enable global interrupts
  sei();
}

void loopButtons()
{
  // Check if any button was pressed
  for (int i = 0; i < 5; i++)
  {
    if (buttonPressed[i])
    {
      Serial.print("Button ");
      Serial.print(i);
      Serial.println(" pressed");
      buttonPressed[i] = false; // Reset flag
    }
  }
}

#endif //BUTTONS_H
