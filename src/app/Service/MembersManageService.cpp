#include "MembersManageService.h"
#include <cstring>
#include <wiringPi.h>

MembersManageService::MembersManageService(ComDev *comDev, LedView *ledView, LCD *lcd)
{
    membersEntity = new MembersEntity();
    membersManagerState = CARD_READER;
    this->comDev = comDev;
    this->ledView = ledView;
    lightState = LIGHT_OFF;
    this->lcd = lcd;
}

MembersManageService::~MembersManageService()
{
}

void MembersManageService::setComDev(ComDev *comDev)
{
    this->comDev = comDev;
}

void MembersManageService::updateStateEvent(std::string devName)
{
    char lcdBuff[20];
    switch (membersManagerState)
    {
        case CARD_READER :
        sprintf(lcdBuff, "REGISTER");
        lcd->WriteStringXY(1, 8, lcdBuff);
            lightState = LIGHT_3;
            if (devName == "ModeButton") {
                membersManagerState = CARD_REGISTER;
                printf("changed to CARD_REGISTER State\n");
            }
        break;
        case CARD_REGISTER :
        sprintf(lcdBuff, " READER ");
        lcd->WriteStringXY(1, 8, lcdBuff);
            lightState = LIGHT_1;
            if (devName == "ModeButton") {
                membersManagerState = CARD_READER;
                printf("changed to CARD_READER State\n");
            }
        break;
    }
    ledView->setState(lightState);
}

void MembersManageService::checkCardNumber(int *cardNum)
{
    char cardNumBuff[20];
    
    switch (membersManagerState)
    {
        case CARD_READER :
            if (membersEntity->findMemberInfo(cardNum)) {
                printf("Registered Member!\n");
                membersEntity->printMemberInfo(cardNum);
                comDev->sendData(cardNum);
                lightState = LIGHT_2;
                sprintf(cardNumBuff, "%0x-%0x-%0x-%0x-%0x" , cardNum[0], cardNum[1],cardNum[2],
                cardNum[3],cardNum[4]);
                lcd->WriteStringXY(0, 0, cardNumBuff);
                delay(2000);
                sprintf(cardNumBuff, "                ");
                lcd->WriteStringXY(0, 0, cardNumBuff);
            }
            else {
                printf("Not Registered Member!\n");
                
            }
        break;
        case CARD_REGISTER :        
            MemberInfo tempMember;
            char tempMemberBuff[4][30];    
            for (int i=0; i<4; i++)
            {
                switch (i)
                {
                    case 0:
                    printf("ID: ");
                    scanf("%s",tempMemberBuff[i]);
                    tempMember.id = atoi(tempMemberBuff[i]);
                    break;
                    case 1:
                    printf("name: ");
                    scanf("%s",tempMemberBuff[i]);
                    strcpy(tempMember.name, tempMemberBuff[i]);
                    break;
                    case 2:
                    printf("address: ");
                    scanf("%s",tempMemberBuff[i]);
                    strcpy(tempMember.address, tempMemberBuff[i]);
                    break;
                    case 3:
                    printf("phonenumber: ");
                    scanf("%s",tempMemberBuff[i]);
                    strcpy(tempMember.phoneNumber, tempMemberBuff[i]);
                    break;
                }
            }
            memcpy(tempMember.cardNum, cardNum, sizeof(tempMember.cardNum));
            membersEntity->addMemberInfo(tempMember);
            printf("Member Registered!\n");
            membersEntity->memoryToDB();
        break;
    }
    ledView->setState(lightState);
}