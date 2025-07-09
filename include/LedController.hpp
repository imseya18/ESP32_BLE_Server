

#pragma once

#include <string>
#include <iostream>
#include "NimBLEDevice.h"
#include <FastLED.h>
#include "Constant.hpp"
#include <freertos/FreeRTOS.h>    
#include <freertos/queue.h>
class LedController
{
    public:
        LedController(CRGBArray<LED_COUNT>& ledsRef, std::vector<CRGBSet>& segmentsRef);
        /*
         Can't copy the class because it contains references to external objects.
         Copying would leave those references bound to the old instance's data,
         leading to dangling references in the new copy.
        */
        LedController(LedController const & src) = delete;
        LedController &     operator=(LedController const & rhs) = delete;
        ~LedController();


        void setLedColor(u_int8_t segment_index, CRGB rgbval) const;
        void setBrightness(u_int8_t brightness_value);
        void setLedsOn() const;
        void setLedsOff() const;
        
    private:
      LedController() = delete;
      u_int8_t _saved_brightness;
      CRGBArray<LED_COUNT>& _leds;
      std::vector<CRGBSet>& _segments;
};
