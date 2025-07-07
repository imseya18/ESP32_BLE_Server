#include "StripCallBacks.hpp"
#include "Constant.hpp"
#include "FastLED.h"


StripCallBacks::StripCallBacks(LedController& led_controller) : _led_controller(led_controller)
{
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
            case LED_COLOR: {
                u_int8_t segment_index =raw_data[SEGMENT_POS];
                CRGB rgbval(raw_data[RED_VALUE_POS],raw_data[GREEN_VALUE_POS], raw_data[BLUE_VALUE_POS]);
                _led_controller.setLedColor(segment_index, rgbval);
                break;
            }
            case BRIGHTNESS: {
                Serial.printf("BRIGHTNESS Command trigered");
                _led_controller.setBrightness(raw_data[BRIGHTNESS_POS]);
                break;
            }
            case LED_ON: {
                _led_controller.setLedsOn();
            }
            case LED_OFF:{
                _led_controller.setLedsOff();
            }
            default:{
                Serial.printf("Not a Valide Command");
                break;
            }
        }
}

bool StripCallBacks::is_valide_payload(const NimBLEAttValue* payload) const {
        if (payload->length() != PAYLOAD_SIZE)
            return false;
        const uint8_t* raw_data = payload->data();
        if(raw_data[0] != START_FLAG || raw_data[PAYLOAD_SIZE - 1] != END_FLAG)
            return false;
        if(raw_data[SEGMENT_POS] < 0 || raw_data[SEGMENT_POS] > SEGMENT_NUMBER)
            return false;
        return true;
}