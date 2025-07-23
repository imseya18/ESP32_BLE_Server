#include <Arduino.h>
#include <FastLED.h>
#include <Preferences.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#include "Constant.hpp"
#include "NimBLEDevice.h"
#include "StripCallBacks.hpp"

static CRGBArray<LED_COUNT> leds;
static std::vector<CRGBSet> segments;
static QueueHandle_t cmdQueue = nullptr;
static StripCallBacks stripCB(cmdQueue);
static LedController led_controller(leds, segments);
static const char *TAG = "Main";
// size of 3 to represente each RGB value
std::vector<std::array<u_int8_t, 3>> persistent_rgb_value(SEGMENT_NUMBER,
                                                          {0, 0, 0});
Preferences persistent_state;

void initLed() {
    ESP_LOGD(TAG, "LED initialization");
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
    FastLED.setCorrection(TypicalLEDStrip);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 4000);
    for (int i = 0; i < SEGMENT_NUMBER; i++) {
        uint8_t start = i * SEGMENT_SIZE;
        uint8_t end = start + SEGMENT_SIZE - 1;
        segments.push_back(leds(start, end));
    }
    led_controller.initLedFromPersistentState();
    ESP_LOGD(TAG, "LED Ready");
}

void initBle() {
    ESP_LOGD(TAG, "BLE initialization");
    NimBLEDevice::init("WitekioLed");
    NimBLEServer *pServer = NimBLEDevice::createServer();
    pServer->advertiseOnDisconnect(true);
    NimBLEService *pService = pServer->createService(UUID_SERVICE);
    NimBLECharacteristic *pCharacteristic = pService->createCharacteristic(
        UUID_LED_COLOR, NIMBLE_PROPERTY::WRITE_NR);
    pServer->addService(pService);
    pService->addCharacteristic(pCharacteristic);
    cmdQueue = xQueueCreate(30, PAYLOAD_SIZE);
    if (cmdQueue == nullptr) {
        ESP_LOGE(TAG, "Queue Creation Failed");
        while (true);
    }
    pCharacteristic->setCallbacks(&stripCB);
    pService->start();
    pServer->getAdvertising()->addServiceUUID(UUID_SERVICE);
    pServer->getAdvertising()->enableScanResponse(true);
    pServer->getAdvertising()->setName("WitekioLed");
    pServer->getAdvertising()->start();
    ESP_LOGD(TAG, "BLE Ready");
}

void setup() {
    Serial.begin(115200);
    initLed();
    initBle();
}

void loop() {
    uint8_t raw_buffer[PAYLOAD_SIZE];
    while (xQueueReceive(cmdQueue, raw_buffer, pdMS_TO_TICKS(20)) == pdTRUE) {
        ESP_LOGD(TAG, "queue commande received");
        switch (raw_buffer[COMMAND_POS]) {
            case LED_COLOR: {
                ESP_LOGD(TAG, "LED_COLOR Command trigered");
                u_int8_t segment_index = raw_buffer[SEGMENT_POS];
                CRGB rgbval(raw_buffer[RED_VALUE_POS],
                            raw_buffer[GREEN_VALUE_POS],
                            raw_buffer[BLUE_VALUE_POS]);
                led_controller.setLedColor(segment_index, rgbval);
                led_controller.saveColorsToPersistentState(segment_index,
                                                           raw_buffer);
                break;
            }
            case BRIGHTNESS: {
                ESP_LOGD(TAG, "BRIGHTNESS Command trigered");
                led_controller.setBrightness(raw_buffer[BRIGHTNESS_POS]);
                break;
            }
            case LED_ON: {
                ESP_LOGD(TAG, "LED_ON Command trigered");
                led_controller.setLedsOn();
                break;
            }
            case LED_OFF: {
                ESP_LOGD(TAG, "LED_OFF Command trigered");
                led_controller.setLedsOff();
                break;
            }
            default: {
                ESP_LOGW(TAG, "Not a valid command");
                break;
            }
        }
    }
    FastLED.show();
}