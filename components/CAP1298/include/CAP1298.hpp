#ifndef CAP1298_H
#define CAP1298_H

#include "I2CController.hpp"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <esp_err.h>


// CAP1298 I2C address
#define CAP1298_I2C_ADDRESS (uint8_t)(0x28)

// CAP1298 registers (see datasheet)
#define CAP1298_MAIN_CONTROL 0x00
#define CAP1298_GENERAL_STATUS 0x02
#define CAP1298_INPUT_STATUS 0x03
#define CAP1298_NOISE_FLAG_STATUS 0x0A
#define CAP1298_SENSOR_INPUT1_DELTA_COUNT_BASE 0x10
#define CAP1298_SENSOR_INPUT2_DELTA_COUNT_BASE 0x11
#define CAP1298_SENSOR_INPUT3_DELTA_COUNT_BASE 0x12
#define CAP1298_SENSOR_INPUT4_DELTA_COUNT_BASE 0x13
#define CAP1298_SENSOR_INPUT5_DELTA_COUNT_BASE 0x14
#define CAP1298_SENSOR_INPUT6_DELTA_COUNT_BASE 0x15
#define CAP1298_SENSOR_INPUT7_DELTA_COUNT_BASE 0x16
#define CAP1298_SENSOR_INPUT8_DELTA_COUNT_BASE 0x17
#define CAP1298_SENSITIVITY_CONTROL 0x1F
#define CAP1298_CONFIG1 0x20
#define CAP1298_INPUT_ENABLE 0x21
#define CAP1298_INPUT_CONFIG 0x22
#define CAP1298_INPUT_CONFIG2 0x23
#define CAP1298_AVERAGING_AND_SAMPLING_CONFIG 0x24
#define CAP1298_CALIBRATION_ACTIVATE 0x26
#define CAP1298_INTERRUPT_ENABLE 0x27
#define CAP1298_REPEAT_RATE_ENABLE 0x28
#define CAP1298_SIGNAL_GUARD 0x29
#define CAP1298_MULTIPLE_TOUCH_CONFIG 0x2A
#define CAP1298_MULTIPLE_TOUCH_PATTERN_CONFIG 0x2B
#define CAP1298_MULTIPLE_TOUCH_PATTERN 0x2D
#define CAP1298_BASE_COUNT_OUT 0x2C
#define CAP1298_RECALIBRATION_CONFIG 0x2F
#define CAP1298_INT_MASK 0x01

#define CAP1298_PRODUCT_ID 0xFD
#define CAP1298_MANUFACTURER_ID 0xFE
#define CAP1298_REVISION 0xFF
#define CAP1298_MANUFACTURER_ID_VALUE 0x5D
#define CAP1298_PRODUCT_ID_VALUE 0x71
#define CAP1298_REVISION_VALUE 0x00

class CAP1298
{
private:
    /* data */
    I2CController *busController;
    uint8_t m_touchData = 0;
    uint8_t m_newTouches = 0;
    uint8_t m_newReleases = 0;
public:
    CAP1298(gpio_num_t sda, gpio_num_t scl, uint32_t freq = 100000, uint8_t address = CAP1298_I2C_ADDRESS);
    ~CAP1298();
    esp_err_t begin();
    esp_err_t setupInterrupt(uint8_t channel);
    bool touchStatusChanged();
    void updateTouchStatus();
    uint8_t getNewTouches() { return m_newTouches; }
    uint8_t getNewReleases() { return m_newReleases; }
};

#endif // CAP1298_H
