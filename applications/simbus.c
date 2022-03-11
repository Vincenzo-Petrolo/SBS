#include "simbus.h"
#include "sensors_header.h"
#include <math.h>


void bus_init(bus_t *obj)
{
    obj->proximity = proximity_start;
    obj->brake_pads_wearing = brake_pads_wearing_value;
    obj->humidity = humidity_value;
    obj->people_onboard = people_onboard;
    obj->rpm = rpm_value;
    obj->speed = initial_speed / 3.6;
    obj->tyre_pressure = tyre_pressure_value;
    obj->brakes = 0;

    return;
}

void set_proximity(bus_t *obj,unsigned int p)
{
    obj->proximity = p;

    return;
}
unsigned int get_proximity(bus_t *obj)
{
    return obj->proximity;
}

void set_humidity(bus_t *obj, uint8_t h)
{
    if (h > 100)
        obj->humidity = 100;
    else obj->humidity = h;

    return;
}
uint8_t get_humidity(bus_t *obj)
{

    return obj->humidity;
}

void set_speed(bus_t *obj, float s)
{
    obj->speed = s;
}
float get_speed(bus_t *obj)
{
    return obj->speed;
}

void set_rpm(bus_t *obj, int r)
{
    if (r > 1)
        obj->rpm = 1;
    else obj->rpm = r;

    return;
}
int get_rpm(bus_t *obj)
{
    return obj->rpm;
}

void set_brake_pads_wearing(bus_t *obj, uint8_t bpw)
{
    if (bpw > 100)
        obj->brake_pads_wearing = 100;
    else obj->brake_pads_wearing = bpw;

    return;
}
uint8_t get_brake_pads_wearing(bus_t *obj)
{
    return obj->brake_pads_wearing;
}
void set_tyre_pressure(bus_t *obj, uint8_t tp)
{
    if (tp > 100)
        obj->tyre_pressure = 100;
    else obj->tyre_pressure = tp;

    return;
}
uint8_t get_tyre_pressure(bus_t *obj)
{
    return obj->tyre_pressure;
}
void set_people_onboard(bus_t *obj, uint8_t pob)
{
    if (pob > 100)
        obj->people_onboard = 100;
    else obj->people_onboard = pob;

    return;
}
uint8_t get_people_onboard(bus_t *obj)
{
    return obj->people_onboard;
}

void set_brake(bus_t *obj, float b)
{
    if (obj->brakes > 10)
        obj->brakes = 10;
    else obj->brakes = b;

    return;
}
float get_brake(bus_t * obj)
{
    return obj->brakes;
}


void step_sim(bus_t *obj, float s)
{
    /*First reduce proximity value by computing distance traveled in s time.*/
    if (obj->speed > 0)
        obj->proximity -= obj->speed*s - (obj->brakes*(100 - obj->brake_pads_wearing)/100)/2 * pow(s,2);
    /*Now reduce speed*/
    obj->speed -= (obj->brakes*obj->brake_pads_wearing/100)*s;

    /*Update also rpm, reduce the rpms by an amount that increases with power of brakes and tyre wearings*/
    obj->rpm = (obj->speed*5 - obj->brakes*obj->brake_pads_wearing);

    if (obj->speed < 0)
        obj->speed = 0;

    return;
}

uint8_t bus_crashed(bus_t *obj)
{
    if (obj->proximity <= 0) {
        return SIMBUS_CRASHED;
    } else {
        return SIMBUS_OK;
    }
}

uint8_t bus_is_still(bus_t *obj)
{
    if (obj->speed == 0) {
        return SIMBUS_STILL;
    } else {
        return SIMBUS_MOVING;
    }
}
