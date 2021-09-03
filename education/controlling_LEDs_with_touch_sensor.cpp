#include "../ev3dev.h"
#include <chrono>
#include <thread>

namespace ev3 = ev3dev;

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
   ev3::touch_sensor touch_s(ev3::INPUT_2);
   // print("Press the touch sensor to change the LED color!")
   // ev3::sound::speak("Press the touch sensor to change the LED color!", true);
   
   ev3::led::all_off();
   std::this_thread::sleep_for(std::chrono::milliseconds(500));
   
   while(true)
   {
      if(touch_s.is_pressed())
      {    		     
         ev3::led::set_color(ev3::led::left, ev3::led::red);
         for(auto led : ev3::led::right)
	 { 
	    led->off();
	 }
      }
      else
      {
         for(auto led : ev3::led::left)
	 {
	    led->off();
	 }
         ev3::led::set_color(ev3::led::right, ev3::led::green);
      }

      // don't let this loop use 100% of CPU
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
