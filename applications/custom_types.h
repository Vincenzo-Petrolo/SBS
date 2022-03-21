#ifndef __CUSTOM_TYPES__
#define __CUSTOM_TYPES__

typedef struct {
  float speed;
  float rpm;
  uint8_t humidity;
  uint16_t proximity;
} msg_t;

typedef struct {
    /*Received through sensors using normal protocols*/
    float speed;
    float rpm;
    uint8_t humidity;
    uint16_t proximity;
    /*Received through CAN*/
    uint8_t brake_pads_wearing; /*Marked as W*/
    uint8_t tyre_pressure; /*Marked as T*/
    uint8_t people_onboard; /*Marked as O*/
} bus_state_t;

typedef struct {
    uint8_t crossway_proximity;
    uint8_t traffic;
    uint8_t traffic_light_status;
} external_state_t;

#endif
