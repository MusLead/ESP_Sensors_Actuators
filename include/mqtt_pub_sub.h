#pragma once

// MQTT BROKER ADDRESS
// TODO: Replace with your ESP32 IP address
#define MQTT_ADDR_URL "mqtt://10.249.73.216:1883"

void mqtt_pubsub_start(void);
void mqtt_publish(const char *topic, const char *msg, int qos);
void mqtt_subscribe(const char *topic, int qos);