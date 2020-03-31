#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QDebug>
#include <QMainWindow>
#include<QWidget>
#include<QPushButton>
#include<QString>
#include<QLabel>
#include<QPalette>
#include<QFile>
#include"card.h"
struct player//玩家结构
{
    QString name;
    int incbr,incst,incmo;//资源增加量
    int bri,sto,mon;//拥有资源
    int tower,wall;//防御设施
    int again;
    int num[6];//拥有卡牌序号
};
class card
{
    int brN,stN,moN;//资源需求
    int number;//卡牌分类序号
public:
    int getbrN(){return brN;}
    int getstN(){return stN;}
    int getmoN(){return moN;}
    card()
    {
        brN=0;stN=0;moN=0;
        number=0;
    }
    card(int num,int b=0,int s=0,int m=0)
    {
        brN=b;stN=s;moN=m;
        number=num;
    }

};
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int x;
    int readline(player &player1,int &round);//读取配置数据
    QString cardpic(int n);//返回卡牌图像
    int check(int n,player p1,card cards[]);//检查出牌是否符合要求
    int draw();//随机抽牌
    int  operate(player &p1,player &p2,card cards[],int n);//玩家操作
    int operate2(player &p1,player &p2,card cards[]);//单人游戏中电脑操作
    void fresh();//刷新资源数据
    void show1(player p1);//展示卡牌
    void enforce(player &p1,player &p2,card cards[],int n);//应用卡牌
    int endgame(player p1,player p2);//检测游戏是否结束
    void end(int n);//游戏结束
    int AI(player p,card cards[]);//人工智能玩家

private:
    int sd=2;//当前游戏玩家数
    Ui::MainWindow *ui;
    QString pl1,pl2;//玩家姓名
    card cards[87];
    player player1={"player1",2,2,2,10,10,10,25,10,0};//初始化玩家数据
    player player2=player1;
    int round=30;//结束游戏局数
    int preplayer;//当前出牌玩家
    int opcard=0;//当前选择牌号
    int flag=0;//是否再次出牌
private slots:
    void slot1();//单人游戏
    void slot2();//双人游戏
    void slot01();//一号按钮
    void slot02();//二号按钮
    void slot03();
    void slot04();
    void slot05();
    void slot06();
    void sloty();//确认按钮
    void slotz();//切换到玩家二
    void slotqh1();//切换到玩家一

};

#endif // MAINWINDOW_H




















