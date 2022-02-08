#Description

The goal of this project is to deliver bare-bone customisable code and schematics to build DIY direct-drive vinyl player.

#Hardware
* Arduino UNO board - you may consider smaller substitution - just be prepared to tinker with it :-)
* TMC2209 driver - i was using Bigtreetech TMC2209 1.2
* NEMA17 stepper motor - i was using ANET 42SHDC3025-24B Stepper Motor (40N.cm. 1.8deg/step)
* 12V PSU for Motor
* 5-9V PSU for Arduino

You may consider using combined 5V + 12V PSU for a neat installation.

#Assembly
* Connect Arduino pin 4 with DIR pin on TMC2209 
* Connect Arduino pin 5 with STEP pin on TMC2209 
* Connect Arduino pin 6 with EN pin on TMC2209 
* Connect Arduino 5V pin with VDD pin on TMC2209 
* Connect Arduino GND pin with GND pin on TMC2209 (next to VDD pin)
* Connect Motor cables with TMC2209 board (mine has Black = B2, Green = B1, Blue = A1, Red = A2)
* Connect 12V with VM pin on TMC2209
* Connect GND (of 12V) with GND pin on TMC2209

Check twice :-)

#Starting and testing
* Hook-up Arduino to computer with Arduino studio
* Power-up the motor (12V PSU)
* Load the tmc2209_directdrive.ino sketch
* The motor should start automatically

ATTENTION
* Check motor temperature! If it gets really HOT - decrease current on TMC2209 board, by rotating potentiometer CLOCKWISE (in my case it took good 180 degrees swing to bring temperature to bearable level).
* There is a whole science behind this adjustment - please check description on Bigtreetech page, if you want to do this in a most proper way.

* Although it’s totally outside the scope of this project, but you definitely would need a spindle and platter. I suggest you to 3Dprint custom spindle and salvage platter from old player.
* I was using Turntable Speed application for iPhone - free and robust - to measure RPM of the final contraption. Based on these measurements you may want to adjust SETSPEED variable.

#Final settings
Once you finish testing and adjustments - burn the code to the Arduino, disconnect USB and power up the Arduino from PSU.

#Food for thought
This project delivers just a simple smooth rotating motor for your DIY turntable for a fraction of real direc-drive turntable cost.
Mine delivers 33.34 RPM with wow/flutter ~0.09 WRMS. Not a match for EDS 1000 but still very good performer.

I’m thinking about using rotary encoder to control start 33 / start 45 / stop  and fine adjustment of RPM, but  i hadn’t get there. Hope you will !

#Kudos & Kredits
* Kasidej Khunvattanakarn (https://github.com/ksdj55/dd_turntable) and his fine turntable project on Thingverse (https://www.thingiverse.com/thing:4894646)
* Dyzy for help with hardware and coding
