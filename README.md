# Home-automation

This project was to make a frequently public environment clock system adapted for at-home usage.

The idea was to abandon the usage of a remote clock signal device (commonly installed at separate facility room in schools, airports, hospitals etc.) and shrink it enough to enable mounting directly on the clock-face back, making the system installable just like any normal clock in a house.

The subtasks and components for this signal device were found as follows:

- A pulse signal that is to be repeatedly sent to a control unit. A signal which, if it weren't an exact render, at least with great similarity could resemble time itself.
This was found to be a RTC DS1307- s.c a Real Time Clock.

- A transformer of some sort, amplifying the voltage enough to push the dials that were connected through gears to the core of the solenoid. From reading manuals, I understood that this had to be done with a 24 volt polar switching current.
Due to this demand, I purchased a SX1308 "voltage booster".

- A signal operated H-Bridge that would output the polar switching pattern, favored by the clock. For this, the NS754410 was chosen.

- A control unit operating the H-Bridge signal. Not only did this have to transfer the RTC info correctly but also change the polarity, and send a square signal with a phase duration long enough to satisfy the inertia in the solenoid as well as the connected mechanics in the movement of the clock arms, which was to be an Arduino Nano.

Links to the components can be found below:

Arduino Nano: https://store.arduino.cc/en-se/products/arduino-nano

DS1307: https://www.electrokit.com/rtc-modul-i2c-mini-ds1307?gad_source=1&gclid=CjwKCAjwxNW2BhAkEiwA24Cm9NVZqLC5jlmfvjE498lM0YvufUM_L7y6S6cdqQxMZDg_3Zzq0jAGfRoCpDUQAvD_BwE

SX1308: https://www.aliexpress.com/item/1005003039023039.html?src=google&src=google&albch=shopping&acnt=298-731-3000&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&gclsrc=aw.ds&&albagn=888888&&ds_e_adid=&ds_e_matchtype=&ds_e_device=c&ds_e_network=x&ds_e_product_group_id=&ds_e_product_id=en1005003039023039&ds_e_product_merchant_id=107802845&ds_e_product_country=SE&ds_e_product_language=en&ds_e_product_channel=online&ds_e_product_store_id=&ds_url_v=2&albcp=21634419038&albag=&isSmbAutoCall=false&needSmbHouyi=false&gad_source=1&gclid=CjwKCAjwxNW2BhAkEiwA24Cm9Jv00RF6vXHpu4WY0Xv7sj6wKlH41vpzUgf-t_xsr6Hwa9SfGRYU4xoCe5EQAvD_BwE

754410: https://www.mouser.se/ProductDetail/Texas-Instruments/SN754410NE?qs=AMJt07B76uuZ4Fb3eRjJ6A%3D%3D&mgh=1&utm_id=20705987001&gad_source=1&gclid=CjwKCAjwxNW2BhAkEiwA24Cm9I8gxWCyl_00ZX5CDdOLIfCuM_b_aM0s1OSrJ3Rd0qJXjFo1g7n7yhoC0ZEQAvD_BwE

To find a Westerstrand 230mm time-face, go ask a janitor to a school or similar facility in Sweden or consult any digital circular marketplace.


To make the signal change polarity, I sketched what I thought to be a good solution. This, I later understood, was a classic component called the H-Bridge. Down below are images of what I imagined this part to do. It used some kind of gates (initially I thought this could be some PNP or NPN transistors, I wasn't sure). 

![Image](https://github.com/user-attachments/assets/2afc39ff-a850-480a-b888-dbd4fa096ca7)
I indicated M for "motor" and wrote directions for what would need to happen to make the current direction shift. 
![Image](https://github.com/user-attachments/assets/8dc3eba8-5701-44d1-a809-5992d16d1d2c)
Here, the direction has changed (see arrow direction for guidance). 
![Image](https://github.com/user-attachments/assets/ccb10140-1dc7-4ae8-9225-38f7ee8a048b)
A while later, this H-bridge was placed as the 754410 component in the final circuit (here the RTC is missing).  

  


Adding the components was done with freely hanging board cable and a bit of soldering for the pin lacking chips. Before I had realized that the Arduino could not send that great a signal to make the time right, I put the components on a breadboard. Images below show the progress. 

![Image](https://github.com/user-attachments/assets/e6207a55-01e6-4ea3-bd06-8b9a1a832bc1)
The breadboard uses two separate lines for ground and current feed (two long canals on the left of the components). 


I decided to have 5v in the feed and the 24v output solely to the clock. 


![Image](https://github.com/user-attachments/assets/f5009000-42f7-4494-b1f8-af0861ad5a69)


The above image shows the connection points on the RTC. This was GND, drive voltage (VCC), serial clock (SCL) and serial Data (SDA). The spacing matched well with the breadboard I used, but soldering needed to be done for the fixation and creation of a circuit. The SCL was connected with port 10 on the Arduino. 







To make the signal change polarity, I sketched what I thought to be a good solution. This, I later understood, was a classic component called the H-Bridge. Down below are images of what I imagined this part to do. It used some kind of gates (initially I thought this could be some PNP or NPN transistors, I wasn't sure).

Image
I indicated M for "motor" and wrote directions for what would need to happen to make the current direction shift.
Image
Here, the direction has changed (see arrow direction for guidance).
Image



The code was used with Arduino IDE. The ports on the Arduino can be changed if desirable, as well as the synchronization start for the time and date. When setting up, I recommend using the Alarm.timeRepeat set at 1 instead of 60 to enable testing connection every second. 

________________________________________________________________________________________________________

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
A while later, this H-bridge was placed as the 754410 component in the final circuit (here the RTC is missing).



To test the signal, I connected the pins from 754410 directly to LED. Since it only allowed passage in one direction, it therefore ran with half the tempo, and gave a good oversight on how long the "on" duration would be for the signal. 


![Image](https://github.com/user-attachments/assets/918a3942-5259-4cc2-99df-af9a87dfc339)
To my delight, the light appeared, showing that the code and circuit design was working. 


I then connected this to a multimeter and increased the voltage sent from the SX1308 to an average of 24v.   

To finish off, I used a USB c connector to ensure that I could use it with both battery and direct power. Since the Arduino consumes roughly 20mA, the battery alternative needs to be in the x-thousands of milliamps to not require changing all the time. For my project it was rather the option, not the efficiency, that was central.  If one really demands a more power efficient option, I believe a ATTINI85 could be a reasonable improvement. 
![Image](https://github.com/user-attachments/assets/ea73588d-1b98-443c-a827-9b260ae5fc51)
This project has led me into some kind of interest of robotics and home automation. I do think I've been inspired to do some more projects in that fashion that I can share on this account in the future.  

