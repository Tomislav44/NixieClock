#include <arduino.h>

//Pin connected to ST_CP of 74HC595
int latchPinSecond = 4;
int latchPinMinute = 7;
int latchPinHour = 10;
////Pin connected to DS of 74HC595
int dataPinSecond = 3;
int dataPinMinute = 6;
int dataPinHour = 9;
//Pin connected to SH_CP of 74HC595
int clockPinSecond = 2;
int clockPinMinute = 5;
int clockPinHour = 8;

// Prototypes of functions
void shiftOut(int myDataPin, int myClockPin, byte myDataOut);
void shiftSelectedBitsSeconds(int selectedBit);
void shiftSelectedBitsMinutes(int selectedBit);
void shiftSelectedBitsHours(int selectedBit);

// the heart of the program
void shiftOut(int myDataPin, int myClockPin, byte myDataOut)
{
    int i=0;
    int pinState;
    digitalWrite(dataPinSecond, 0);
    digitalWrite(clockPinSecond, 0);
    for (i=7; i>=0; i--)  {
        digitalWrite(myClockPin, 0);
        if ( myDataOut & (1<<i) )
        {
            pinState= 1;
        }
        else
        {
            pinState= 0;
        }       
        digitalWrite(myDataPin, pinState);
        digitalWrite(myClockPin, 1);
        digitalWrite(myDataPin, 0);
    }
    digitalWrite(myClockPin, 0);
}

// Functions to control shift registers
void shiftSelectedBitsSeconds(int selectedBit)
{
    digitalWrite(latchPinSecond, 0);
    shiftOut(dataPinSecond, clockPinSecond, selectedBit);
    shiftOut(dataPinSecond, clockPinSecond, selectedBit);
    digitalWrite(latchPinSecond, 1);
    digitalWrite(latchPinSecond, 0);
    shiftOut(dataPinSecond, clockPinSecond, selectedBit);
    shiftOut(dataPinSecond, clockPinSecond, selectedBit);
    digitalWrite(latchPinSecond, 1);
}
void shiftSelectedBitsMinutes(int selectedBit)
{
    digitalWrite(latchPinMinute, 0);
    shiftOut(dataPinMinute, clockPinMinute, selectedBit);
    shiftOut(dataPinMinute, clockPinMinute, selectedBit);
    digitalWrite(latchPinMinute, 1);
    digitalWrite(latchPinMinute, 0);
    shiftOut(dataPinMinute, clockPinMinute, selectedBit);
    shiftOut(dataPinMinute, clockPinMinute, selectedBit);
    digitalWrite(latchPinMinute, 1);
}
void shiftSelectedBitsHours(int selectedBit)
{
    digitalWrite(latchPinHour, 0);
    shiftOut(dataPinHour, clockPinHour, selectedBit);
    shiftOut(dataPinHour, clockPinHour, selectedBit);
    digitalWrite(latchPinHour, 1);
    digitalWrite(latchPinHour, 0);
    shiftOut(dataPinHour, clockPinHour, selectedBit);
    shiftOut(dataPinHour, clockPinHour, selectedBit);
    digitalWrite(latchPinHour, 1);
}
