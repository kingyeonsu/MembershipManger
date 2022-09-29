#ifndef LEDVIEW_H
#define LEDVIEW_H

#pragma once

#include <wiringPi.h>
#include <string>
#include "LED.h"
#include "LightState.h"

class LedView
{
private:
    int lightState;
    LED *light1, *light2, *light3;

public:
    LedView(LED *led1, LED *led2, LED *led3);
    ~LedView();
    void setState(int state);
    void lightView();
    void lightOff();
    void lightOn_1();
    void lightOn_2();
    void lightOn_3();


};

#endif