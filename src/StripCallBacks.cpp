#include "StripCallBacks.hpp"
#include "Constant.hpp"
#include "FastLED.h"
#include "esp_log.h"

static const char* TAG = "SripCB";


StripCallBacks::StripCallBacks(QueueHandle_t& cmdQueue) : _cmdQueue(cmdQueue)
{
}

StripCallBacks::~StripCallBacks()
{

}

void StripCallBacks::onWrite(NimBLECharacteristic* payload, NimBLEConnInfo& connInfo) {
        const NimBLEAttValue payload_value = payload->getValue();
        const uint16_t payload_size = payload_value.length();
        const uint8_t * raw_data = payload_value.data();
        if(!isValidePayload(&payload_value))
        {
            ESP_LOGW(TAG, "Invalid payload");
            return;
        }
        xQueueSend(_cmdQueue, raw_data, 0);
}

bool StripCallBacks::isValidePayload(const NimBLEAttValue* payload) const {
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