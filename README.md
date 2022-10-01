# Octoprint-status-dashboard
This project was created as a simple hardware dashboard, so the user could on first glance know the state of the current 3D print.

If you search an internet for "3D printer status monitor", "Octoprint monitor" and similar phrases, you will find a lot of very nice looking things. I did not like any of those, since all of them (that I found back in the day) had display. Sometimes big, sometimes small, but always display.
Display can display (pun intended) a lot of informations at once, but usually it takes longer to absorb them. And I wanted to read 3D printer status with one quick glance.
I wanted just a bunch of LEDs showing me, how long do I have to wait until I can play with finished print.

# Requirements
My 3D printer runs Octoprint (and I think almost every printer should run it), and Octoprint has REST API (https://docs.octoprint.org/en/master/api/index.html). So I have found what is possible in the documentation and settled on these parameters that will be shown:
1) printer state - 2 LEDs, one for Ready, one for Printing
2) Extruder temps - 3 LEDs, Cool (extruder below 25C), Heat (currently heating), on Temperature (actual temp is within 5 degrees of target temp)
3) Bed temps - 3 LEDs, the same as Extruder temps.
4) Progress - 10 LEDs, one for each 10% (the LED lits up when the progres is over its percentage)
5) ETA - 5 LEDs, in roughly logarytmic scale. Most of my prints were under 2 hours, so 2h, 1h, 30mins, 15mins and 5mins were chosen (the LED lits up when the time is over its value)


# Technology
As brain I have choosen NodeMCU, which utilizes my favourite ESP8266 chip. It has Wifi connectivity and is very low cost. Since I wanted this project to be easily expandable (I thought about adding inputs for preheating and so on), I have chosen to use shifting registers 74HC595N to drive the LEDs. Here (https://www.arduino.cc/en/Tutorial/Foundations/ShiftOut) is very nice example directly from arduino how to connect it. The 74HC595N can drive LEDs directly, and you can chain them all you want. Since this project needs to drive 23 LEDs, I have used 3 of them.

#3D print
Usually, one of the hardes part of creating project is making a case for it. Luckily, as you have probably guessed it, I own a 3D printer.
The main body was desingned in OpenSCAD, the files are included in the folder *model*. It was designed to be printed in 3 different colors. Start printing in a base color, change to rectangle color in last 6 layers, and then change to legend color for the last 3 layers.
The 3d print should screw together, just use very small screws (it was designed quite poorly).

#How to replicate this project
1) Connect shifting register to your LEDs based on this manual (https://www.arduino.cc/en/Tutorial/Foundations/ShiftOut)
2) Install Arduino IDE
3) Install ESP8266 board in the Arduino IDE (https://create.arduino.cc/projecthub/electropeak/getting-started-w-nodemcu-esp8266-on-arduino-ide-28184f, step 1.)
4) Download the code from this project
5) Change the apiKey to the api key of your Octoprint instance
6) change the printerAddressApi and jobAddressApi to your Octoprint instance
7) If needed, change the LEDs order
8) Change your wifi ssid and password
9) Upload sketch
10) Enjoy


