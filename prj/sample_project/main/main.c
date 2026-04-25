#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/projdefs.h"

void app_main(void)
{
    while (1) {
        ESP_LOGI("main", "helloworld");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
