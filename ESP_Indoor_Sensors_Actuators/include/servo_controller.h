#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <iot_servo.h>
#include <stdbool.h>

// GPIO PINS
#define SERVO_WINDOW1_GPIO 23     // Window servo 1 – normal (0° <--> 90°)
#define SERVO_WINDOW2_GPIO 18     // Window servo 2 – inverted (90° <--> 0°)
#define SERVO_DOOR_INDOOR_GPIO 26 // Door servo indoor – normal (0° <--> 90°)

// STATES
extern bool window_state;      // false=closed, true=open
extern bool door_indoor_state; // false=closed, true=open

esp_err_t servo_init(void);
void servo_start_task(void *pvParameters);