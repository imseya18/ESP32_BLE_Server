

#pragma once

#include <string>
#include <iostream>
#include "NimBLEDevice.h"
#include <FastLED.h>
#include "Constant.hpp"

class StripCallBacks : public NimBLECharacteristicCallbacks
{
    public:
        StripCallBacks(CRGBArray<LED_COUNT>& ledsRef, std::vector<CRGBSet>& segmentsRef);
        ~StripCallBacks();
        StripCallBacks(StripCallBacks const & src) = delete;
        StripCallBacks &     operator=(StripCallBacks const & rhs) = delete;
        
        void onWrite(NimBLECharacteristic* payload, NimBLEConnInfo& connInfo) override;
    private:
      CRGBArray<LED_COUNT>& _leds;
      std::vector<CRGBSet>& _segments;
      StripCallBacks() = delete;

      bool is_valide_payload(const NimBLEAttValue* payload) const;

};

