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

Image
I indicated M for "motor" and wrote directions for what would need to happen to make the current direction shift.
Image
Here, the direction has changed (see arrow direction for guidance).
Image
A while later, this H-bridge was placed as the 754410 component in the final circuit (here the RTC is missing).



