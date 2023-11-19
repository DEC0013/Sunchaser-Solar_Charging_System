#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include "PubSubClient.h"
#include <ArduinoJson.h>
#include <DateTime.h>
#include <ESPDateTime.h>
class Communicator
{
public:
    volatile bool is_server = false;
    const int interrupt_pin = 33;

private:
    const char *_ssid_wifi_to_connect = "RFS-S21FE";
    const char *_password_wifi_to_connect = "23011306";
    HTTPClient _http_client;

    const char *_ssid_wifi_ap = "ESP32_SUNCHASER";
    const char *_password_wifi_ap = NULL;
    WebServer _web_server;

    volatile bool _rise_flag = false;
    volatile bool _fall_flag = false;

    const char *mqtt_server = "your_mqtt_broker_address";
    const int mqtt_port = 1883; // Default MQTT port
    WiFiClient _esp_client;
    PubSubClient _mqtt_client;

public:
    Communicator();
    void init();
    void attach_interruption();
    void interrupt_handler();
    void check_flags();
    static void IRAM_ATTR on_interruption();
    void run_server();
    void check_connection();
    void mqtt_reconnect();
    void mqtt_subscribe(const char *topic);
    void mqtt_publish(const char *topic, const char *message);
    void mqtt_callback(char *topic, byte *payload, unsigned int length);
    void setup_datetime();
    void mqtt_loop();
    bool check_interruption_flag();

private:
    void _setup_mqtt();
    void _notify_rise_edge();
    void _notify_fall_edge();
    void _setup_wifi_client();
    void _setup_wifi_ap();
    void _stop_ap();
    void _wifi_ap_config();
    void _handle_root();
    void _handle_get_cache();
    ;
};

#endif // COMMUNICATOR_H
