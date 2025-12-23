// ----
// FINAL IMPLEMENTATION WITH ALL COMPONENTS
#include "esp_log.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "wifi.h"
#include "mqtt_pub_sub.h"

#include "i2c_bus.h"
#include "bme680_sensor.h"
#include "anemometer.h"

#include "relay_switch.h"
#include "servo_door_sensor.h"

static const char *TAG = "OUTDOOR_MAIN";

void app_main(void)
{
    // 1 System Info
    ESP_LOGI(TAG, "System start");
    ESP_LOGI(TAG, "Free heap: %lu", esp_get_free_heap_size());
    ESP_LOGI(TAG, "IDF version: %s", esp_get_idf_version());

    // 2 Always initialize the default NVS partition first
    nvs_flash_init();

    // 3 WiFi
    connect_wifi();

    // 4 Start MQTT (connect + subscribe + auto publish logic preserved)
    mqtt_pubsub_start();

    //
    // 5 INIT THE I2C componennt
    ESP_ERROR_CHECK(i2c_bus_init());
    //
    // ...

    //
    // 6 SENSORS INIT
    ESP_ERROR_CHECK(bme680_sensor_init());

    // SERVO INIT
    ESP_ERROR_CHECK(servo_init());

    //
    // 7 At the end create a task from the sensor
    // BME680 TASK
    xTaskCreate(bme680_read_task, "outdoor_bme680_task", 4096, NULL, 3, NULL);
    // ANEMOMETER TASK
    xTaskCreate(anemometer_task, "outdoor_anemometer_task", 3072, NULL, 4, NULL);
    // RELAY SWITCH TASK
    xTaskCreate(relay_start_task, "outdoor_relay_task", 2048, NULL, 2, NULL);
    // SERVO TASK
    xTaskCreate(servo_start_task, "outdoor_servo_door_task", 2048, NULL, 2, NULL);

    ESP_LOGI(TAG, "System initialized successfully");
}
// ----