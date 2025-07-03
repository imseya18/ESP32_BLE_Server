#pragma once

#include "NimBLEDevice.h"

//BLE UUID
static const NimBLEUUID UUID_SERVICE("d0d02988-9d8c-41e1-abbc-c1587419475d");
static const NimBLEUUID UUID_LED_COLOR("b18d531d-0d2e-4315-b253-677c0b9bdf72");



//PAYLOAD STRUCTURE = [STARTFLAG, SEGMENT_NUMBER, GREEN, RED, BLUE, COMMAND, ENDFLAG]
//PAYLOAD
static constexpr uint8_t START_FLAG = 0x38;
static constexpr uint8_t END_FLAG = 0x83;
static constexpr uint8_t PAYLOAD_SIZE = 7;
static constexpr uint8_t COMMAND_POS = 5;
//COMMANDE HEX

#define LED_COLOR 0x01
#define BRIGHTNESS 0x02

//LED STRIP
static constexpr uint8_t LED_PIN   = 48;
static constexpr uint16_t LED_COUNT = 60;
static constexpr uint8_t SEGMENT_NUMBER = 15; // Equal to number of card spot on the testbench
static constexpr uint8_t SEGMENT_SIZE = LED_COUNT / SEGMENT_NUMBER;