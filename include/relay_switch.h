#pragma once
#define GPIO_RELAY 18

extern volatile int fan_state; // 0 = off, 1 = on

void relay_task(void *pvParameters);