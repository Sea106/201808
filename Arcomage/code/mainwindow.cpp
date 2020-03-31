#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>
#include<QMessageBox>
#include<QMenu>
#include<QMenuBar>
#include<QToolBar>
#include<QDialog>
#include<QString>
#include<QInputDialog>
#include<QDebug>
#include<QImage>
#include<QHBoxLayout>
#include<QPixmap>
#include<QIODevice>
#include<QByteArray>
extern QString pl1,pl2;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化players
    ui->label_2->setPixmap(QPixmap(":/1_files/background.jpg"));
    ui->qh1->hide();
    ui->end->hide();
    int j;
    QPalette inc;
    inc.setColor(QPalette::WindowText,Qt::yellow);
    setFixedSize(870,650);
    QToolBar *tBar=addToolBar("Toolbar");
    QMenuBar *mBar=menuBar();
    QMenu *pFile=mBar->addMenu("开始");
    QAction *pNew1=pFile->addAction("单人");
    QAction *pNew2=pFile->addAction("双人");
    ui->plr1->setText("Player1");
    ui->plr2->setText("Player2");
    ui->p1ib->setPalette(inc);
    ui->p1im->setPalette(inc);
    ui->p1is->setPalette(inc);
    ui->p2ib->setPalette(inc);
    ui->p2im->setPalette(inc);
    ui->p2is->setPalette(inc);
    cards[0]=card(0,0);
    cards[1]=card(1,0);
    cards[2]=card(2,1);
    cards[3]=card(3,3);
    cards[4]=card(4,4);
    cards[5]=card(5,7);
    cards[6]=card(6,2);
    cards[7]=card(7,5);
    cards[8]=card(8,2);
    cards[9]=card(9,3);
    cards[10]=card(10,2);
    cards[11]=card(11,3);
    cards[12]=card(12,7);
    cards[13]=card(13,8);
    cards[14]=card(14,0);
    cards[15]=card(15,5);
    cards[16]=card(16,4);
    cards[17]=card(17,6);
    cards[18]=card(18,0);
    cards[19]=card(19,8);
    cards[20]=card(20,9);
    cards[21]=card(21,9);
    cards[22]=card(22,11);
    cards[23]=card(23,13);
    cards[24]=card(24,15);
    cards[25]=card(25,16);
    cards[26]=card(26,18);
    cards[27]=card(27,24);
    cards[28]=card(28,7);
    cards[29]=card(29,0,1);
    cards[30]=card(30,0,2);
    cards[31]=card(31,0,2);
    cards[32]=card(32,0,3);
    cards[33]=card(33,0,2);
    cards[34]=card(34,0,5);
    cards[35]=card(35,0,4);
    cards[36]=card(36,0,6);
    cards[37]=card(37,0,2);
    cards[38]=card(38,0,3);
    cards[39]=card(39,0,4);
    cards[40]=card(40,0,3);
    cards[41]=card(41,0,7);
    cards[42]=card(42,0,7);
    cards[43]=card(43,0,6);
    cards[44]=card(44,0,9);
    cards[45]=card(45,0,8);
    cards[46]=card(46,0,7);
    cards[47]=card(47,0,10);
    cards[48]=card(48,0,5);
    cards[49]=card(49,0,13);
    cards[50]=card(50,0,4);
    cards[51]=card(51,0,12);
    cards[52]=card(52,0,14);
    cards[53]=card(53,0,16);
    cards[54]=card(54,0,15);
    cards[55]=card(55,0,17);
    cards[56]=card(56,0,21);
    cards[57]=card(57,0,8);
    cards[58]=card(58,0,0);
    cards[59]=card(59,0,0,1);
    cards[60]=card(60,0,0,1);
    cards[61]=card(61,0,0,3);
    cards[62]=card(62,0,0,2);
    cards[63]=card(63,0,0,3);
    cards[64]=card(64,0,0,4);
    cards[65]=card(65,0,0,6);
    cards[66]=card(66,0,0,3);
    cards[67]=card(67,0,0,5);
    cards[68]=card(68,0,0,6);
    cards[69]=card(69,0,0,7);
    cards[70]=card(70,0,0,8);
    cards[71]=card(71,0,0,0);
    cards[72]=card(72,0,0,5);
    cards[73]=card(73,0,0,6);
    cards[74]=card(74,0,0,6);
    cards[75]=card(75,0,0,5);
    cards[76]=card(76,0,0,8);
    cards[77]=card(77,0,0,9);
    cards[78]=card(78,0,0,11);
    cards[79]=card(79,0,0,9);
    cards[80]=card(80,0,0,10);
    cards[81]=card(81,0,0,14);
    cards[82]=card(82,0,0,11);
    cards[83]=card(83,0,0,12);
    cards[84]=card(84,0,0,15);
    cards[85]=card(85,0,0,17);
    cards[86]=card(86,0,0,25);

    connect(pNew1,&QAction::triggered,this,&MainWindow::slot1);
    connect(pNew2,&QAction::triggered,this,&MainWindow::slot2);
    connect(ui->qh1,&QPushButton::clicked,this,&MainWindow::slotqh1);
    readline(player1,round);//读取配置
    player2=player1;
    for(j=0;j<6;j++)//初始化卡牌
    {
        player1.num[j]=draw();
    }
    for(j=0;j<6;j++)//初始化卡牌
    {
        player2.num[j]=draw();
    }
    ui->rs1->setPixmap(QPixmap(":/1_files/Resource.bmp"));
    ui->rs2->setPixmap(QPixmap(":/1_files/Resource.bmp"));
    ui->tt1->setPixmap(QPixmap(":/1_files/TowerTop0.png"));
    ui->tt2->setPixmap(QPixmap(":/1_files/TowerTop1.png"));
    ui->tower1->setPixmap((QPixmap(":/1_files/Tower.bmp")));
    ui->tower2->setPixmap((QPixmap(":/1_files/Tower.bmp")));
    ui->w1->setPixmap((QPixmap(":/1_files/Wall.png")));
    ui->w2->setPixmap((QPixmap(":/1_files/Wall.png")));

}
void MainWindow::end(int n)
{
    //ui->end->setPixmap(QPixmap(":/1_files/background.jpg"));

    if(n==3)
    {
        ui->end->setText("平局");
    }
        else if(n==1)
    {
        ui->end->setText("玩家1胜利");
    }
        else if(n==2)
    {
        ui->end->setText("玩家2胜利");
    }
    ui->end->show();
}
void MainWindow::slot01(){
    opcard=1;
}
void MainWindow::slot02(){opcard=2;
                         }
