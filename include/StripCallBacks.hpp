

#pragma once

#include <string>
#include <iostream>
#include "NimBLEDevice.h"
class StripCallBacks : public NimBLECharacteristicCallbacks
{
    public:
        StripCallBacks();
        StripCallBacks(StripCallBacks const & src);
        ~StripCallBacks();
        StripCallBacks &     operator=(StripCallBacks const & rhs);
        
        void onWrite(NimBLECharacteristic* payload, NimBLEConnInfo& connInfo) override;
    private:
        bool is_valide_payload(const NimBLEAttValue* payload) const;

};

