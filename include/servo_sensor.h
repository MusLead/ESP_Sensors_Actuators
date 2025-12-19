#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <iot_servo.h>
#include <esp_err.h>

// SERVO CONFIG
#define SERVO_GPIO 23             // GPIO pin connected to the servo
extern volatile int window_state; // 0 = closed, 1 = open

esp_err_t servo_init(void);

void servo_task(void *pvParameters);
