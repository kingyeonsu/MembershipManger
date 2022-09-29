#ifndef CLOCKSERVICE_H
#define CLOCKSERVICE_H

#pragma once

#include <time.h>
#include "ClockView.h"

class ClockService
{
private:
    time_t curTime;
    ClockView *clockView;

public:
    ClockService(ClockView *view);
    ~ClockService();
    void updateEvent();
    void stopWatchEvent();
    void stopWatchIint();

};

#endif