

#pragma once

#include <FastLED.h>

#include <iostream>
#include <string>

#include "Constant.hpp"
#include "LedController.hpp"
#include "NimBLEDevice.h"
class StripCallBacks : public NimBLECharacteristicCallbacks {
   public:
    StripCallBacks(QueueHandle_t &cmdQueue);
    ~StripCallBacks();
    /*
     Can't copy the class because it contains references to external objects.
     Copying would leave those references bound to the old instance's data,
     leading to dangling references in the new copy.
    */
    StripCallBacks(StripCallBacks const &src) = delete;
    StripCallBacks &operator=(StripCallBacks const &rhs) = delete;

    void onWrite(NimBLECharacteristic *payload,
                 NimBLEConnInfo &connInfo) override;

   private:
    QueueHandle_t &_cmdQueue;
    StripCallBacks() = delete;

    bool isValidePayload(const NimBLEAttValue *payload) const;
};
