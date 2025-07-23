#include "LedController.hpp"

#include <Preferences.h>

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

void LedController::setLedsFromPersistentStates() {
    for (uint8_t i = 0; i < persistent_rgb_value.size(); i++) {
        CRGB rgbval(persistent_rgb_value[i][0], persistent_rgb_value[i][1],
                    persistent_rgb_value[i][2]);
        setLedColor(i, rgbval);
    }
}

boolean LedController::getLedsColorsFromPersistentState() {
    persistent_state.begin(STORE_NAME, true);
    bool key = persistent_state.isKey(STORE_LEDS_KEY);
    if (key) {
        persistent_state.getBytes(
            STORE_LEDS_KEY, persistent_rgb_value.data(),
            SEGMENT_NUMBER * sizeof(std::array<u_int8_t, 3>));
    } else {
        ESP_LOGD(TAG, "key: %s not found", STORE_LEDS_KEY);
    }
    persistent_state.end();
    return key;
}

void LedController::initLedFromPersistentState() {
    if (!getLedsColorsFromPersistentState()) return;
    setLedsFromPersistentStates();
}

void LedController::saveColorsToPersistentState(uint8_t segment_index,
                                                uint8_t *raw_buffer) {
    persistent_rgb_value[segment_index] = {raw_buffer[RED_VALUE_POS],
                                           raw_buffer[GREEN_VALUE_POS],
                                           raw_buffer[BLUE_VALUE_POS]};
    persistent_state.begin(STORE_NAME, false);
    persistent_state.putBytes(
        STORE_LEDS_KEY, persistent_rgb_value.data(),
        (SEGMENT_NUMBER * sizeof(std::array<uint8_t, 3>)));
    persistent_state.end();
}