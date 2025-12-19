#pragma once
#define GPIO_ABSORBER 26

extern volatile int absorber_state; // 0 = off, 1 = on

void absorber_task(void *pvParameters);