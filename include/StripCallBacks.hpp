

#pragma once

#include <string>
#include <iostream>
#include "NimBLEDevice.h"
#include <FastLED.h>
#include "Constant.hpp"
#include "LedController.hpp"
class StripCallBacks : public NimBLECharacteristicCallbacks
{
    public:
        StripCallBacks(LedController& led_controller);
        ~StripCallBacks();
        /*
         Can't copy the class because it contains references to external objects.
         Copying would leave those references bound to the old instance's data,
         leading to dangling references in the new copy.
        */
        StripCallBacks(StripCallBacks const & src) = delete;
        StripCallBacks &     operator=(StripCallBacks const & rhs) = delete;
        
        void onWrite(NimBLECharacteristic* payload, NimBLEConnInfo& connInfo) override;
    private:
      LedController& _led_controller;
      StripCallBacks() = delete;

      bool is_valide_payload(const NimBLEAttValue* payload) const;

};

