#include <arduino.h>
#include <Wire.h>
#include "shiftRegister.h"

#define DS3231_I2C_ADDRESS 0x68 

// Parameter to hold data for seconds/minutes/hours
int secondLow = 0;
int secondHigh = 0;
int seconds = 0;

int minuteLow = 0;
int minuteHigh = 0;
int minutes = 0;

int hourLow = 0;
int hourHigh = 0;
int hours = 0;

// Prototypes for all functions
byte decToBcd(byte val);
byte bcdToDec(byte val);
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year);
void readDS3231time(byte *second,byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year);
void displayTime();
void turnOnSecondL(int number);
void turnOnSecondH(int number);
void turnOnMinuteL(int number);
void turnOnMinuteH(int number);
void turnOnHourL(int number);
void turnOnHourH(int number);

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
    return( (val/10*16) + (val%10) );
}
byte bcdToDec(byte val)
{  // Convert binary coded decimal to normal decimal numbers
    return( (val/16*10) + (val%16) );
}

// Functions for setting and reading the time from the DS3231 RTC module
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
{
    // sets time and date data to DS3231
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0); // set next input to start at the seconds register
    Wire.write(decToBcd(second)); // set seconds
    Wire.write(decToBcd(minute)); // set minutes
    Wire.write(decToBcd(hour)); // set hours
    Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
    Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
    Wire.write(decToBcd(month)); // set month
    Wire.write(decToBcd(year)); // set year (0 to 99)
    Wire.endTransmission();
}
void readDS3231time(byte *second,byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year)
{
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0); // set DS3231 register pointer to 00h
    Wire.endTransmission();
    Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
    // request seven bytes of data from DS3231 starting from register 00h
    *second = bcdToDec(Wire.read() & 0x7f);
    *minute = bcdToDec(Wire.read());
    *hour = bcdToDec(Wire.read() & 0x3f);
    *dayOfWeek = bcdToDec(Wire.read());
    *dayOfMonth = bcdToDec(Wire.read());
    *month = bcdToDec(Wire.read());
    *year = bcdToDec(Wire.read());
}

// Function to convert the time from the RTC module to output for the Binary to Decimal Decoder
void displayTime()
{
     turnOnHourH(2);
     turnOnHourL(2);
     turnOnMinuteH(2);
     turnOnMinuteL(2);
     turnOnSecondH(2);
     turnOnSecondL(2);
 }



