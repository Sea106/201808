#ifndef PLAYER_H
#define PLAYER_H
#include<QPushButton>
#include<QMessageBox>
#include<QMenu>
#include<QMenuBar>
#include<QToolBar>
#include<QDialog>
#include<QString>
#include<QInputDialog>
//#include<QDebug>
#include<QImage>
#include<QHBoxLayout>
#include<QPixmap>
struct player//玩家结构
{
    QString name;
    int incbr,incst,incmo;//资源增加量
    int bri,sto,mon;//拥有资源
    int tower,wall;//防御设施
    int again;
    int num[6];//拥有卡牌序号
};
#endif // PLAYER_H
