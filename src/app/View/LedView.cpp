#include "LedView.h"

LedView::LedView(LED *led1, LED *led2, LED *led3)
{
    this->light1 = led1;
    this->light2 = led2;
    this->light3 = led3;
    this->lightState = LIGHT_OFF;
}

LedView::~LedView()
{

}

void LedView::setState(int state)
{
    lightState = state;
}

void LedView::lightView()
{
    switch (lightState)
    {
        case LIGHT_OFF:
            lightOff();
        break;
        case LIGHT_1:
            lightOn_1();
        break;
        case LIGHT_2:
            lightOn_2();
        break;
        case LIGHT_3:
            lightOn_3();
        break;
    }
}

void LedView::lightOff()
{
    light1->off();
    light2->off();
    light3->off();
}

void LedView::lightOn_1()
{
    light1->on();
    light2->off();
    light3->off();
}

void LedView::lightOn_2()
{
    light1->off();
    light2->on();
    light3->off();
}

void LedView::lightOn_3()
{
    light1->off();
    light2->off();
    light3->on();
}