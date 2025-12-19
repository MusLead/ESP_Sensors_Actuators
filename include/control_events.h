// control_events.h
#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

extern EventGroupHandle_t control_event_group;

#define FAN_ON_BIT BIT0
#define WINDOW_OPEN_BIT BIT1
#define ABSORBER_ON_BIT BIT2
