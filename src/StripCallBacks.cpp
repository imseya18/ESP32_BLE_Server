#include "StripCallBacks.hpp"
#include "Constant.hpp"

StripCallBacks::StripCallBacks()
{

}

StripCallBacks::StripCallBacks(StripCallBacks const & src)
{
    *this = src;
}

StripCallBacks &     StripCallBacks::operator=(StripCallBacks const & rhs){
    if (this == &rhs) {
        return *this;
    }
    return *this;
}

StripCallBacks::~StripCallBacks()
{

}


void StripCallBacks::onWrite(NimBLECharacteristic* payload, NimBLEConnInfo& connInfo) {
        const NimBLEAttValue payload_value = payload->getValue();
        const uint16_t payload_size = payload_value.length();
        const uint8_t * raw_data = payload_value.data();
        if(!is_valide_payload(&payload_value))
        {
            Serial.printf("Not a valide Payload!\n");
            return;
        }
        for(int i = 0; i < payload_size; i++)
        {
            Serial.printf("%#02X,", raw_data[i]);
        }
        Serial.printf("\n");
        switch (raw_data[COMMAND_POS])
        {
        case LED_COLOR:
            Serial.printf("LED_COLOR Command trigered");
            break;
        
        case BRIGHTNESS:
            Serial.printf("BRIGHTNESS Command trigered");
            break;

        default:
            Serial.printf("Not a Valide Command");
            break;
        }
}

bool StripCallBacks::is_valide_payload(const NimBLEAttValue* payload) const {
        if (payload->length() != PAYLOAD_SIZE)
            return false;
        const uint8_t* raw_data = payload->data();
        if(raw_data[0] != START_FLAG || raw_data[PAYLOAD_SIZE - 1] != END_FLAG)
            return false;
        return true;
}