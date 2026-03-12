#include "servo_controller.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "Servo_Controller";

bool window_state = false;
bool door_indoor_state = false;

esp_err_t servo_init(void)
{
    servo_config_t servo_cfg = {
        .max_angle = 180,
        .min_width_us = 500,
        .max_width_us = 2500,
        .freq = 50,
        .timer_number = LEDC_TIMER_0,
        .channels = {
            .servo_pin = {SERVO_WINDOW1_GPIO, SERVO_WINDOW2_GPIO, SERVO_DOOR_INDOOR_GPIO},
            .ch = {LEDC_CHANNEL_0, LEDC_CHANNEL_1, LEDC_CHANNEL_2},
        },
        .channel_number = 3,
    };

    esp_err_t res = iot_servo_init(LEDC_LOW_SPEED_MODE, &servo_cfg);
    if (res != ESP_OK)
    {
        ESP_LOGE(TAG, "Servo init failed: %s", esp_err_to_name(res));
        return res;
    }

    ESP_LOGI(TAG, "3 Servos initialized (GPIO %d, %d, %d)",
             SERVO_WINDOW1_GPIO, SERVO_WINDOW2_GPIO, SERVO_DOOR_INDOOR_GPIO);
    return ESP_OK;
}

void servo_start_task(void *pvParameters)
{
    ESP_LOGI(TAG, "Servo task started");
    while (1)
    {
        // Window 1 – normal: closed=0°, open=90°
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, 0, window_state ? 90 : 0);

        // Window 2 – inverted: closed=90°, open=0°
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, 1, window_state ? 0 : 90);

        // Door indoor – normal: closed=0°, open=90°
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, 2, door_indoor_state ? 90 : 0);

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}