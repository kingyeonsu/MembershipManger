#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "Monitor.h"
#include "DeviceData.h"
#include "MembersManageService.h"
#include "ClockService.h"

class Controller
{
private:
    Monitor *monitor;
    MembersManageService *membersManageService;
    ClockService *clockService;

public:
    Controller(MembersManageService *membersManageService, ClockService *clockService);
    virtual ~Controller();
    void updateEvent(DeviceData data);
    
};

#endif /* __CONTROLLER_H__ */
