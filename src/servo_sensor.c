#include "servo_sensor.h"
#include "esp_log.h"
#include "control_events.h"

static const char *TAG = "Servo_Task";

volatile int window_state = 0;

// Servo Initialization
esp_err_t servo_init(void)
{
    servo_config_t servo_cfg = {
        .max_angle = 180,
        .min_width_us = 500,
        .max_width_us = 2500,
        .freq = 50,
        .timer_number = LEDC_TIMER_0,
        .channels = {
            .servo_pin = {SERVO_GPIO},
            .ch = {LEDC_CHANNEL_0},
        },
        .channel_number = 1,
    };

    esp_err_t res = iot_servo_init(LEDC_LOW_SPEED_MODE, &servo_cfg);
    if (res != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize servo: %s", esp_err_to_name(res));
        return res;
    }

    ESP_LOGI(TAG, "Servo initialized successfully on GPIO %d", SERVO_GPIO);
    return ESP_OK;
}

// Servo Control Task
void servo_task(void *pvParameters)
{
    int last_state = -1;

    while (1)
    {
        EventBits_t bits = xEventGroupGetBits(control_event_group);
        int open = bits & WINDOW_OPEN_BIT;

        if (open != last_state)
        {
            iot_servo_write_angle(
                LEDC_LOW_SPEED_MODE,
                0,
                open ? 90 : 0);
            last_state = open;
        }

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}
