#ifndef __CUSTOM_TYPES__
#define __CUSTOM_TYPES__

typedef struct {
  uint8_t value;
  uint8_t sensor;
} msg_t;

typedef struct {
    uint8_t speed;
    uint8_t rpm;
    uint8_t humidity;
    uint8_t proximity;
} bus_state_t;

#endif