void MainWindow::slot03(){opcard=3;
                         }
void MainWindow::slot04(){opcard=4;
                         }
void MainWindow::slot05(){opcard=5;
                         }
void MainWindow::slot06(){opcard=6;
                         }
void MainWindow::slotqh1()
{
    show1(player1);
    ui->pb1->show();
    ui->pb2->show();
    ui->pb3->show();
    ui->pb4->show();
    ui->pb5->show();
    ui->pb6->show();
}
int MainWindow::readline(player &player1,int &round)
{
    int e[9];
    QFile file(":/1_files/Configuration.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        int a=0;
        while (!file.atEnd())
        {
            QByteArray line=file.readLine();
            QString str(line);
            e[a]=str.toInt();
            a++;
        }
    }
    player1.tower=e[0];
    player1.wall=e[1];
    player1.bri=e[2];
    player1.incbr=e[3];
    player1.sto=e[4];
    player1.incst=e[5];
    player1.mon=e[6];
    player1.incmo=e[7];
    round=e[8];
}
void MainWindow::sloty()
{
    //round--;
    if(round<0)
    {
        //end
        end(3);
        return;
    }
    QString str=QString::number(round);
    ui->round->setText(str);
    if(opcard==0) return;
    if(preplayer==1)
    {
        show1(player1);
        operate(player1,player2,cards,opcard);
        preplayer=2;
        ui->z->show();
        ui->qh1->hide();

        if(player1.wall<=0)ui->w1->hide();
        else ui->w1->show();
        if(player2.wall<=0)ui->w2->hide();
        else ui->w2->show();
        ui->pb1->hide();
        ui->pb2->hide();
        ui->pb3->hide();
        ui->pb4->hide();
        ui->pb5->hide();
        ui->pb6->hide();
        if(flag)
        {
            flag=0;
            preplayer=1;
            sloty();
            ui->pb1->show();
            ui->pb2->show();
            ui->pb3->show();
            ui->pb4->show();
            ui->pb5->show();
            ui->pb6->show();
            ui->z->hide();
        }
    }
    else if(preplayer==2&&sd==2)
    {
        operate(player2,player1,cards,opcard);
        preplayer=1;
        if(flag)
        {
            flag=0;
            preplayer=2;
            sloty();
            show1(player2);
        }
        if(player1.wall<=0)ui->w1->hide();
        else ui->w1->show();
        if(player2.wall<=0)ui->w2->hide();
        else ui->w2->show();

    }
    int t=endgame(player1,player2);
    qDebug()<<t;
    if(t)
        end(t);
    opcard=0;
    player1.bri+=player1.incbr;
    player1.sto+=player1.incst;
    player1.mon+=player1.incmo;
    player2.bri+=player2.incbr;
    player2.sto+=player2.incst;
    player2.mon+=player2.incmo;
    fresh();

}
void MainWindow::slotz()
{
    if(preplayer==1)return;
    show1(player2);
    if(sd==2)//双人
    {
        ui->pb1->show();
        ui->pb2->show();
        ui->pb3->show();
        ui->pb4->show();
        ui->pb5->show();
        ui->pb6->show();

        preplayer=2;
        sloty();
    }
    else if(sd==1)//单人
    {
        operate2(player2,player1,cards);
        ui->z->hide();
        ui->qh1->show();
    }
    round--;
}
int MainWindow::AI(player p,card cards[])
{//自身资源/防御增加+1，对手增加-1，再次出牌+3，资源产量+5，消耗-1
    int a[87]={-1,7,3,2,3,-2,-3,-3,1,1,2,1,-2,0,0,1,1,4,10,0,1,5,-2,-1,-2,-1,-2,4,-3,3,2,1,2,1,-1,0,1,1,2,1,2,4,-5,2,1,-4,4,1,-5,-3,-7,-1,-1,-1,5,1,-1,-3,0,4,0,2,1,0,-2,-1,2,2,-2,3,0,3,1,1,3,1,0,0,-3,1,-4,-1,2,8,-1,-7,0};
    int t1=-20,t2=-20,m1=-1,m2=-1;
        for(int i=0;i<6;i++)//可出
        {
            if(check(i+1,p,cards)<2&&a[p.num[i]]>t1)
            {
                m1=i+1;
                t1=a[p.num[i]];
            }
        }
        for(int i=0;i<6;i++)//可弃
        {
            if(check(i+1,p,cards)%2==0&&(-a[p.num[i]]>t2))
            {
                m2=i+1;
                t2=a[p.num[i]];
            }
        }
        if(t1>=t2)
        {
            return 10*m1+1;
        }
        else
        {
            return 10*m2+2;
        }
}
int MainWindow::operate2(player &p1,player &p2,card cards[])
   {
       int n,a;
       a=AI(p1,cards);
           n=a/10;
           a=a-10*n;
               if(a==1)
               {
                   ui->cardlast->setPixmap(QPixmap(cardpic(p1.num[n-1])));
                   enforce(p1,p2,cards,p1.num[n-1]);
                   fresh();
                   p1.num[n-1]=MainWindow::draw();
               }
               else if(a==2)
               {
                   p1.num[n-1]=MainWindow::draw();
               }

       if(p1.again)
       {
           p1.again=0;
           operate2(p1,p2,cards);
       }
       preplayer=1;
       show1(p1);
       //round--;
   }
