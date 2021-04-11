#include <Arduino.h>
#include <Wire.h>
#include "RTC.h"
// #include "shiftRegister.h"

#define selectProgram 0

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    // DS3231 seconds, minutes, hours, day, date, month, year
    setDS3231time(45,59,10,2,11,01,21); // Use this function once to initialize, after init, comment this out of the code.

    //set pins to output because they are addressed in the main loop
    pinMode(latchPinSecond, OUTPUT);
    pinMode(clockPinSecond, OUTPUT);
    pinMode(dataPinSecond, OUTPUT);
    
    pinMode(latchPinMinute, OUTPUT);
    pinMode(clockPinMinute, OUTPUT);
    pinMode(dataPinMinute, OUTPUT);

    pinMode(latchPinHour, OUTPUT);
    pinMode(clockPinHour, OUTPUT);
    pinMode(dataPinHour, OUTPUT);

    Serial.begin(9600);
    
}

void loop()
{
    if (!selectProgram)
    {
        displayTime();  // display the real-time clock data on the Serial Monitor,
        delay(1000);    // every second
    }
    else
    {
        // Do something else
    }
    
}