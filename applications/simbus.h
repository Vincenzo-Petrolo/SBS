#ifndef __SIMBUS_H__
#define __SIMBUS_H__

#include <stdio.h>

#define SIMBUS_OK 0
#define SIMBUS_CRASHED 1
#define SIMBUS_MOVING 2
#define SIMBUS_STILL 3

typedef struct {
    /*These values are dynamic*/
    float speed;
    float proximity;
    uint8_t humidity;
    int rpm;
    uint8_t brake_pads_wearing;
    uint8_t tyre_pressure;
    uint8_t people_onboard;
    float brakes;
    float time;
} bus_t;

void bus_init(bus_t *);

void set_proximity(bus_t *, float);
float get_proximity(bus_t *);

void set_humidity(bus_t *, uint8_t);
uint8_t get_humidity(bus_t *);

void set_speed(bus_t *, float);
float get_speed(bus_t *);

void set_rpm(bus_t *, int);
int get_rpm(bus_t *);

void set_brake_pads_wearing(bus_t *, uint8_t);
uint8_t get_brake_pads_wearing(bus_t *);

void set_tyre_pressure(bus_t *, uint8_t);
uint8_t get_tyre_pressure(bus_t *);

void set_people_onboard(bus_t *, uint8_t);
uint8_t get_people_onboard(bus_t *);

void set_brake(bus_t *, float);
float get_brake(bus_t *);

void step_sim(bus_t *, float s);

uint8_t bus_crashed(bus_t *);

uint8_t bus_is_still(bus_t *);

float get_time(bus_t *);

#endif
