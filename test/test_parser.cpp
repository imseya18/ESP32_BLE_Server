#include <unity.h>
#include "StripCallBacks.hpp"


std::vector<uint8_t> valide_payload_raw = {
  START_FLAG,           
  0x02,           
  0x10, 0x20, 0x30, 
  0x01,           
  END_FLAG            
};

std::vector<uint8_t> too_long_payload_raw = {
  START_FLAG,           
  0x02,           
  0x10, 0x20, 0x30, 
  0x01,           
  END_FLAG,
  0x01            
};

std::vector<uint8_t> too_short_payload_raw = {
  START_FLAG,           
  0x02,           
  0x10, 0x20, 0x30,           
  END_FLAG,          
};

std::vector<uint8_t> wrong_segment_value_raw = {
  START_FLAG,           
  SEGMENT_NUMBER + 1,           
  0x10, 0x20, 0x30,
  0x01,            
  END_FLAG,          
};

std::vector<uint8_t> wrong_start_flag_value_raw = {
  START_FLAG + 1,           
  SEGMENT_NUMBER + 1,           
  0x10, 0x20, 0x30,
  0x01,            
  END_FLAG,          
};

std::vector<uint8_t> wrong_end_flag_value_raw = {
  START_FLAG,           
  SEGMENT_NUMBER + 1,           
  0x10, 0x20, 0x30,
  0x01,            
  END_FLAG + 1,          
};

bool is_valide_payload(const NimBLEAttValue* payload) {
        if(!payload)
            return false;
        if (payload->length() != PAYLOAD_SIZE)
            return false;
        const uint8_t* raw_data = payload->data();
        if(raw_data[0] != START_FLAG || raw_data[PAYLOAD_SIZE - 1] != END_FLAG)
            return false;
        if(raw_data[SEGMENT_POS] < 0 || raw_data[SEGMENT_POS] > SEGMENT_NUMBER)
            return false;
        return true;
}


void test_valid_payload() {
  NimBLEAttValue valide_payload(valide_payload_raw); 
  TEST_ASSERT_EQUAL(true, is_valide_payload(&valide_payload));
}

void test_wrong_size_payload() {
  NimBLEAttValue too_long_payload(too_long_payload_raw);
  NimBLEAttValue too_short_payload(too_short_payload_raw);
  TEST_ASSERT_EQUAL(false, is_valide_payload(&too_long_payload));
  TEST_ASSERT_EQUAL(false, is_valide_payload(&too_short_payload));
}

void test_segment_pos(){
    NimBLEAttValue wrong_segment_value(wrong_segment_value_raw);
    TEST_ASSERT_EQUAL(false, is_valide_payload(&wrong_segment_value));
}

void test_null_payload() {
    TEST_ASSERT_EQUAL(false, is_valide_payload(nullptr));
}

void test_flag_value(){
    NimBLEAttValue wrong_start_flag_value(wrong_start_flag_value_raw);
    NimBLEAttValue wrong_end_flag_value(wrong_end_flag_value_raw);
    TEST_ASSERT_EQUAL(false, is_valide_payload(&wrong_start_flag_value));
    TEST_ASSERT_EQUAL(false, is_valide_payload(&wrong_end_flag_value));
}

void setup() {
  UNITY_BEGIN();
  RUN_TEST(test_valid_payload);
  RUN_TEST(test_wrong_size_payload);
  RUN_TEST(test_segment_pos);
  RUN_TEST(test_null_payload);
  RUN_TEST(test_flag_value);
  UNITY_END();
}

void loop() {}