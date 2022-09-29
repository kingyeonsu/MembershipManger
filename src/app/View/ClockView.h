#ifndef CLOCKVIEW_H
#define CLOCKVIEW_H

#pragma once

#include <wiringPi.h>
#include <time.h>
#include "LCD.h"

class ClockView
{
private:
    struct tm timeDate;
    LCD *lcd;
    int stopwatchCount;

public:
    ClockView(LCD *Lcd);
    ~ClockView();
    void updateTime(struct tm *timeData);
    void updateStopWatch();
    void initStopWatch();

};

#endif