#include "LedController.hpp"

#include "esp_log.h"

static const char *TAG = "LedController";
LedController::LedController(CRGBArray<LED_COUNT> &ledsRef,
                             std::vector<CRGBSet> &segmentsRef)
    : _leds(ledsRef), _segments(segmentsRef), _saved_brightness(255) {}

LedController::~LedController() {}

void LedController::setLedColor(uint8_t segment_index, CRGB rgbval) const {
    _segments[segment_index].fill_solid(rgbval);
    FastLED.show();
    ESP_LOGD(TAG, "Color set to: R:%i G:%i B:%i on segment: %i", rgbval.r,
             rgbval.g, rgbval.b, segment_index);
}

void LedController::setBrightness(uint8_t brightness_value) {
    _saved_brightness = brightness_value;
    FastLED.setBrightness(brightness_value);
    FastLED.show();
    ESP_LOGD(TAG, "Brightness set to: %i", brightness_value);
}

void LedController::setLedsOn() const {
    FastLED.setBrightness(_saved_brightness);
    FastLED.show();
}

void LedController::setLedsOff() const {
    FastLED.setBrightness(0);
    FastLED.show();
}
