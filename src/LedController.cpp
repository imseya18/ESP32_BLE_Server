#include "LedController.hpp"

LedController::LedController(CRGBArray<LED_COUNT> &ledsRef, std::vector<CRGBSet> &segmentsRef) : _leds(ledsRef), _segments(segmentsRef), _saved_brightness(255)
{
}


LedController::~LedController()
{

}

void LedController::setLedColor(u_int8_t segment_index, CRGB rgbval)
{
     _segments[segment_index].fill_solid(rgbval);
     FastLED.show();
}

void LedController::setBrightness(u_int8_t brightness_value)
{
    _saved_brightness = brightness_value;
    FastLED.setBrightness(brightness_value);
    FastLED.show();
}

void LedController::setLedsOn()
{
    FastLED.setBrightness(_saved_brightness);
}

void LedController::setLedsOff()
{
    FastLED.setBrightness(0);
}
