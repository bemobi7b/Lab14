#define COUNTERPIN D6
#define STOPPERPIN D7

#include "oled-wing-adafruit.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

volatile uint16_t counter = 0;
volatile bool interruptOccured = false;
volatile bool areInterruptsOn = true;
volatile bool buttonState = false;

OledWingAdafruit display;

void setup()
{
  display.setup();
  resetDisplay();
  display.display();
  pinMode(COUNTERPIN, INPUT_PULLUP);
  pinMode(STOPPERPIN, INPUT_PULLUP);
  attachInterrupt(COUNTERPIN, isr, FALLING);
}
void loop()
{
  display.loop();

  if (interruptOccured)
  {
    counter++;
    resetDisplay();
    display.println(counter);
    display.display();
    interruptOccured = false;
  }
  if ((!digitalRead(STOPPERPIN)))
  {
    buttonState = true;
  }
  else if (buttonState)
  {
    areInterruptsOn = !areInterruptsOn;
    if (areInterruptsOn)
    {
      interrupts();
    }
    else
    {
      noInterrupts();
    }
    buttonState = false;
  }
}
void resetDisplay()
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
}
void isr()
{
  noInterrupts();
  interruptOccured = true;
  interrupts();
}