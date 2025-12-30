#pragma once

// MQTT BROKER ADDRESS
// Adjust the IP address as per your MQTT broker location
#define MQTT_ADDR_URL "mqtt://192.168.0.220:1883"

void mqtt_pubsub_start(void);
void mqtt_publish(const char *topic, const char *msg, int qos);
void mqtt_subscribe(const char *topic, int qos);