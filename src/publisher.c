#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mosquitto.h>
#include "tahu.pb.h"   // Sparkplug Protobuf
#include "pb_encode.h"
#include "tahu.h"      // Custom helpers like get_next_payload, add_simple_metric

#define MQTT_HOST "localhost"
#define MQTT_PORT 1883
#define TOPIC "spBv1.0/MyGroup/DBIRTH/MyNode/MyDevice"

void publish_payload(struct mosquitto *mosq) {
    uint8_t buffer[256] = {0};
    size_t message_length;

    // Create payload
    org_eclipse_tahu_protobuf_Payload payload;
    get_next_payload(&payload);

    // Add a single metric to the payload
    uint32_t value = 42;  // Example value
    add_simple_metric(&payload, "temperature", false, 0, METRIC_DATA_TYPE_INT32, false, false, &value, sizeof(value));

    // Encode the payload into the buffer
    message_length = encode_payload(buffer, sizeof(buffer), &payload);

    // Publish payload
    int rc = mosquitto_publish(mosq, NULL, TOPIC, message_length, buffer, 0, false);
    if (rc == MOSQ_ERR_SUCCESS) {
        printf("Published payload to topic: %s\n", TOPIC);
    } else {
        fprintf(stderr, "Publish failed: %s\n", mosquitto_strerror(rc));
    }

    // Free payload memory
    free_payload(&payload);
}

int main() {
    struct mosquitto *mosq = NULL;

    mosquitto_lib_init();
    mosq = mosquitto_new(NULL, true, NULL);

    if (mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60)) {
        fprintf(stderr, "Failed to connect to broker\n");
        return EXIT_FAILURE;
    }

    publish_payload(mosq);

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return EXIT_SUCCESS;
}
