/* Link tutorial: https://www.mathworks.com/help/thingspeak/mqtt-basics.html */
#define SECRET_MQTT_ADDRESS_URL "mqtt3.thingspeak.com"
#define SECRET_MQTT_PORT "1883"
#define SECRET_MQTT_USERNAME "IgAhECIoJjcSHhwwCR49DTs"
#define SECRET_MQTT_CLIENT_ID "IgAhECIoJjcSHhwwCR49DTs"
#define SECRET_MQTT_PASSWORD "omKdOVvpxyI2Cmh4wDOYNe4R"

#define SECRET_MQTT_CHANELID 2173391
#define SECRET_MQTT_QoS 0

/*
    MQTT_ADDRESS_URL: mqtt3.thingspeak.com
    MQTT_PORT: 1883
    MQTT_USERNAME: IgAhECIoJjcSHhwwCR49DTs
    MQTT_CLIENT_ID: IgAhECIoJjcSHhwwCR49DTs
    MQTT_PASSWORD: omKdOVvpxyI2Cmh4wDOYNe4R
    MQTT_CHANELID: 2173391
    MQTT_QoS: 0
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Frame pushlish data to a field in a channel
#define MQTT_PUBLISH_TOPIC "channels/2173391/publish/fields/field"
/*-----> MQTT_PUBLISH_TOPIC + (number of the field) */
/*
    * Example puslish data to a field in a channel
    Topic: channels/2173391/publish/fields/field1
    Payload: 25
*/

// Frame subscribe to a field in a channel
#define MQTT_SUBSCRIBE_TOPIC "channels/2173391/subscribe/fields/field"
/*-----> MQTT_SUBSCRIBE_TOPIC + (number of the field) */
/*
    * Example subscribe to a field in a channel
    Topic: channels/2173391/subscribe/fields/field2
    QoS: 0
*/