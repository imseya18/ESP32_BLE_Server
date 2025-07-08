#include "StripCallBacks.hpp"
#include "Constant.hpp"
#include "FastLED.h"
#include "esp_log.h"

static const char* TAG = "SripCB";

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
            ESP_LOGW(TAG, "Invalid payload");
            return;
        }
        switch (raw_data[COMMAND_POS])
        {
            case LED_COLOR: {
                ESP_LOGD(TAG ,"LED_COLOR Command trigered");
                u_int8_t segment_index = raw_data[SEGMENT_POS];
                CRGB rgbval(raw_data[RED_VALUE_POS],raw_data[GREEN_VALUE_POS], raw_data[BLUE_VALUE_POS]);
                _led_controller.setLedColor(segment_index, rgbval);
                break;
            }
            case BRIGHTNESS: {
                ESP_LOGD(TAG ,"BRIGHTNESS Command trigered");
                _led_controller.setBrightness(raw_data[BRIGHTNESS_POS]);
                break;
            }
            case LED_ON: {
                ESP_LOGD(TAG ,"LED_ON Command trigered");
                _led_controller.setLedsOn();
                break;
            }
            case LED_OFF:{
                ESP_LOGD(TAG ,"LED_OFF Command trigered");
                _led_controller.setLedsOff();
                break;
            }
            default:{
                ESP_LOGW(TAG ,"Not a valid command");
                break;
            }
        }
}

bool StripCallBacks::is_valide_payload(const NimBLEAttValue* payload) const {
        if (payload->length() != PAYLOAD_SIZE){
            ESP_LOGD(TAG, "Invalid payload length=%u", payload->length());
            return false;
        }
        const uint8_t* raw_data = payload->data();
        if(raw_data[0] != START_FLAG || raw_data[PAYLOAD_SIZE - 1] != END_FLAG){
            ESP_LOGD(TAG, "Invalid payload Flag");
            return false;
        }
        if(raw_data[SEGMENT_POS] < 0 || raw_data[SEGMENT_POS] > SEGMENT_NUMBER){
            ESP_LOGD(TAG, "Invalid Segment Value");
            return false;
        }
        return true;
}