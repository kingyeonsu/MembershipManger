#include "LED.h"

// :: --> 범위 지정 연산자
LED::LED(int pin)   // 생성자 (초기화)
{
    pinNum = pin;
    ledState=0;
    wiringPiSetup();
    pinMode(pinNum, OUTPUT);
}

LED::~LED()  // 소멸자
{
}

void LED::on()
{
    ledState=1;
    digitalWrite(pinNum, ledState);
}

void LED::off()
{
    ledState=0;
    digitalWrite(pinNum, ledState);
}

void LED::toggle()
{
    ledState = ledState ^ 1;    // ^: XOR
    digitalWrite(pinNum, ledState);
}