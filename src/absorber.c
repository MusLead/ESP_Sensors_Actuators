#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <esp_log.h>
#include "absorber.h"
#include "control_events.h"
#include "esp_log.h"

volatile int absorber_state = 0;

// ABSORBER TASK
void absorber_task(void *pvParameters)
{
    gpio_set_direction(GPIO_ABSORBER, GPIO_MODE_OUTPUT);

    while (1)
    {
        EventBits_t bits = xEventGroupGetBits(control_event_group);
        gpio_set_level(GPIO_ABSORBER, (bits & ABSORBER_ON_BIT));
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}