#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/power.h>    // Power management
#include <avr/interrupt.h>
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
int inputPin = 9; //Chip Pin is 12. choose the input pin (for PIR sensor)

int val = 0; // variable for reading the pin status

//  14 is right pin 4 on 2313, bottom right on 85
int ledPin = 14;
//
int ledInd = 1; // indicator pin, chip pin 3
// how long to stay on in seconds (10 = 10 seconds)
long cycles = 180;

void setup()
{


  for (int i = 1; i < 20; i++) {
    pinMode(i, OUTPUT);
  }
  //add input to extend time on
  pinMode(inputPin, INPUT_PULLUP); // declare sensor as input


}

void loop() {

  for (int i = 1; i < cycles; i++) {
    digitalWrite(ledPin, HIGH); // turn LED ON
    digitalWrite(ledInd , HIGH); // turn LED ON

    delay(1000);

    digitalWrite(ledPin, LOW); // turn LED OFF
    digitalWrite(ledInd, LOW); // turn LED OFF

    if (digitalRead(inputPin) == LOW) {
      i = 1;
    }


  }
  goToSleep ();
}

\
void goToSleep ()
{

  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
  //  static byte prevADCSRA = ADCSRA;
  //  ADCSRA = 0;
  power_all_disable ();  // power off ADC, Timer 0 and 1, serial interface
  //  noInterrupts ();       // timed sequence coming up
  //  resetWatchdog ();      // get watchdog ready
  sleep_enable ();       // ready to sleep
  interrupts ();         // interrupts are required now
  sleep_cpu ();          // sleep
  //  sleep_disable ();      // precaution
  //  power_all_enable ();   // power everything back on
  //    ADCSRA = 1;            // turn on ADC
  ////  ADCSRA = prevADCSRA;
}  // end of goToSleep
