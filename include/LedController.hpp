

#pragma once

#include <FastLED.h>
#include <Preferences.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#include <iostream>
#include <string>

#include "Constant.hpp"
#include "NimBLEDevice.h"

extern std::vector<std::array<u_int8_t, 3>> persistent_rgb_value;
extern Preferences persistent_state;
class LedController {
   public:
    LedController(CRGBArray<LED_COUNT> &ledsRef,
                  std::vector<CRGBSet> &segmentsRef);
    /*
     Can't copy the class because it contains references to external objects.
     Copying would leave those references bound to the old instance's data,
     leading to dangling references in the new copy.
    */
    LedController(LedController const &src) = delete;
    LedController &operator=(LedController const &rhs) = delete;
    ~LedController();

    void setLedColor(uint8_t segment_index, CRGB rgbval) const;
    void setBrightness(uint8_t brightness_value);
    void setLedsOn() const;
    void setLedsOff() const;

    void setLedsFromPersistentStates();
    void initLedFromPersistentState();
    void saveColorsToPersistentState(uint8_t segment_index,
                                     uint8_t *raw_buffer);

   private:
    LedController() = delete;
    boolean getLedsColorsFromPersistentState();
    u_int8_t _saved_brightness;
    CRGBArray<LED_COUNT> &_leds;
    std::vector<CRGBSet> &_segments;
};