//    byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
//    // retrieve data from DS3231
//    readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
//
//    //for hours - max hours = 23   
//    int hourL, hourH = 0;
//    hourH = hour / 10;
//    if (hour >= 10)
//    {
//        hourL = hour % 10;
//    }
//    else
//    {
//        hourL = hour;
//    }
//
//    switch (hourH)
//    {
//        case 0:
//        turnOnHourH(0);
//        break;
//        case 1:
//        turnOnHourH(1);
//        break;
//        case 2:
//        turnOnHourH(2);
//        break;
//        default:
//        break;
//    }
//        
//    switch (hourL)
//    {
//        case 0:
//        turnOnHourL(0);
//        break;
//        case 1:
//        turnOnHourL(1);
//        break;
//        case 2:
//        turnOnHourL(2);
//        break;
//        case 3:
//        turnOnHourL(3);
//        break;
//        case 4:
//        turnOnHourL(4);
//        break;
//        case 5:
//        turnOnHourL(5);
//        break;
//        case 6:
//        turnOnHourL(6);
//        break;
//        case 7:
//        turnOnHourL(7);
//        break;
//        case 8:
//        turnOnHourL(8);
//        break;
//        case 9:
//        turnOnHourL(9);
//        break;
//        default:
//        break;
//    }
//    
//    //for minutes - max min. = 59   
//    int minuteL, minuteH = 0;
//    minuteH = minute / 10;
//    if (minute >= 10)
//    {
//        minuteL = minute % 10;
//    }
//    else
//    {
//        minuteL = minute;
//    }
//
//    switch (minuteH)
//    {
//        case 0:
//        turnOnMinuteH(0);
//        break;
//        case 1:
//        turnOnMinuteH(1);
//        break;
//        case 2:
//        turnOnMinuteH(2);
//        break;
//        case 3:
//        turnOnMinuteH(3);
//        break;
//        case 4:
//        turnOnMinuteH(4);
//        break;
//        case 5:
//        turnOnMinuteH(5);
//        break;
//        default:
//        break;
//    }
//        
//    switch (minuteL)
//    {
//        case 0:
//        turnOnMinuteL(0);
//        break;
//        case 1:
//        turnOnMinuteL(1);
//        break;
//        case 2:
//        turnOnMinuteL(2);
//        break;
//        case 3:
//        turnOnMinuteL(3);
//        break;
//        case 4:
//        turnOnMinuteL(4);
//        break;
//        case 5:
//        turnOnMinuteL(5);
//        break;
//        case 6:
//        turnOnMinuteL(6);
//        break;
//        case 7:
//        turnOnMinuteL(7);
//        break;
//        case 8:
//        turnOnMinuteL(8);
//        break;
//        case 9:
//        turnOnMinuteL(9);
//        break;
//        default:
//        break;
//    }
//    
//    //for seconds - max sec. = 59
//    int secondL, secondH = 0;
//    secondH = second / 10;
//    if (second >= 10)
//    {
//        secondL = second % 10;
//    }
//    else
//    {
//        secondL = second;
//    }
//
//    switch (secondH)
//    {
//        case 0:
//        turnOnSecondH(0);
//        break;
//        case 1:
//        turnOnSecondH(1);
//        break;
//        case 2:
//        turnOnSecondH(2);
//        break;
//        case 3:
//        turnOnSecondH(3);
//        break;
//        case 4:
//        turnOnSecondH(4);
//        break;
//        case 5:
//        turnOnSecondH(5);
//        break;
//        default:
//        break;
//    }
//        
//    switch (secondL)
//    {
//        case 0:
//        turnOnSecondL(0);
//        break;
//        case 1:
//        turnOnSecondL(1);
//        break;
//        case 2:
//        turnOnSecondL(2);
//        break;
//        case 3:
//        turnOnSecondL(3);
//        break;
//        case 4:
//        turnOnSecondL(4);
//        break;
//        case 5:
//        turnOnSecondL(5);
//        break;
//        case 6:
//        turnOnSecondL(6);
//        break;
//        case 7:
//        turnOnSecondL(7);
//        break;
//        case 8:
//        turnOnSecondL(8);
//        break;
//        case 9:
//        turnOnSecondL(9);
//        break;
//        default:
//        break;
//    }
//}

// Functions to take care of turning individual bits on or off
void turnOnSecondL(int number)
{
    secondLow = number;
    seconds = secondHigh + (secondLow << 4);
    shiftSelectedBitsSeconds(seconds);
    // For debug monitoring
    Serial.print(number);
    Serial.print("\n");
}
void turnOnSecondH(int number)
{ 
    secondHigh = number;
    seconds = secondHigh + (secondLow << 4);
    shiftSelectedBitsSeconds(seconds);
    // For debug monitoring
    Serial.print(":");
    Serial.print(number);
}

void turnOnMinuteL(int number)
{    
    minuteLow = number;
    minutes = minuteHigh + (minuteLow << 4);
    shiftSelectedBitsMinutes(minutes);
    // For debug monitoring
    Serial.print(number);
}
void turnOnMinuteH(int number)
{       
    minuteHigh = number;
    minutes = minuteHigh + (minuteLow << 4);
    shiftSelectedBitsMinutes(minutes); 
    // For debug monitoring
    Serial.print(":");
    Serial.print(number);
}

void turnOnHourL(int number)
{
    hourLow = number;
    hours = hourHigh + (hourLow << 4);
    shiftSelectedBitsHours(hours);
    // For debug monitoring
    Serial.print(number);
}
void turnOnHourH(int number)
{
    hourHigh = number;
    hours = hourHigh + (hourLow << 4);
    shiftSelectedBitsHours(hours);
    // For debug monitoring
    Serial.print("Time: ");
    Serial.print(number);
}
