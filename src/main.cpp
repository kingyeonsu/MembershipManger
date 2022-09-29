#include <iostream>
#include <thread>
#include <cstring>
#include <wiringPi.h>
#include "GolfMembershipManager.h"
#include "Listener.h"
#include "Controller.h"
#include "MembersManageService.h"
#include "MembersEntity.h"
#include "tcpServer.h"
#include "ComDev.h"
#include "I2C.h"
#include "lcd.h"
#include "LedView.h"
#include "LED.h"
#include "MemberInfo.h"
#include "ClockService.h"
#include "ClockView.h"
#include "ClockCheck.h"


void serverThread(tcpServer *server)
{
    char recvBuff[BUFSIZ];
    char recvBuff_find[BUFSIZ];
    char recvBuff_delete[BUFSIZ];
    int recvLen, recvLen_find, recvLen_delete;
    MembersEntity *membersEntity = new MembersEntity;

    while (server->waitAccept() > 0)
    {
        server->setClientState(true);
        while((recvLen = server->recvData(recvBuff, sizeof(recvBuff))) > 0)
        {
            if (strcmp(recvBuff, "find") == 0)
            {
                while((recvLen_find = server->recvData(recvBuff_find, sizeof(recvBuff_find))) > 0)
                { 
                    recvBuff_find[recvLen_find] = '\0';
                    membersEntity->findMemberInfo(recvBuff_find);
                    membersEntity->memoryToDB();
                    server->sendData(recvBuff_find, recvLen_find);
                    printf("find received : %s\n", recvBuff_find);
                    break;
                }
            }
           if (strcmp(recvBuff, "delete") == 0)
            {
                while((recvLen_find = server->recvData(recvBuff_find, sizeof(recvBuff_find))) > 0)
                { 
                    recvBuff_find[recvLen_delete] = '\0';
                    membersEntity->delClientMember(recvBuff_find);
                    membersEntity->memoryToDB();
                    server->sendData(recvBuff_find, recvLen_delete);
                    printf("delete completed : %s\n", recvBuff_find);
                    break;
                }
            }
            recvBuff[recvLen] = '\0';
            server->sendData(recvBuff, recvLen);
            printf("received : %s\n", recvBuff);
        }
        server->closeSocket(server->getClientSocket());
        server->setClientState(false);
        printf("close client socket\n");
    }
}

int main(void)
{
    tcpServer *cardTcpServer = new tcpServer(5100);
    ClockCheck *clockCheck = new ClockCheck("clock");
    I2C *i2c = new I2C("/dev/i2c-1", 0x27);
    LED *closeLed = new LED(21);
    LED *openLed = new LED(22);
    LED *registerLed = new LED(23);
    LCD *lcd = new LCD(i2c);
    LedView *ledView = new LedView(closeLed, openLed, registerLed);
    ClockView *clockView = new ClockView(lcd);
    ClockService *clockService = new ClockService(clockView);
    ComDev *comDev = new ComDev(cardTcpServer);
    MembersManageService * membersManageSerivce = new MembersManageService(comDev, ledView, lcd);
    Controller *controller = new Controller(membersManageSerivce, clockService);
    Listener *listener = new Listener(controller, clockCheck);
    std::thread threadFunc(serverThread, cardTcpServer);

    //GolfMembershipManager golfMembershipManager;

    //golfMembershipManager.run();
    while(1)
    {
        listener->checkEvent();
        ledView->lightView();
        delay(50);
    }
    
    return 0;
}
