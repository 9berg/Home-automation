#include <DS1307RTC.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <Wire.h> 



int enA = 10;
int in1 = 7; 
int in2 = 5; 



void setup()
{
    
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    
  Serial.begin(9600);
  Serial.println("In setup....");
  /*
  using rtc, sync system time to rtc
   setTime(8,29,0,1,1,11); // set time to Saturday 8:29:00am Jan 1 2011 //old way *****************
   */

  // following lines added to set time from rtc, took from timeRtcSet example, added jim *****************
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if (timeStatus() != timeSet) 
    Serial.println("Unable to sync with the RTC");
  else
    Serial.println("RTC has set the system time");
  // end of setting the time ******************************


Alarm.timerRepeat(60, Repeat);            // pulse every 60   seconds



  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalClockDisplay();
  Serial.println("Ending setup....");
}


void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void Repeat() {
  digitalWrite(enA, HIGH);
  Serial.println("PULSE");
  digitalWrite(7, !digitalRead(7));  // toggle state
  digitalWrite(5, !digitalRead(5));
  delay(1000);
  digitalWrite(enA, LOW);
  
}


void  loop(){  
  digitalClockDisplay();
  Alarm.delay(1000);

}