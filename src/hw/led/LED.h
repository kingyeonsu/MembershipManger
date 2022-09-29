#ifndef LED_H
#define LED_H

#pragma once

#include <wiringPi.h>

class LED   // 캡슐화
{
// private, public: 접근 지정 명령어

private:    // class LED 안에서만 공유  // 정보 은닉
    int pinNum, ledState;   // 속성, 필드

public:     // 전체 공개용
    // 메소드
    LED(int pin);   // 생성자
    ~LED();  // 소멸자
    void on();
    void off();
    void toggle();
};

#endif