#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
#include "tahu.pb.h"       // Sparkplug Protobuf
#include "pb_decode.h"     // Protobuf decoder
#include "pb_encode.h"
#include <inttypes.h>      // For PRIu64

#define MQTT_HOST "localhost"
#define MQTT_PORT 1883
#define TOPIC "spBv1.0/MyGroup/DBIRTH/MyNode/MyDevice"
#define METRIC_DATA_TYPE_FLOAT 9
#define METRIC_DATA_TYPE_INT32 2
void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
    printf("Message received on topic: %s\n", message->topic);

    // Decode payload
    org_eclipse_tahu_protobuf_Payload payload = org_eclipse_tahu_protobuf_Payload_init_default;
    pb_istream_t stream = pb_istream_from_buffer((uint8_t *)message->payload, message->payloadlen);

    if (!pb_decode(&stream, org_eclipse_tahu_protobuf_Payload_fields, &payload)) {
        fprintf(stderr, "Failed to decode payload\n");
        return;
    }

    // Print decoded payload data
    printf("Timestamp: %" PRIu64 "\n", payload.timestamp);
    for (int i = 0; i < payload.metrics_count; i++) {
        printf("Metric: %s, Datatype: %d\n", payload.metrics[i].name, payload.metrics[i].datatype);
        // if (payload.metrics[i].datatype == METRIC_DATA_TYPE_INT32) {
            printf("Value (Int32): %d\n", payload.metrics[i].value.int_value);
        // }

    }
}

int main() {
    struct mosquitto *mosq = NULL;

    // Initialize the Mosquitto library
    mosquitto_lib_init();

    // Create a new Mosquitto client
    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Error: Out of memory.\n");
        return EXIT_FAILURE;
    }

    // Set the message callback
    mosquitto_message_callback_set(mosq, on_message);

    // Connect to the MQTT broker
    if (mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60)) {
        fprintf(stderr, "Failed to connect to broker\n");
        return EXIT_FAILURE;
    }

    // Subscribe to the topic
    mosquitto_subscribe(mosq, NULL, TOPIC, 0);
    printf("Subscribed to topic: %s\n", TOPIC);

    // Loop forever to receive messages
    mosquitto_loop_forever(mosq, -1, 1);

    // Cleanup
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return EXIT_SUCCESS;
}
