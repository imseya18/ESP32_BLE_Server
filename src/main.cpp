#include <Arduino.h>
#include "NimBLEDevice.h"
#include "Constant.hpp"
#include "StripCallBacks.hpp"
#include <FastLED.h>

CRGBArray<LED_COUNT> leds;
std::vector<CRGBSet> segments;

void initLed() {
    Serial.println("LED initialization");
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
    FastLED.setCorrection(TypicalLEDStrip);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 4000);
    for(int i = 0; i < SEGMENT_NUMBER; i++){
        uint8_t start = i * SEGMENT_SIZE;
        uint8_t end = start + SEGMENT_SIZE - 1;
        segments.push_back(leds(start, end));
    }
    Serial.println("LED Ready");
}

void initBle() {
    Serial.println("BLE initialization");
    NimBLEDevice::init("WitekioLed");
    NimBLEServer *pServer = NimBLEDevice::createServer();
    NimBLEService *pService = pServer->createService(UUID_SERVICE);
    NimBLECharacteristic *pCharacteristic = pService->createCharacteristic(UUID_LED_COLOR, NIMBLE_PROPERTY::WRITE_NR);
    pServer->addService(pService);
    pService->addCharacteristic(pCharacteristic);
    pCharacteristic->setCallbacks(new StripCallBacks());
    pService->start();
    pServer->getAdvertising()->addServiceUUID(UUID_SERVICE);
    pServer->getAdvertising()->setName("WitekioLed");
    pServer->getAdvertising()->start();
    Serial.println("BLE Ready");
}

void setup() {
    Serial.begin(115200);
    initBle();
    initLed();
}

void loop() {
  // put your main code here, to run repeatedly:
delay(1000);
}
