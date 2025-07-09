#pragma once

#include "NimBLEDevice.h"

//BLE UUID
static const NimBLEUUID UUID_SERVICE("d0d02988-9d8c-41e1-abbc-c1587419475d");
static const NimBLEUUID UUID_LED_COLOR("b18d531d-0d2e-4315-b253-677c0b9bdf72");



//PAYLOAD STRUCTURE = [STARTFLAG, SEGMENT_NUMBER, RED, GREEN, BLUE, COMMAND, ENDFLAG]
//PAYLOAD
constexpr uint8_t START_FLAG = 0x38;
constexpr uint8_t END_FLAG = 0x83;
constexpr uint8_t RED_VALUE_POS = 2;
constexpr uint8_t GREEN_VALUE_POS = 3;
constexpr uint8_t BLUE_VALUE_POS = 4;
constexpr uint8_t BRIGHTNESS_POS = 2;
constexpr uint8_t PAYLOAD_SIZE = 7;
constexpr uint8_t COMMAND_POS = 5;
constexpr uint8_t SEGMENT_POS = 1;
constexpr uint8_t QUEUE_LENGTH = 16;
//COMMANDE HEX
enum  cmd : uint8_t {
    LED_COLOR = 0x01,
    BRIGHTNESS = 0x02,
    LED_ON = 0x03,
    LED_OFF = 0x04,
};

//LED STRIP
constexpr uint8_t LED_PIN   = 16;
constexpr uint16_t LED_COUNT = 60;
constexpr uint8_t SEGMENT_NUMBER = 15; // Equal to number of card spot on the testbench
constexpr uint8_t SEGMENT_SIZE = LED_COUNT / SEGMENT_NUMBER;