void MainWindow::slot1()//单人
{
    ui->qh1->show();
    sd=1;
    ui->z->setText("电脑出牌");
    bool ok;
    QString pl1=QInputDialog::getText(NULL,"Playername",
                                      "请输入玩家1姓名",
    QLineEdit::Normal,
                                      "Player1",
                                      &ok);
    {if (ok)
     QMessageBox::information(NULL,"Information",
                              "Player1 is:<b>"+pl1+"</b>",
                              QMessageBox::Yes|QMessageBox::No,
                              QMessageBox::Yes);
    }
    ui->plr1->setText(pl1);
    ui->plr2->setText("Computer");
    readline(player1,round);//读取配置
    QString str=QString::number(round);
    ui->round->setText(str);
    player2=player1;
    for(int j=0;j<6;j++)//初始化卡牌
    {
        player1.num[j]=draw();
    }
    for(int j=0;j<6;j++)//初始化卡牌
    {
        player2.num[j]=draw();
    }
    ui->rs1->setPixmap(QPixmap(":/1_files/Resource.bmp"));
    ui->rs2->setPixmap(QPixmap(":/1_files/Resource.bmp"));
    ui->tt1->setPixmap(QPixmap(":/1_files/TowerTop0.png"));
    ui->tt2->setPixmap(QPixmap(":/1_files/TowerTop1.png"));
    ui->tower1->setPixmap((QPixmap(":/1_files/Tower.bmp")));
    ui->tower2->setPixmap((QPixmap(":/1_files/Tower.bmp")));
    ui->w1->setPixmap((QPixmap(":/1_files/Wall.png")));
    ui->w2->setPixmap((QPixmap(":/1_files/Wall.png")));
    ui->pb1->show();
    ui->pb2->show();
    ui->pb3->show();
    ui->pb4->show();
    ui->pb5->show();
    ui->pb6->show();
                fresh();
                connect(ui->pb1,&QPushButton::clicked,this,&MainWindow::slot01);
                connect(ui->pb2,&QPushButton::clicked,this,&MainWindow::slot02);
                connect(ui->pb3,&QPushButton::clicked,this,&MainWindow::slot03);
                connect(ui->pb4,&QPushButton::clicked,this,&MainWindow::slot04,Qt::UniqueConnection);
                connect(ui->pb5,&QPushButton::clicked,this,&MainWindow::slot05,Qt::UniqueConnection);
                connect(ui->pb6,&QPushButton::clicked,this,&MainWindow::slot06,Qt::UniqueConnection);
                connect(ui->y,&QPushButton::clicked,this,&MainWindow::sloty,Qt::UniqueConnection);
                connect(ui->z,&QPushButton::clicked,this,&MainWindow::slotz,Qt::UniqueConnection);
                preplayer=1;
                show1(player1);

}

