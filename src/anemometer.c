// anemometer.c
#include "anemometer.h"
#include "mqtt_pub_sub.h"
#include "esp_timer.h"

static volatile uint32_t pulse_count = 0;
static portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

static void IRAM_ATTR anemometer_isr(void *arg)
{
    portENTER_CRITICAL_ISR(&mux);
    pulse_count++;
    portEXIT_CRITICAL_ISR(&mux);
}

void anemometer_task(void *pvParameters)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << SENSOR_PIN),
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_POSEDGE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE};

    gpio_config(&io_conf);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(SENSOR_PIN, anemometer_isr, NULL);

    char msg[32];

    while (1)
    {
        uint32_t pulses;

        portENTER_CRITICAL(&mux);
        pulses = pulse_count;
        pulse_count = 0;
        portEXIT_CRITICAL(&mux);

        float wind_speed = (float)pulses * 2.4f; // 1 Sekunde Messzeit

        snprintf(msg, sizeof(msg), "%.2f", wind_speed);
        mqtt_publish("ESP32/wind", msg, 1);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}