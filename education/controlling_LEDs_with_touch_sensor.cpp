#include "../ev3dev.h"

/* 
from time import sleep

from ev3dev2.sensor import INPUT_2
from ev3dev2.sensor.lego import TouchSensor
from ev3dev2.led import Leds
from ev3dev2.sound import Sound

ts = TouchSensor(INPUT_2)
leds = Leds()
speaker = Sound() */

int main()
{
   // print("Press the touch sensor to change the LED color!")
   ev3dev::sound::speak("Press the touch sensor to change the LED color!", true);
   
   while(true)
   {
      ev3dev::led::set_color(ev3dev::led::left, ev3dev::led::red);
      ev3dev::led::set_color(ev3dev::led::right, ev3dev::led::green);
   }
/*
while True:
    if ts.is_pressed:
        leds.set_color("LEFT", "GREEN")
        leds.set_color("RIGHT", "GREEN")
    else:
        leds.set_color("LEFT", "RED")
        leds.set_color("RIGHT", "RED")
    # don't let this loop use 100% of CPU
    sleep(0.01)
*/

}
