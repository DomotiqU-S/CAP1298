#include <CAP1298.hpp>
#include "esp_log.h"
#include <stdio.h>

CAP1298 cap_driver(GPIO_NUM_1, GPIO_NUM_0);

void readTouchStatus(void * pvParameters)
{
    while(1) {
        if (cap_driver.touchStatusChanged())
        {
            cap_driver.updateTouchStatus();
            ESP_LOGI("CAP1298", "New touches: %d", cap_driver.getNewTouches());
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

extern "C" void app_main(void)
{
    esp_err_t ret = cap_driver.begin();
    if (ret == ESP_OK)
    {
        ESP_LOGI("CAP1298", "CAP1298 initialized");
    }
    else
    {
        ESP_LOGE("CAP1298", "CAP1298 initialization failed");
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    xTaskCreate(readTouchStatus, "readTouchStatus", 1024, NULL, 5, NULL);
}
