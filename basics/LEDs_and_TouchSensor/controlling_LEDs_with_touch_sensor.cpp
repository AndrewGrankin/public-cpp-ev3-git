#include "../../ev3dev.h"
#include <chrono>
#include <thread>
#include <iostream>

namespace ev3 = ev3dev;

int main()
{
   ev3::touch_sensor touch_s(ev3::INPUT_2);
   std::cout << "Press the touch sensor to switch the LED color!" << std::endl;
   ev3::sound::speak("Press the touch sensor to switch the LED color!", false);
   
   // switch the leds off and wait for a second
   ev3::led::all_off();
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   
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
   return 0;
}
