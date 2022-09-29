#include "ClockView.h"

ClockView::ClockView(LCD *Lcd)
{
    this->lcd = Lcd;
    stopwatchCount = 0;
}

ClockView::~ClockView()
{

}

void ClockView::updateTime(struct tm *timeData)
{
    char clockBuff[30];
    sprintf(clockBuff, "%02d:%02d:%02d",
     timeData->tm_hour,  timeData->tm_min, timeData->tm_sec);

    lcd->WriteStringXY(1, 0, clockBuff);
}

void ClockView::updateStopWatch()
{
    static unsigned int prevStopWatchTime= 0;
    char stopwatchBuff[30];
    if (millis() - prevStopWatchTime > 100)
    {
        prevStopWatchTime = millis();
        stopwatchCount++;
        printf("stopwatchCount: %d\n", stopwatchCount);
        if (stopwatchCount > 99999)
        {
            stopwatchCount=0;
        }
    }
    sprintf(stopwatchBuff, "%05d", stopwatchCount);
    lcd->WriteStringXY(1, 10, stopwatchBuff);    
}

void ClockView::initStopWatch()
{
    stopwatchCount = 0;
}