void MainWindow::slot2()//双
{
    bool ok;
    sd=2;
    QString pl1=QInputDialog::getText(NULL,"Playername",
                                      "请输入玩家1姓名",
    QLineEdit::Normal,
                                      "Player1",
                                      &ok);
    {if (ok)
     QMessageBox::information(NULL,"Information",
                              "Playername1 is:<b>"+pl1+"</b>",
                              QMessageBox::Yes|QMessageBox::No,
                              QMessageBox::Yes);
        QString pl2=QInputDialog::getText(NULL,"Playername",
                                          "请输入玩家2姓名",
        QLineEdit::Normal,
                                          "Player2",
                                          &ok);
        {if (ok)
         QMessageBox::information(NULL,"Information",
                                  "Playername2 is:<b>"+pl2+"</b>",
                                  QMessageBox::Yes|QMessageBox::No,
                                  QMessageBox::Yes);
            ui->plr1->setText(pl1);
            ui->plr2->setText(pl2);
            ui->z->setText("切换到玩家2");
            readline(player1,round);//读取配置
            QString str=QString::number(round);
            ui->round->setText(str);
            player2=player1;
            for(int j=0;j<6;j++)//初始化卡牌
            {
                player1.num[j]=draw();
            }
            for(int j=0;j<6;j++)//初始化卡牌
            {
                player2.num[j]=draw();
            }
            ui->rs1->setPixmap(QPixmap(":/1_files/Resource.bmp"));
            ui->rs2->setPixmap(QPixmap(":/1_files/Resource.bmp"));
            ui->tt1->setPixmap(QPixmap(":/1_files/TowerTop0.png"));
            ui->tt2->setPixmap(QPixmap(":/1_files/TowerTop1.png"));
            ui->tower1->setPixmap((QPixmap(":/1_files/Tower.bmp")));
            ui->tower2->setPixmap((QPixmap(":/1_files/Tower.bmp")));
            ui->w1->setPixmap((QPixmap(":/1_files/Wall.png")));
            ui->w2->setPixmap((QPixmap(":/1_files/Wall.png")));
            ui->pb1->show();
            ui->pb2->show();
            ui->pb3->show();
            ui->pb4->show();
            ui->pb5->show();
            ui->pb6->show();
                fresh();
                preplayer=1;
                show1(player1);
                connect(ui->pb1,&QPushButton::clicked,this,&MainWindow::slot01);
                connect(ui->pb2,&QPushButton::clicked,this,&MainWindow::slot02);
                connect(ui->pb3,&QPushButton::clicked,this,&MainWindow::slot03);
                connect(ui->pb4,&QPushButton::clicked,this,&MainWindow::slot04,Qt::UniqueConnection);
                connect(ui->pb5,&QPushButton::clicked,this,&MainWindow::slot05,Qt::UniqueConnection);
                connect(ui->pb6,&QPushButton::clicked,this,&MainWindow::slot06,Qt::UniqueConnection);
                connect(ui->y,&QPushButton::clicked,this,&MainWindow::sloty,Qt::UniqueConnection);
                connect(ui->z,&QPushButton::clicked,this,&MainWindow::slotz,Qt::UniqueConnection);


     }
}
 }
int  MainWindow::operate(player &p1,player &p2,card cards[],int n)//玩家操作
{

        int i;
        int a;
        show1(p1);
        a=p1.num[n-1];//n=卡牌编号
        if(n)i=check(n,p1,cards);
        if(n)
        {
            if(i==0)//可出可弃
            {
                QMessageBox *m1=new QMessageBox;
                        m1->show();
                       int ret=QMessageBox::question(this,"是否出牌","yes出No弃",QMessageBox::Yes|QMessageBox::No);
                       switch(ret){
                       case QMessageBox::Yes://出牌
                           ui->cardlast->setPixmap(QPixmap(cardpic(p1.num[n-1])));
                           enforce(p1,p2,cards,p1.num[n-1]);
                           fresh();
                           p1.num[n-1]=MainWindow::draw();
                           show1(p1);
                           break;
                       case QMessageBox::No://弃牌
                           p1.num[n-1]=MainWindow::draw();
                            }
            }
            else if(i==1)
                {
                    p1.num[n-1]=MainWindow::draw();
                    ui->cardlast->setPixmap(QPixmap(cardpic(p1.num[n-1])));
                }
            else if(i==2)
                {
                    p1.num[n-1]=MainWindow::draw();
                }
            show1(player1);
            if(p1.again)
            {
                p1.again=0;
                flag=1;
            }
          }
        opcard=0;
        }

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::show1(player p1)
{

    ui->card1->setPixmap(QPixmap(cardpic(p1.num[0])));
    ui->card2->setPixmap(QPixmap(cardpic(p1.num[1])));
    ui->card3->setPixmap(QPixmap(cardpic(p1.num[2])));
    ui->card4->setPixmap(QPixmap(cardpic(p1.num[3])));
    ui->card5->setPixmap(QPixmap(cardpic(p1.num[4])));
    ui->card6->setPixmap(QPixmap(cardpic(p1.num[5])));
}
int MainWindow::check(int n,player p1,card cards[])//检查出牌是否符合要求
{
    n--;
    int i;
    n=p1.num[n];//n=卡牌编号
    int mon=cards[n].getmoN();
    int sto=cards[n].getstN();
    int bri=cards[n].getbrN();
    if(mon>p1.mon||sto>p1.sto||bri>p1.bri)
    {
        if(n==34)i=3;//不可出不可弃
        else i=2;//可弃
    }
    else
    {
        if(n==34) i=1;//可出
        else i=0;//可出可弃
    }
    return i;
}
int MainWindow::draw()//随机抽牌
    {
        return rand()%(87);
    }
