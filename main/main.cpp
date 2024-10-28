#include <CAP1298.hpp>
#include "esp_log.h"
#include <stdio.h>

// #define UNIT_TEST

#ifdef UNIT_TEST
#include "unity.h"

CAP1298 touch_sensor(GPIO_NUM_1, GPIO_NUM_0);

/**
 * @brief The test case checks if the CAP1298 object is created successfully
 * 
 */
TEST_CASE("CAP1298 initialization", "[CAP1298]")
{
    CAP1298* cap_driver = new CAP1298(GPIO_NUM_1, GPIO_NUM_0);
    TEST_ASSERT_NOT_NULL(cap_driver);
    delete cap_driver;
}

TEST_CASE("CAP1298 initialization failed", "[CAP1298]")
{
    CAP1298* cap_driver = new CAP1298(GPIO_NUM_1, GPIO_NUM_1);
    TEST_ASSERT_EQUAL(ESP_ERR_INVALID_ARG, cap_driver->getFlag());
    delete cap_driver;
}

TEST_CASE("CAP1298 begin", "[CAP1298]")
{
    CAP1298* cap_driver = new CAP1298(GPIO_NUM_1, GPIO_NUM_0);
    TEST_ASSERT_EQUAL(ESP_OK, cap_driver->begin());
    delete cap_driver;
}

TEST_CASE("CAP1298 touchStatusChanged", "[CAP1298]")
{
    CAP1298* cap_driver = new CAP1298(GPIO_NUM_1, GPIO_NUM_0);
    TEST_ASSERT_EQUAL(ESP_OK, cap_driver->begin());
    TEST_ASSERT_FALSE(cap_driver->touchStatusChanged());
    delete cap_driver;
}

#endif

CAP1298 cap_driver(GPIO_NUM_1, GPIO_NUM_0);

extern "C" void app_main(void)
{
    #ifdef UNIT_TEST
        UNITY_BEGIN();
        unity_run_test_by_name("CAP1298 initialization");
        unity_run_test_by_name("CAP1298 initialization failed");
        unity_run_test_by_name("CAP1298 begin");
        UNITY_END();
    #endif

    esp_err_t ret = cap_driver.begin();

    ret = cap_driver.setupInterrupt(2);

    if (ret != ESP_OK)
    {
        ESP_LOGE("CAP1298", "CAP1298 initialization failed");
    }
    else
    {
        ESP_LOGI("CAP1298", "CAP1298 initialization successful");
    }

    // while(1) {
    //     if (cap_driver.touchStatusChanged())
    //     {
    //         cap_driver.updateTouchStatus();
    //         ESP_LOGI("CAP1298", "New touches: %d", cap_driver.getNewTouches());
    //         ESP_LOGI("CAP1298", "New releases: %d", cap_driver.getNewReleases());
    //     }
    //     vTaskDelay(100 / portTICK_PERIOD_MS);
    // }
}
