#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <iot_servo.h>
#include <stdbool.h>

// SERVO CONFIG
#define SERVO_DOOR_GPIO 23 // GPIO pin connected to the servo
extern bool door_state;    // false = closed, true = open

esp_err_t servo_init(void);

void servo_start_task(void *pvParameters);