int MainWindow::endgame(player p1,player p2)
{
    if(round==0)return 3;
    if(p1.tower<0&&p2.tower<0)return 3;
    if(p1.tower<0&&p2.tower>0)return 2;
    if(p1.tower>0&&p2.tower<0)return 1;
    if(p1.tower>50&&p2.tower<50)return 1;
    if(p1.tower>50&&p2.tower>50)return 3;
    if(p1.tower<50&&p2.tower>50)return 2;
    int n1=0,n2=0;
    if(p1.bri<0)n1++;
    if(p1.mon<0)n1++;
    if(p1.sto<0)n1++;
    if(p2.bri<0)n1++;
    if(p2.mon<0)n1++;
    if(p2.sto<0)n1++;
    if(n1>1||n2>1)
    {
        if(n1>n2)return 2;
        else if(n2>n1)return 1;
        else return 3;
    }
    return 0;
}
QString MainWindow::cardpic(int n)
{
    QString str;
    int c1=(n)/29,c2=(n)%29;
        if(c1==0)
        {
            switch(c2)
            {
             case 0:return":/1_files/Card0_00.bmp";
                 break;
             case 1:return":/1_files/Card0_01.bmp";
                 break;
            case 2:return":/1_files/Card0_02.bmp";
                break;
            case 3:return":/1_files/Card0_03.bmp";
                break;
            case 4:return":/1_files/Card0_04.bmp";
                break;
            case 5:return":/1_files/Card0_05.bmp";
                break;
            case 6:return":/1_files/Card0_06.bmp";
                break;
            case 7:return":/1_files/Card0_07.bmp";
                break;
            case 8:return":/1_files/Card0_08.bmp";
                break;
            case 9:return":/1_files/Card0_09.bmp";
                break;
            case 10:return":/1_files/Card0_10.bmp";
                break;
            case 11:return":/1_files/Card0_11.bmp";
                break;
            case 12:return":/1_files/Card0_12.bmp";
                break;
            case 13:return":/1_files/Card0_13.bmp";
                break;
            case 14:return":/1_files/Card0_14.bmp";
                break;
            case 15:return":/1_files/Card0_15.bmp";
                break;
            case 16:return":/1_files/Card0_16.bmp";
                break;
            case 17:return":/1_files/Card0_17.bmp";
                break;
            case 18:return":/1_files/Card0_18.bmp";
                break;
            case 19:return":/1_files/Card0_19.bmp";
                break;
            case 20:return":/1_files/Card0_20.bmp";
                break;
            case 21:return":/1_files/Card0_21.bmp";
                break;
            case 22:return":/1_files/Card0_22.bmp";
                break;
            case 23:return":/1_files/Card0_23.bmp";
                break;
            case 24:return":/1_files/Card0_24.bmp";
                break;
            case 25:return":/1_files/Card0_25.bmp";
                break;
            case 26:return":/1_files/Card0_26.bmp";
                break;
            case 27:return":/1_files/Card0_27.bmp";
                break;
            case 28:return":/1_files/Card0_28.bmp";
                break;
                }
            }
            else if(c1==1)
            {
                switch(c2)
                {
                case 0:return":/1_files/Card1_00.bmp";
                    break;
                case 1:return":/1_files/Card1_01.bmp";
                    break;
               case 2:return":/1_files/Card1_02.bmp";
                   break;
               case 3:return":/1_files/Card1_03.bmp";
                   break;
               case 4:return":/1_files/Card1_04.bmp";
                   break;
               case 5:return":/1_files/Card1_05.bmp";
                   break;
               case 6:return":/1_files/Card1_06.bmp";
                   break;
               case 7:return":/1_files/Card1_07.bmp";
                   break;
               case 8:return":/1_files/Card1_08.bmp";
                   break;
               case 9:return":/1_files/Card1_09.bmp";
                   break;
               case 10:return":/1_files/Card1_10.bmp";
                   break;
               case 11:return":/1_files/Card1_11.bmp";
                   break;
               case 12:return":/1_files/Card1_12.bmp";
                   break;
               case 13:return":/1_files/Card1_13.bmp";
                   break;
               case 14:return":/1_files/Card1_14.bmp";
                   break;
               case 15:return":/1_files/Card1_15.bmp";
                   break;
               case 16:return":/1_files/Card1_16.bmp";
                   break;
               case 17:return":/1_files/Card1_17.bmp";
                   break;
               case 18:return":/1_files/Card1_18.bmp";
                   break;
               case 19:return":/1_files/Card1_19.bmp";
                   break;
               case 20:return":/1_files/Card1_20.bmp";
                   break;
               case 21:return":/1_files/Card1_21.bmp";
                   break;
               case 22:return":/1_files/Card1_22.bmp";
                   break;
               case 23:return":/1_files/Card1_23.bmp";
                   break;
               case 24:return":/1_files/Card1_24.bmp";
                   break;
               case 25:return":/1_files/Card1_25.bmp";
                   break;
               case 26:return":/1_files/Card1_26.bmp";
                   break;
               case 27:return":/1_files/Card1_27.bmp";
                   break;
               case 28:return":/1_files/Card1_28.bmp";
                   break;

                }
            }
            else if(c1==2)
            {
                switch(c2)
                {
                case 0:return":/1_files/Card2_00.bmp";
                    break;
                case 1:return":/1_files/Card2_01.bmp";
                    break;
               case 2:return":/1_files/Card2_02.bmp";
                   break;
               case 3:return":/1_files/Card2_03.bmp";
                   break;
               case 4:return":/1_files/Card2_04.bmp";
                   break;
               case 5:return":/1_files/Card2_05.bmp";
                   break;
               case 6:return":/1_files/Card2_06.bmp";
                   break;
               case 7:return":/1_files/Card2_07.bmp";
                   break;
               case 8:return":/1_files/Card2_08.bmp";
                   break;
               case 9:return":/1_files/Card2_09.bmp";
                   break;
               case 10:return":/1_files/Card2_10.bmp";
                   break;
               case 11:return":/1_files/Card2_11.bmp";
                   break;
               case 12:return":/1_files/Card2_12.bmp";
                   break;
               case 13:return":/1_files/Card2_13.bmp";
                   break;
               case 14:return":/1_files/Card2_14.bmp";
                   break;
               case 15:return":/1_files/Card2_15.bmp";
                   break;
               case 16:return":/1_files/Card2_16.bmp";
                   break;
               case 17:return":/1_files/Card2_17.bmp";
                   break;
               case 18:return":/1_files/Card2_18.bmp";
                   break;
               case 19:return":/1_files/Card2_19.bmp";
                   break;
               case 20:return":/1_files/Card2_20.bmp";
                   break;
               case 21:return":/1_files/Card2_21.bmp";
                   break;
               case 22:return":/1_files/Card2_22.bmp";
                   break;
               case 23:return":/1_files/Card2_23.bmp";
                   break;
               case 24:return":/1_files/Card2_24.bmp";
                   break;
               case 25:return":/1_files/Card2_25.bmp";
                   break;
               case 26:return":/1_files/Card2_26.bmp";
                   break;
               case 27:return":/1_files/Card2_27.bmp";
                   break;
               case 28:return":/1_files/Card2_28.bmp";
                   break;
           }
        }
}
void MainWindow::fresh()
{
    QString str=QString::number(player1.bri);
    ui->p1b->setText(str);
    str=QString::number(player2.bri);
    ui->p2b->setText(str);
    str=QString::number(player1.sto);
    ui->p1s->setText(str);
    str=QString::number(player2.sto);
    ui->p2s->setText(str);
    str=QString::number(player1.mon);
    ui->p1m->setText(str);
    str=QString::number(player2.mon);
    ui->p2m->setText(str);
    str=QString::number(player1.tower);
    ui->p1t->setText(str);
    str=QString::number(player2.tower);
    ui->p2t->setText(str);
    str=QString::number(player1.wall);
    ui->p1w->setText(str);
    str=QString::number(player2.wall);
    ui->p2w->setText(str);
    str=QString::number(player1.incbr);
    ui->p1ib->setText(str);
    str=QString::number(player2.incbr);
    ui->p2ib->setText(str);
    str=QString::number(player1.incst);
    ui->p1is->setText(str);
    str=QString::number(player2.incst);
    ui->p2is->setText(str);
    str=QString::number(player1.incmo);
    ui->p1im->setText(str);
    str=QString::number(player2.incmo);
    ui->p2im->setText(str);
}
void MainWindow::enforce(player &p1,player &p2,card cards[],int n)
    {

        p1.bri-=cards[n].getbrN();
        p1.mon-=cards[n].getmoN();
        p1.sto-=cards[n].getstN();
        int c1=(n)/29,c2=(n)%29;
        if(c1==0)
        {
            switch(c2)
            {
                case 0:
                    p1.bri-=8;p2.bri-=8;
                    break;
                case 1:
                    p1.bri+=2;p1.sto+=2;p1.again=1;
                    break;
                case 2:
                    p1.wall++;p1.again=1;
                    break;
                case 3:
                    p1.incbr++;
                    break;
                case 4:
                    if(p1.incbr<p2.incbr) p1.incbr+=2;
                    else p1.incbr++;
                    break;
                case 5:
                    p1.wall+=4;p1.incbr++;
                    break;
                case 6:
                    p1.wall+=5;p1.sto-=6;
                    break;
                case 7:
                    if(p1.incbr<p2.incbr)p1.incbr=p2.incbr;
                    break;
                case 8:
                    p1.wall+=3;
                    break;
                case 9:
                    p1.wall+=4;
                    break;
                case 10:
                    p1.incbr++;
                    p2.incbr++;
                    p1.sto+=4;
                    break;
                case 11:
                    if(p1.wall)p1.wall+=3;
                    else p1.wall+=6;
                    break;
                case 12:
                    p1.wall-=5;
                    p2.wall-=5;
                    p1.again=1;
                    break;
                case 13:
                    p1.incst++;
                    p1.again=1;
                    break;
                case 14:
                    p1.incbr--;
                    p2.incbr--;
                    break;
                case 15:
                    p1.wall+=6;
                    break;
                case 16:
                    p2.incbr--;
                    break;
                case 17:
                    p1.incbr+=2;
                    break;
                case 18:
                    p1.incbr--;
                    p1.wall+=10;
                    p1.sto+=5;
                    break;
                case 19:
                    p1.wall+=8;
                    break;
                case 20:
                    p1.wall+=5;
                    p1.incmo++;
                    break;
                case 21:
                    if(p1.incst>p2.incst)
                        if(p2.wall>=12)p2.wall-=12;
                        else{p2.tower=p2.tower-12+p2.wall;p2.wall=0;}
                    else
                    if(p2.wall>=8)p2.wall-=8;
                        else{p2.tower=p2.tower-8+p2.wall;p2.wall=0;}
                    break;
                case 22:
                    if(p1.wall<p2.wall)
                    if(p2.wall>=6)p2.wall-=6;
                    else{p2.tower=p2.tower-6+p2.wall;p2.wall=0;}
                    else p2.tower-=6;
                    break;
                case 23:
                    p2.tower-=5;
                    p2.mon-=8;
                    break;
                case 24:
                    if(p2.wall>=8)p2.wall-=8;
                    else{p2.tower=p2.tower-8,p2.wall;p2.wall=0;}
                    p2.incbr--;
                    break;
                case 25:
                    p2.sto-=10;p2.bri-=5;
                    p1.sto+=5;p1.bri+=2;
                    break;
                case 26:
                    if(p2.wall>=10)p2.wall-=10;
                    else{p2.tower=p2.tower-10,p2.wall;p2.wall=0;}
                    p1.incmo--;
                    break;
                case 27:
                    if(p2.wall>=10)p2.wall-=10;
                    else{p2.tower=p2.tower-10,p2.wall;p2.wall=0;}
                    p2.mon-=5;p2.incmo--;
                    break;
                case 28:
                    p1.wall+=9;
                    p1.mon-=5;
                    break;

            }
        }
        else if(c1==1)
        {
            switch(c2)
            {
                case 0:
                    p1.tower++;
                    p1.again=1;
                    break;
                case 1:
                    p2.tower--;
                    p1.again=1;
                    break;
                case 2:
                    p1.tower+=3;
                    break;
                case 3:
                    p1.incst++;
                    break;
                case 4:
                    p1.again++;
                    break;
                case 5:
                    p1.tower+=3;
                    break;
                case 6:
                    p1.tower+=2;
                    p2.tower-=2;
                    break;
                case 7:
                    p1.incst++;
                    p1.tower+=3;
                    p2.tower++;
                    break;
                case 8:
                    p2.tower-=3;
                    break;
                case 9:
                    p1.tower+=5;
                    break;
                case 10:
                    p2.tower-=5;
                    break;
                case 11:
                    p1.incst+=2;
                    p1.tower-=5;
                    break;
                case 12:
                    p1.incst++;p1.tower+=3;p1.wall+=3;
                    break;
                case 13:
                    if(p1.incst>=p2.incst)p2.incst=p1.incst;
                    else p1.incst=p2.incst;
                    break;
                case 14:
                    p1.tower+=8;
                    break;
                case 15:
                    p1.incst++;
                    p1.tower+=5;
                    break;
                case 16:
                    p1.incst--;
                    p2.tower-=9;
                    break;
                case 17:
                    p1.tower+=5;
                    p2.bri-=6;
                    break;
                case 18:
                    p1.tower+=11;
                    break;
                case 19:
                    p1.incst--;
                    p2.incst--;
                    p1.tower-=7;
                    p2.tower-=7;
                    break;
                case 20:
                    p1.tower+=6;
                    p2.tower-=4;
                    break;
                case 21:
                    p1.tower+=7;
                    p1.bri-=10;
                    break;
                case 22:
                    p1.tower+=8;
                    p1.wall+=3;
                    break;
                case 23:
                    p1.tower+=8;
                    p1.incmo++;
                    break;
                case 24:
                    p1.tower+=15;
                    break;
                case 25:
                    p1.tower+=10;
                    p1.wall+=5;
                    p1.mon+=5;
                    break;
                case 26:
                    p1.tower+=12;
                    p2.tower-=6;
                    break;
                case 27:
                    p1.tower+=20;
                    break;
                case 28:
                    p1.tower+=11;
                    p1.wall-=6;
                    break;

            }
        }
        else if(c1==2)
        {
            switch(c2)
            {
                case 0:
                    p1.mon-=6;
                    p2.mon-=6;
                    break;
                case 1:
                    if(p2.wall>=2)p2.wall-=2;
                    else{p2.tower=p2.tower-2+p2.wall;p2.wall=0;}
                    p1.again=1;
                    break;
                case 2:
                    if(p2.wall>=4)p2.wall-=4;
                    else{p2.tower=p2.tower-4+p2.wall;p2.wall=0;}
                    p1.sto-=3;
                    break;
                case 3:
                    p1.incmo++;
                    break;
                case 4:
                    p1.again=1;
                    break;
                case 5:
                    if(p2.wall>=6)p2.wall-=6;
                    else{p2.tower=p2.tower-6+p2.wall;p2.wall=0;}
                    if(p1.wall>=3)p1.wall-=3;
                    else{p1.tower=p1.tower-3,p1.wall;p1.wall=0;}
                    break;
                case 6:
                    p2.tower-=3;p1.tower--;
                    break;
                case 7:
                    p2.tower-=2;
                    p1.again=1;
                    break;
                case 8:
                    if(p2.wall>=5)p2.wall-=5;
                    else{p2.tower=p2.tower-5+p2.wall;p2.wall=0;}
                    break;
                case 9:
                    if(p2.wall>=4)p2.wall-=4;
                    else{p2.tower=p2.tower-4+p2.wall;p2.wall=0;}
                    p1.wall+=3;
                    break;
                case 10:
                    p2.tower-=4;
                    break;
                case 11:
                    p1.incmo+=2;
                    break;
                case 12:
                    if(p2.wall>=2)p2.wall-=2;
                    else{p2.tower=p2.tower-2+p2.wall;p2.wall=0;}
                    p1.wall+=4;
                    p1.tower+=2;
                    break;
                case 13:
                    p1.incmo++;
                    p2.incmo++;
                    p1.mon+=3;
                    break;
                case 14:
                    if(p2.wall>=6)p2.wall-=6;
                    else{p2.tower=p2.tower-6+p2.wall;p2.wall=0;}
                    break;
                case 15:
                    if(p2.wall>=7)p2.wall-=7;
                    else{p2.tower=p2.tower-7+p2.wall;p2.wall=0;}
                    break;
                case 16:
                    if(p2.wall>=6)p2.wall-=6;
                    else{p2.tower=p2.tower-6+p2.wall;p2.wall=0;}
                    p2.mon-=3;
                    break;
                case 17:
                    if(p2.wall>=6)p2.wall-=6;
                    else{p2.tower=p2.tower-6+p2.wall;p2.wall=0;}
                    p1.bri-=5;p2.bri-=5;
                    p1.sto-=5;p2.sto-=5;
                    p1.mon-=5;p2.mon-=5;
                    break;
                case 18:
                    if(p2.wall)
                    {
                        if(p2.wall>=6)p2.wall-=6;
                        else{p2.tower=p2.tower-6+p2.wall;p2.wall=0;}
                    }
                    else p2.tower-=10;
                    break;
                case 19:
                    if(p2.wall>=9)p2.wall-=9;
                    else{p2.tower=p2.tower-9+p2.wall;p2.wall=0;}
                    break;
                case 20:
                    if(p2.wall)
                    {
                        if(p2.wall>=10)p2.wall-=10;
                        else{p2.tower=p2.tower-10+p2.wall;p2.wall=0;}
                    }
                    else p2.tower-=7;
                    break;
                case 21:
                    if(p1.incst>p2.incst)
                        if(p2.wall>=12)p2.wall-=12;
                        else{p2.tower=p2.tower-12+p2.wall;p2.wall=0;}
                    else
                    if(p2.wall>=8)p2.wall-=8;
                        else{p2.tower=p2.tower-8+p2.wall;p2.wall=0;}
                    break;
                case 22:
                    if(p1.wall<p2.wall)
                    if(p2.wall>=6)p2.wall-=6;
                    else{p2.tower=p2.tower-6+p2.wall;p2.wall=0;}
                    else p2.tower-=6;
                    break;
                case 23:
                    p2.tower-=5;
                    p2.mon-=8;
                    break;
                case 24:
                    if(p2.wall>=8)p2.wall-=8;
                    else{p2.tower=p2.tower-8,p2.wall;p2.wall=0;}
                    break;
                case 25:
                    p2.sto-=10;p2.bri-=5;
                    p1.sto+=5;p1.bri+=2;
                    break;
                case 26:
                    if(p2.wall>=10)p2.wall-=10;
                    else{p2.tower=p2.tower-10,p2.wall;p2.wall=0;}
                    break;
                case 27:
                    if(p2.wall>=10)p2.wall-=10;
                    else{p2.tower=p2.tower-10,p2.wall;p2.wall=0;}
                    p2.mon-5;p2.incmo--;
                    break;
                case 28:
                    if(p2.wall>=20)p2.wall-=20;
                    else{p2.tower=p2.tower-20,p2.wall;p2.wall=0;}
                    p2.sto-=10;p2.incmo--;
                    break;

            }
        }
    }
