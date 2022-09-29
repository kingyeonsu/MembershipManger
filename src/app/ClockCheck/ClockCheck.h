#ifndef CLOCKCHECK_H
#define CLOCKCHECK_H

#pragma once

#include <time.h>
#include "DeviceData.h"

class ClockCheck
{
private:
    time_t prevSec;
    DeviceData clockData;

public:
    ClockCheck(std::string name);
    ~ClockCheck();
    bool isUpdate();
    DeviceData getClockData();
};

#endif