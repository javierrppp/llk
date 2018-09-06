#include "handler.h"

handler::handler(QObject *parent) : QObject(parent)
{

}
handler* handler::hand = new handler;

handler *handler::getInstance()
{
    return hand;
}

void handler::tellShowHistory()
{
    emit showHistory();
}

void handler::tellStart()
{
    emit startGame();
}

void handler::tellExit()
{
    emit exitGame();
}

void handler::tellSettings()
{
    emit showSettingsInterface();
}

void handler::tellReset()
{
    emit resetInterface();
}

void handler::tellTheSelectOrder(int order)
{
    emit selectOrder(order);
}

void handler::tellModifyVolumn(bool on)
{
    emit modifyVolumn(on);
}

void handler::tellPlaySound(QString path)
{
    emit playSound(path);
}

void handler::tellRefresh(bool used)
{
    emit refresh(used);
}

void handler::tellToFind()
{
    emit findAPair();
}

void handler::boom_be_clicked(bool order)
{
    emit boom(order);
}

void handler::tellToHomepage(int from)
{
    //from为0表示设置中点击的，from为1表示从游戏结束界面点击的，from为2表示从游戏通关界面点击的
    emit toHomepage(from);
}

void handler::tellToPlayAgain()
{
    emit playAgain();
}

void handler::tellToNextCheckpoint()
{
    emit toNextCheckpoint();
}
