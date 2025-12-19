#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <esp_log.h>
#include "relay_switch.h"
#include "control_events.h"

volatile int fan_state = 0;

// RELAY SWITCH TASK
void relay_task(void *pvParameters)
{
    gpio_set_direction(GPIO_RELAY, GPIO_MODE_OUTPUT);

    while (1)
    {
        EventBits_t bits = xEventGroupGetBits(control_event_group);
        gpio_set_level(GPIO_RELAY, (bits & FAN_ON_BIT));
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}