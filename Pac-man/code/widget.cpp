#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    read();
    ui->a->setPixmap(QPixmap(":/a/back.jpg.png"));
    ui->pac->setPixmap(QPixmap(":/a/pac.png"));
    setWindowTitle("Pacman");
    setFixedSize(800,490);
    bool ok;
    presentname=QInputDialog::getText(NULL,"Playername",
                                      "请输入玩家姓名",
    QLineEdit::Normal,
                                      "Player1",
                                      &ok);
    {if (ok)
     QMessageBox::information(NULL,"Information",
                              "玩家姓名为:<b>"+presentname+"</b>",
                              QMessageBox::Yes|QMessageBox::No,
                              QMessageBox::Yes);
    }
    qDebug()<<presentname;
    ui->opening->setPixmap(QPixmap(":/a/opening.jpg"));
    initialize();
    for(int i=0;i<14;i++)
    {
        for(int j=0;j<19;j++)
        {
            if(lat[i][j]==1)
            {
                lat[i][j]=2;
            }
        }
    }
   int x2,y2;
   for(int i=0;i<3;i++)
   {
       do
       {
           x2=rand()%11+1;
           y2=rand()%16+1;
       }while(lat[x2][y2]!=2);
       lat[x2][y2]=3;
       do
       {
           x2=rand()%11+1;
           y2=rand()%16+1;
       }while(lat[x2][y2]!=2);
       lat[x2][y2]=4;
   }
   read();
    connect(ui->Level1,&QPushButton::clicked,this,&Widget::Level1);
    connect(ui->Level2,&QPushButton::clicked,this,&Widget::Level2);
    connect(ui->Level3,&QPushButton::clicked,this,&Widget::Level3);
}
Widget::~Widget()
{
    delete ui;
}
void Widget::Level1()
{
    Level=1;
    timerId=this->startTimer(100);
    ui->stackedWidget->setCurrentIndex(3);
}
void Widget::Level2()
{
    Level=2;
    timerId=this->startTimer(100);
    ui->stackedWidget->setCurrentIndex(3);
    g2.lives=1;
    g1.lives=1;
}
void Widget::Level3()
{
    Level=3;
    timerId=this->startTimer(100);
    ui->stackedWidget->setCurrentIndex(3);
    g3.lives=1;
    g4.lives=1;
}
void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    //p.drawPixmap(0,0,width(),height(),QPixmap(":/a/back.jpg.png"));
    for(int i=0;i<14;i++)
    {
        for(int j=0;j<19;j++)
        {
            if(lat[i][j]==0)
            {
                p.drawPixmap(widt*j,widt*i,widt,widt,QPixmap(exc(0)));
            }
            if(lat[i][j]==1)
            {
                p.drawPixmap(widt*j,widt*i,widt,widt,QPixmap(exc(1)));
            }
            if(lat[i][j]==2)
            {
                p.drawPixmap(widt*j,widt*i,widt,widt,QPixmap(exc(2)));
            }
            else if(lat[i][j]==3)
            {
                p.drawPixmap(widt*j,widt*i,widt,widt,QPixmap(exc(3)));
            }
            else if(lat[i][j]==4)
            {
                p.drawPixmap(widt*j,widt*i,widt,widt,QPixmap(exc(4)));
            }
            else if(lat[i][j]==7)
            {
                p.drawPixmap(widt*j,widt*i,widt,widt,QPixmap(exc(7)));
            }
            else if(lat[i][j]==8)
            {
                p.drawPixmap(widt*j,widt*i,widt,widt,QPixmap(exc(8)));
            }
            else if(lat[i][j]==9)
            {
                p.drawPixmap(widt*j,widt*i,widt,widt,QPixmap(exc(9)));
            }

        }
    }
    if(pacman.orient==1)
    {
        p.drawPixmap(pacman.x,pacman.y,widt,widt,QPixmap(":/a/p1.png"));
    }
    else if(pacman.orient==2)
    {
        p.drawPixmap(pacman.x,pacman.y,widt,widt,QPixmap(":/a/p2.png"));
    }
    else if(pacman.orient==3)
    {
        p.drawPixmap(pacman.x,pacman.y,widt,widt,QPixmap(":/a/p3.png"));
    }
    else if(pacman.orient==4||pacman.orient==0)
    {
        p.drawPixmap(pacman.x,pacman.y,widt,widt,QPixmap(":/a/p4.png"));
    }
    if(g1.lives)
    {
        p.drawPixmap(g1.x,g1.y,widt,widt,QPixmap(":/a/blueg.png"));
    }
    if(g2.lives)
    {
        p.drawPixmap(g2.x,g2.y,widt,widt,QPixmap(":/a/greeng.png"));
    }
    if(g3.lives)
    {
        p.drawPixmap(g3.x,g3.y,widt,widt,QPixmap(":/a/greyg.png"));
    }
    if(g4.lives)
    {
        p.drawPixmap(g4.x,g4.y,widt,widt,QPixmap(":/a/purpleg.png"));
    }

}
QString Widget::img(int i, int j)
{
    if(lat[i][j]==1)
    {
        return ":/a/bean.jpg";
    }

    else if(lat[i][j]==2)
    {
        return ":/a/gold.jpg";
    }
    else if(lat[i][j]==3)
    {
        return ":/a/blue.jpg";
    }
}
void Widget::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_A)
    {
        if(lat[pacman.y/widt][int(pacman.x/wid-0.1)]==0||lat[int(pacman.y/wid+0.9)][int(pacman.x/wid-0.1)]==0||lat[pacman.y/widt][int(pacman.x/wid-0.1)]==8||lat[int(pacman.y/wid+0.9)][int(pacman.x/wid-0.1)]==8)//撞墙
        {
            preo=3;
        }
        else
        {
            pacman.orient=3;
        }
    }
    else if(ev->key()==Qt::Key_W)
    {
        if(lat[int(pacman.y/wid-0.1)][pacman.x/widt]==0||lat[int(pacman.y/wid-0.12)][int(pacman.x/wid+0.9)]==0)//撞墙
        {
            preo=1;
        }
        else
        {
            pacman.orient=1;
        }
    }
    else if(ev->key()==Qt::Key_S)
    {
        if(lat[int(pacman.y/wid+1+0.1)][pacman.x/widt]==0||lat[int(pacman.y/wid+1+0.1)][int(pacman.x/wid+0.9)]==0)//撞墙
        {
            preo=2;
        }
        else
        {
            pacman.orient=2;
        }
    }
    else if(ev->key()==Qt::Key_D)
    {
        if(lat[pacman.y/widt][int(pacman.x/wid+1+0.1)]==0||lat[int(pacman.y/wid+0.9)][int(pacman.x/wid+1+0.1)]==0)//撞墙
        {
            preo=4;
        }
        else
        {
            pacman.orient=4;
        }
    }
}
void Widget::timerEvent(QTimerEvent *ev)
{
    if(pacman.lives==3)//苟命牌
    {
        ui->liv1->setPixmap(QPixmap(":/a/pacman.png"));
    }
    else
    {
        ui->liv1->setPixmap(QPixmap(":/a/blank.png"));
    }
    if(pacman.lives>=2)
    {
        ui->liv2->setPixmap(QPixmap(":/a/pacman.png"));
    }
    else
    {
        ui->liv2->setPixmap(QPixmap(":/a/blank.png"));
    }
    if(pacman.lives>=1)
    {
        ui->liv3->setPixmap(QPixmap(":/a/pacman.png"));
    }
    else
    {
        ui->liv3->setPixmap(QPixmap(":/a/blank.png"));

    }
    if(pacman.lives==0)//挂了
    {
        ui->gameover->setPixmap(QPixmap(":/a/gameover.png"));
        killTimer(this->timerId);

    }
    if(f3==0)//200转
    {
        sec1++;
    }
    if(sec1>=10)
    {
        sec1=0;
        f3=1;
    }
    if(f4==0)//210转
    {
        sec1++;
    }
    if(sec1>=10)
    {
        sec1=0;
        f4=1;
    }
    if(f5==0)//300转
    {
        sec2++;
    }
    if(sec2>=10)
    {
        sec2=0;
        f5=1;
    }
    if(f6==0)//310转
    {
        sec3++;
    }
    if(sec3>=10)
    {
        sec3=0;
        f6=1;
    }
    if(Level==2)
    {
        gmove(g2,0);
        gmove(g1,2);
            if((g2.x+10)/widt==(pacman.x+10)/widt&&(g2.y+10)/widt==(pacman.y+10)/widt)
            {
                pacman.lives--;
                pacman.x=9*widt;
                pacman.y=9*widt;
                g2.x=9*widt;
                g2.y=6*widt;
            }
            if((g1.x+10)/widt==(pacman.x+10)/widt&&(g1.y+10)/widt==(pacman.y+10)/widt)
            {
                pacman.lives--;

                pacman.x=9*widt;
                pacman.y=9*widt;
                g1.x=9*widt;
                g1.y=6*widt;
            }
    }
    else if(Level==3)
    {
        gmove(g3,1);
        gmove(g4,3);
        if((g3.x+10)/widt==(pacman.x+10)/widt&&(g3.y+10)/widt==(pacman.y+10)/widt)
        {
            pacman.lives--;
            pacman.x=9*widt;
            pacman.y=9*widt;
            g3.x=9*widt;
            g3.y=6*widt;
        }
        if((g4.x+10)/widt==(pacman.x+10)/widt&&(g4.y+10)/widt==(pacman.y+10)/widt)
        {
            pacman.lives--;
            pacman.x=9*widt;
            pacman.y=9*widt;
            g4.x=9*widt;
            g4.y=6*widt;
        }
    }

    usedtime++;
    QString str=QString::number(pacman.score);//记分牌
    ui->score->setText(str);
    str=QString::number(usedtime/10);
    str=str+'s';
    ui->usedtime->setText(str);
    if(pacman.score>=135)//通关
    {
        rank();

        ui->a->move(0,0);
        killTimer(this->timerId);
        ui->benci->hide();
        ui->presentname->setText(presentname);
        str=QString::number(usedtime/10);
        ui->presentscore->setText(str);
        ui->stackedWidget->setCurrentIndex(2);
        return;
    }
    if(pacman.buff)
    {
        speed=8;
        sec++;
    }
    else
    {
        speed=5;
    }
    if(sec==40)
    {
        pacman.buff=0;
        sec=0;
    }

    if(preo)//试图转向
    {
        turn=1;
        if(preo==1)
        {
            if(lat[int(pacman.y/wid-0.1)][pacman.x/widt]==0||lat[int(pacman.y/wid-0.12)][int(pacman.x/wid+0.9)]==0)//撞墙
            {
                turn=0;
            }
        }
        else if(preo==2)
        {
            if(lat[int(pacman.y/wid+1+0.1)][pacman.x/widt]==0||lat[int(pacman.y/wid+1+0.1)][int(pacman.x/wid+0.9)]==0)//撞墙
            {
                turn=0;
            }
        }
        else if(preo==3)
        {
            if(lat[pacman.y/widt][int(pacman.x/wid-0.1)]==0||lat[int(pacman.y/wid+0.9)][int(pacman.x/wid-0.1)]==0||lat[pacman.y/widt][int(pacman.x/wid-0.1)]==8||lat[int(pacman.y/wid+0.9)][int(pacman.x/wid-0.1)]==8)//撞墙
            {
                turn=0;
            }
        }
        else if(preo==4)
        {
            if(lat[pacman.y/widt][int(pacman.x/wid+1+0.1)]==0||lat[int(pacman.y/wid+0.9)][int(pacman.x/wid+1+0.1)]==0)//撞墙
            {
                turn=0;
            }
        }
        if(turn)
        {
            pacman.orient=preo;
            preo=0;
        }
    }

    if(pacman.orient==1)//上
    {
        if(lat[int(pacman.y/wid-0.1)][pacman.x/widt]==0||lat[int(pacman.y/wid-0.12)][int(pacman.x/wid+0.9)]==0)//撞墙
        {
            pacman.y=int(pacman.y/wid-0.1+1)*widt;
            pacman.x=pacman.x;
        }
        else //不撞墙
        {
            if(lat[int(pacman.y/wid+0.4)][pacman.x/widt]==2)//吃豆
            {
                pacman.score++;
                lat[int(pacman.y/wid+0.4)][pacman.x/widt]=1;
            }
            else if(lat[int(pacman.y/wid+0.4)][pacman.x/widt]==3)//大豆
            {
                pacman.score++;
                pacman.buff=1;
                lat[int(pacman.y/wid+0.4)][pacman.x/widt]=1;
            }
            else if(lat[int(pacman.y/wid+0.4)][pacman.x/widt]==4)//蓝豆
            {
                pacman.score+=3;
                lat[int(pacman.y/wid+0.4)][pacman.x/widt]=1;
            }
            pacman.y-=speed;
        }
    }
    else if(pacman.orient==2)//下
    {
        if(lat[int(pacman.y/wid+1+0.1)][pacman.x/widt]==0||lat[int(pacman.y/wid+1+0.1)][int(pacman.x/wid+0.9)]==0)//撞墙
        {
            pacman.y=int(pacman.y/wid+0.1)*widt;
            pacman.x=pacman.x;
        }
        else //不撞墙
        {
            if(lat[int(pacman.y/wid+1-0.4)][pacman.x/widt]==2)//吃豆
            {
                pacman.score++;
                lat[int(pacman.y/wid+1-0.4)][pacman.x/widt]=1;
            }
            else if(lat[int(pacman.y/wid+1-0.4)][pacman.x/widt]==3)//大豆
            {
                pacman.score++;
                pacman.buff=1;
                lat[int(pacman.y/wid+1-0.4)][pacman.x/widt]=1;
            }
            else if(lat[int(pacman.y/wid+1-0.4)][pacman.x/widt]==4)//蓝豆
            {
                pacman.score+=3;
                lat[int(pacman.y/wid+1-0.4)][pacman.x/widt]=1;
            }
            pacman.y+=speed;
        }
    }
    else if(pacman.orient==3)//左
    {
        if(lat[pacman.y/widt][int(pacman.x/wid-0.1)]==0||lat[int(pacman.y/wid+0.9)][int(pacman.x/wid-0.1)]==0||lat[pacman.y/widt][int(pacman.x/wid-0.1)]==8||lat[int(pacman.y/wid+0.9)][int(pacman.x/wid-0.1)]==8)//撞墙
        {
            pacman.x=int(pacman.x/wid-0.1+1)*widt;
            pacman.y=pacman.y;
        }
        else //不撞墙
        {
            if(lat[pacman.y/widt][int(pacman.x/wid+0.4)]==2)//吃豆
            {
                pacman.score++;
                lat[pacman.y/widt][int(pacman.x/wid+0.4)]=1;
            }
            else if(lat[pacman.y/widt][int(pacman.x/wid+0.4)]==3)//大豆
            {
                pacman.score++;
                pacman.buff=1;
                lat[pacman.y/widt][int(pacman.x/wid+0.4)]=1;
            }
            else if(lat[pacman.y/widt][int(pacman.x/wid+0.4)]==4)//蓝豆
            {
                pacman.score+=3;
                lat[pacman.y/widt][int(pacman.x/wid+0.4)]=1;
            }
            pacman.x-=speed;
        }
    }
    else if(pacman.orient==4)//右
    {

        if(lat[pacman.y/widt][int(pacman.x/wid+1+0.1)]==0||lat[int(pacman.y/wid+0.9)][int(pacman.x/wid+1+0.1)]==0)//撞墙
        {

            pacman.x=int(pacman.x/wid+0.1)*widt;
            pacman.y=pacman.y;
        }
        else //不撞墙
        {

            if(lat[pacman.y/widt][int(pacman.x/wid+1-0.4)]==2)//吃豆
            {
                pacman.score++;
                lat[pacman.y/widt][int(pacman.x/wid+1-0.4)]=1;
            }
            else if(lat[pacman.y/widt][int(pacman.x/wid+1-0.4)]==3)//大豆
            {
                pacman.score++;
                pacman.buff=1;
                lat[pacman.y/widt][int(pacman.x/wid+1-0.4)]=1;
            }
            else if(lat[pacman.y/widt][int(pacman.x/wid+1-0.4)]==4)//蓝豆
            {
                pacman.score+=3;
                lat[pacman.y/widt][int(pacman.x/wid+1-0.4)]=1;
            }
            else if(lat[pacman.y/widt][int(pacman.x/wid+1-0.4)]==9)//蓝豆
            {
                pacman.x=1*widt;
                pacman.y=pacman.y;
            }
            pacman.x+=speed;
        }
    }
    update();
}
void Widget::initialize()
{
    /*
     * 初始化地图
     * lat[i][j]==0:墙
     * 1：空
     * 2：小豆（分数加一）
     * 3：大豆（加速/杀鬼效果）
     * 4：蓝豆（分数加三）
     * 5：人（pacman）
     * 6：鬼
     * 7：出生点
     * 8:gatel
     * 9:gater
     */
    for(int i=0;i<19;i++)
    {
        lat[0][i]=0;
        lat[13][i]=0;
}
    for(int i=1;i<14;i++)
    {
        lat[i][0]=0;
        lat[i][18]=0;
    }
    for(int i=1;i<13;i++)
    {
        for(int j=1;j<18;j++)
        {
            lat[i][j]=1;
        }
    }
    for(int i=5;i<14;i++)
    {
        lat[2][i]=0;
    }
    lat[2][3]=0;
    lat[2][15]=0;
    lat[8][1]=0;
    lat[10][1]=0;
    lat[12][1]=0;
    lat[8][17]=0;
    lat[10][17]=0;
    lat[12][17]=0;
    for(int i=2;i<7;i++)
    {
        lat[i][2]=0;
        lat[i][16]=0;
    }
    for(int i=8;i<12;i++)
    {
        lat[i][3]=0;
        lat[i][5]=0;
        lat[i][13]=0;
        lat[i][15]=0;
    }
    for(int i=7;i<12;i++)
    {
        lat[11][i]=0;
    }
    for(int i=4;i<15;i++)
    {
        lat[4][i]=0;
        lat[6][i]=0;
    }
    lat[4][6]=1;
    lat[4][9]=1;
    lat[4][12]=1;
    lat[6][5]=0;
    lat[6][13]=0;
    lat[6][9]=7;//出生点
    lat[8][7]=0;
    lat[8][8]=0;
    lat[8][10]=0;
    lat[8][11]=0;
    lat[9][7]=0;
    lat[9][8]=0;
    lat[9][10]=0;
    lat[9][11]=0;
    lat[1][0]=8;
    lat[1][18]=9;
    for(int i=0;i<14;i++)
    {
        for(int j=0;j<19;j++)
        {
            if(lat[i][j]==0||lat[i][j]==8||lat[i][j]==9)
            xr[i][j]=0;
            else xr[i][j]=1;
        }
    }
    for(int i=1;i<=13;i++)
        {
            for(int j=1;j<=18;j++)
            {
                if(xr[i][j]!=0)
                {
                    int sum=0;
                    if(xr[i-1][j]!=0)sum++;
                    if(xr[i+1][j]!=0)sum++;
                    if(xr[i][j-1]!=0)sum++;
                    if(xr[i][j+1]!=0)sum++;
                    if(sum>=3)xr[i][j]=2;
                }

            }
        }
    xr[6][9]=2;

}
void Widget::closeEvent(QCloseEvent *ev)//窗口关闭控件
{
    int ret=QMessageBox::question(this,"question","是否需要关闭窗口");
    if(ret==QMessageBox::Yes)
    {
        ev->accept();
    }
    else
    {
        ev->ignore();
    }
}
QString Widget::exc(int i)
{
    if(i==0)
    {
        return ":/a/wall1.png";
    }
    if(i==1)
    {
        return ":/a/empty.jpg";
    }
    if(i==2)
    {
        return ":/a/bean.jpg";
    }
    if(i==3)
    {
        return ":/a/gold.jpg";
    }
    if(i==4)
    {
        return ":/a/blue.jpg";
    }
    if(i==7)
    {
        return ":/a/point.jpg";
    }
    if(i==8)
    {
        return ":/a/gatel.jpg";
    }
    if(i==9)
    {
        return ":/a/gater.jpg";
    }
}
void Widget::read()
{
    if(Level==1)
    {
        QFile file(":/a/Level1.txt");
        if(file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            int a=0;
            while (!file.atEnd())
            {
                QByteArray line=file.readLine();
                QString name2(line);
                name1[a]=name2;
                a++;
            }
        }
        file.close();
        int a=0;
        QFile file1(":/a/Level1s.txt");
        if(file1.open(QIODevice::ReadOnly|QIODevice::Text))
        {

            while (!file1.atEnd())
            {
                QByteArray line=file1.readLine();
                QString str(line);
                score1[a]=str.toDouble();
                a++;
            }
        }
        file1.close();
    }
    else if(Level==2)
    {
        QFile file(":/a/Level2.txt");
        if(file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            int a=0;
            while (!file.atEnd())
            {
                QByteArray line=file.readLine();
                QString name2(line);
                name1[a]=name2;
                a++;
            }
        }
        file.close();
        int a=0;
        QFile file1(":/a/Level2s.txt");
        if(file1.open(QIODevice::ReadOnly|QIODevice::Text))
        {

            while (!file1.atEnd())
            {
                QByteArray line=file1.readLine();
                QString str(line);
                score1[a]=str.toDouble();
                a++;
            }
        }
        file1.close();
    }
    else if(Level==3)
    {
        QFile file(":/a/Level3.txt");
        if(file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            int a=0;
            while (!file.atEnd())
            {
                QByteArray line=file.readLine();
                QString name2(line);
                name1[a]=name2;
                a++;
            }
        }
        file.close();
        int a=0;
        QFile file1(":/a/Level3s.txt");
        if(file1.open(QIODevice::ReadOnly|QIODevice::Text))
        {

            while (!file1.atEnd())
            {
                QByteArray line=file1.readLine();
                QString str(line);
                score1[a]=str.toDouble();
                a++;
            }
        }
        file1.close();
    }

    ui->pn0->setText(name1[0]);
    ui->pn1->setText(name1[1]);
    ui->pn2->setText(name1[2]);
    ui->pn3->setText(name1[3]);
    ui->pn4->setText(name1[4]);
    ui->pn5->setText(name1[5]);
    ui->pn6->setText(name1[6]);
    ui->pn7->setText(name1[7]);
    ui->pn8->setText(name1[8]);
    ui->pn9->setText(name1[9]);
    QString str=QString::number(score1[0]);
    ui->pn0_2->setText(str);
    str=QString::number(score1[1]);
    ui->pn1_2->setText(str);
    str=QString::number(score1[2]);
    ui->pn2_2->setText(str);
    str=QString::number(score1[3]);
    ui->pn3_2->setText(str);
    str=QString::number(score1[4]);
    ui->pn4_2->setText(str);
    str=QString::number(score1[5]);
    ui->pn5_2->setText(str);
    str=QString::number(score1[6]);
    ui->pn6_2->setText(str);
    str=QString::number(score1[7]);
    ui->pn7_2->setText(str);
    str=QString::number(score1[8]);
    ui->pn8_2->setText(str);
    str=QString::number(score1[9]);
    ui->pn9_2->setText(str);

}
void Widget::rank()
{
    presentname+='\n';
    for(int i=0;i<10;i++){
        if(usedtime/10<score1[i]){
            for(int j=8;j>=i;j--){
                name1[j+1]=name1[j];
                score1[j+1]=score1[j];
            }
            name1[i]=presentname;
            score1[i]=usedtime/10;
            break;
        }
    }

    ui->pn0->setText(name1[0]);
    ui->pn1->setText(name1[1]);
    ui->pn2->setText(name1[2]);
    ui->pn3->setText(name1[3]);
    ui->pn4->setText(name1[4]);
    ui->pn5->setText(name1[5]);
    ui->pn6->setText(name1[6]);
    ui->pn7->setText(name1[7]);
    ui->pn8->setText(name1[8]);
    ui->pn9->setText(name1[9]);
    QString str=QString::number(score1[0]);
    ui->pn0_2->setText(str);
    str=QString::number(score1[1]);
    ui->pn1_2->setText(str);
    str=QString::number(score1[2]);
    ui->pn2_2->setText(str);
    str=QString::number(score1[3]);
    ui->pn3_2->setText(str);
    str=QString::number(score1[4]);
    ui->pn4_2->setText(str);
    str=QString::number(score1[5]);
    ui->pn5_2->setText(str);
    str=QString::number(score1[6]);
    ui->pn6_2->setText(str);
    str=QString::number(score1[7]);
    ui->pn7_2->setText(str);
    str=QString::number(score1[8]);
    ui->pn8_2->setText(str);
    str=QString::number(score1[9]);
    ui->pn9_2->setText(str);
    ui->presentname->setText(presentname);
    str=QString::number(usedtime/10);
    ui->presentscore->setText(str);
    if(Level==1)
    {
        QString path=QFileDialog::getSaveFileName(this,"Level1","../a/","TXT(*.txt)");
        if(path.isEmpty()==0)
        {
            QFile file2;
            file2.setFileName(path);
            bool isOK=file2.open(QIODevice::WriteOnly);
            if(isOK==true)
            {
                for(int i=0;i<10;i++)
                {
                    file2.write(name1[i].toUtf8());
                    //file2.write("\n");
                }
            }
        }
        path=QFileDialog::getSaveFileName(this,"Level1s","../a/","TXT(*.txt)");
        if(path.isEmpty()==0)
        {
            QFile file3;
            file3.setFileName(path);
            bool isOK=file3.open(QIODevice::WriteOnly);
            if(isOK==true)
            {
                QString str;
                for(int i=0;i<10;i++)
                {
                    str=QString::number(score1[i]);
                    file3.write(str.toUtf8());
                    file3.write("\n");
                }
            }
        }
    }
    if(Level==2)
    {
        QString path=QFileDialog::getSaveFileName(this,"Level2","../a/","TXT(*.txt)");
        if(path.isEmpty()==0)
        {
            QFile file2;
            file2.setFileName(path);
            bool isOK=file2.open(QIODevice::WriteOnly);
            if(isOK==true)
            {
                for(int i=0;i<10;i++)
                {
                    file2.write(name1[i].toUtf8());
                    //file2.write("\n");
                }
            }
        }
        path=QFileDialog::getSaveFileName(this,"Level2s","../a/","TXT(*.txt)");
        if(path.isEmpty()==0)
        {
            QFile file3;
            file3.setFileName(path);
            bool isOK=file3.open(QIODevice::WriteOnly);
            if(isOK==true)
            {
                QString str;
                for(int i=0;i<10;i++)
                {
                    str=QString::number(score1[i]);
                    file3.write(str.toUtf8());
                    file3.write("\n");
                }
            }
        }
    }
    if(Level==3)
    {
        QString path=QFileDialog::getSaveFileName(this,"Level3","../a/","TXT(*.txt)");
        if(path.isEmpty()==0)
        {
            QFile file2;
            file2.setFileName(path);
            bool isOK=file2.open(QIODevice::WriteOnly);
            if(isOK==true)
            {
                for(int i=0;i<10;i++)
                {
                    file2.write(name1[i].toUtf8());
                    //file2.write("\n");
                }
            }
        }
        path=QFileDialog::getSaveFileName(this,"Level3s","../a/","TXT(*.txt)");
        if(path.isEmpty()==0)
        {
            QFile file3;
            file3.setFileName(path);
            bool isOK=file3.open(QIODevice::WriteOnly);
            if(isOK==true)
            {
                QString str;
                for(int i=0;i<10;i++)
                {
                    str=QString::number(score1[i]);
                    file3.write(str.toUtf8());
                    file3.write("\n");
                }
            }
        }
    }

}

int Widget::incident0(man &g)
{
    int direct[5];
    int sum=0;
    if(lat[int(g.y/wid-0.1)][g.x/widt]!=0&&lat[int(g.y/wid-0.12)][int(g.x/wid+0.9)]!=0)//1撞墙
    {
        sum++;
        direct[sum]=1;
    }
    if(lat[int(g.y/wid+1+0.1)][g.x/widt]!=0&&lat[int(g.y/wid+1+0.1)][int(g.x/wid+0.9)]!=0)//2撞墙
    {
        sum++;
        direct[sum]=2;
    }
    if(lat[g.y/widt][int(g.x/wid-0.1)]!=0&&lat[int(g.y/wid+0.9)][int(g.x/wid-0.1)]!=0&&lat[g.y/widt][int(g.x/wid-0.1)]!=8&&lat[int(g.y/wid+0.9)][int(g.x/wid-0.1)]!=8)//3撞墙
    {
        sum++;
        direct[sum]=3;
    }

    if(lat[g.y/widt][int(g.x/wid+1+0.1)]!=0&&lat[int(g.y/wid+0.9)][int(g.x/wid+1+0.1)]!=0&&lat[g.y/widt][int(g.x/wid+1+0.1)]!=9&&lat[int(g.y/wid+0.9)][int(g.x/wid+1+0.1)]!=9)//4撞墙
    {
        sum++;
        direct[sum]=4;
    }
    direct[0]=direct[rand()%sum+1];
    return direct[0];
}
int Widget::incident1(man &g,man &pacman)
{//当鬼处于路口时进入函数
    int direct[3];
    int sum=0;
    if(lat[int(g.y/wid-0.1)][g.x/widt]!=0&&lat[int(g.y/wid-0.12)][int(g.x/wid+0.9)]!=0&&g.y>=pacman.y)//1撞墙
    {
        sum++;
        direct[sum]=1;
    }
    if(lat[int(g.y/wid+1+0.1)][g.x/widt]!=0&&lat[int(g.y/wid+1+0.1)][int(g.x/wid+0.9)]!=0&&g.y<=pacman.y)//2撞墙
    {
        sum++;
        direct[sum]=2;
    }
    if(lat[g.y/widt][int(g.x/wid-0.1)]!=0&&lat[int(g.y/wid+0.9)][int(g.x/wid-0.1)]!=0&&lat[g.y/widt][int(g.x/wid-0.1)]!=8&&lat[int(g.y/wid+0.9)][int(g.x/wid-0.1)]!=8&&g.x>=pacman.x)//3撞墙
    {
        sum++;
        direct[sum]=3;
    }

    if(lat[g.y/widt][int(g.x/wid+1+0.1)]!=0&&lat[int(g.y/wid+0.9)][int(g.x/wid+1+0.1)]!=0&&lat[g.y/widt][int(g.x/wid+1+0.1)]!=9&&lat[int(g.y/wid+0.9)][int(g.x/wid+1+0.1)]!=9&&g.x<=pacman.x)//4撞墙
    {
        sum++;
        direct[sum]=4;
    }
    direct[0]=direct[rand()%sum+1];
    return direct[0];
}
int Widget::incident2(int &m,int &n,man &pacman)
{//当鬼处于路口时进入函数
    int direct[3];
    int sum=0;
    if(lat[int(m/wid-0.1)][n/widt]!=0&&lat[int(m/wid-0.12)][int(n/wid+0.9)]!=0&&m>=pacman.y)//1撞墙
    {
        sum++;
        direct[sum]=1;
    }
    if(lat[int(m/wid+1+0.1)][n/widt]!=0&&lat[int(m/wid+1+0.1)][int(n/wid+0.9)]!=0&&m<=pacman.y)//2撞墙
    {
        sum++;
        direct[sum]=2;
    }
    if(lat[m/widt][int(n/wid-0.1)]!=0&&lat[int(m/wid+0.9)][int(n/wid-0.1)]!=0&&lat[m/widt][int(n/wid-0.1)]!=8&&lat[int(m/wid+0.9)][int(n/wid-0.1)]!=8&&n>=pacman.x)//3撞墙
    {
        sum++;
        direct[sum]=3;
    }

    if(lat[m/widt][int(n/wid+1+0.1)]!=0&&lat[int(m/wid+0.9)][int(n/wid+1+0.1)]!=0&&lat[m/widt][int(n/wid+1+0.1)]!=9&&lat[int(m/wid+0.9)][int(n/wid+1+0.1)]!=9&&n<=pacman.x)//4撞墙
    {
        sum++;
        direct[sum]=4;
    }
    direct[0]=direct[rand()%sum+1];
    return direct[0];
}

int Widget::move(man &g,  int &m,int &n, man &pacman)
{
    int l=0;
    int direct=incident2(m,n,pacman);
    if(direct==1)
        while(lat[int(m/wid-0.1)][n/widt]!=0&&lat[int(m/wid-0.12)][int(n/wid+0.9)]!=0){
            m-=speed;
            l+=speed;
         }
    else if(direct==2)
        while(lat[int(m/wid+1+0.1)][n/widt]!=0&&lat[int(m/wid+1+0.1)][int(n/wid+0.9)]!=0){
            m+=speed;
            l+=speed;
        }
    else if(direct==3)
        while(lat[m/widt][int(n/wid-0.1)]!=0&&lat[int(m/wid+0.9)][int(n/wid-0.1)]!=0&&lat[m/widt][int(n/wid-0.1)]!=8&&lat[int(m/wid+0.9)][int(n/wid-0.1)]!=8){
            n-=speed;
            l+=speed;
        }
    else if(direct==4)
        while(lat[m/widt][int(n/wid+1+0.1)]!=0&&lat[int(m/wid+0.9)][int(n/wid+1+0.1)]!=0&&lat[m/widt][int(n/wid+1+0.1)]!=9&&lat[int(m/wid+0.9)][int(n/wid+1+0.1)]!=9){
            n+=speed;
            l+=speed;
        }
    if(m==pacman.y&&n==pacman.x)return 1;
     else return l+move(g,m,n,pacman);
}
int Widget::incident3 (man &g,man &pacman)
{
    int m=g.y,n=g.x; //记录每一次拐点，
    //最后返回方向
    int p;
    int sum=0;
    int direct[3];
    int length[3];
    if(lat[int(g.y/wid-0.1)][g.x/widt]!=0&&lat[int(g.y/wid-0.12)][int(g.x/wid+0.9)]!=0&&g.y>=pacman.y)//1撞墙
    {
        sum++;
        direct[sum]=1;
    }
    if(lat[int(g.y/wid+1+0.1)][g.x/widt]!=0&&lat[int(g.y/wid+1+0.1)][int(g.x/wid+0.9)]!=0&&g.y<=pacman.y)//2撞墙
    {
        sum++;
        direct[sum]=2;
    }
    if(lat[g.y/widt][int(g.x/wid-0.1)]!=0&&lat[int(g.y/wid+0.9)][int(g.x/wid-0.1)]!=0&&lat[g.y/widt][int(g.x/wid-0.1)]!=8&&lat[int(g.y/wid+0.9)][int(g.x/wid-0.1)]!=8&&g.x>=pacman.x)//3撞墙
    {
        sum++;
        direct[sum]=3;
    }

    if(lat[g.y/widt][int(g.x/wid+1+0.1)]!=0&&lat[int(g.y/wid+0.9)][int(g.x/wid+1+0.1)]!=0&&lat[g.y/widt][int(g.x/wid+1+0.1)]!=9&&lat[int(g.y/wid+0.9)][int(g.x/wid+1+0.1)]!=9&&g.x<=pacman.x)//4撞墙
    {
        sum++;
        direct[sum]=4;
    }
    int l=0;
    for(int i=1;i<=sum;i++){
        if(direct[i]==1)
        while(lat[int(m/wid-0.1)][n/widt]!=0&&lat[int(m/wid-0.12)][int(n/wid+0.9)]!=0&&m>=pacman.y){
            m-=speed;
            l+=speed;
         }
    else if(direct[i]==2)
        while(lat[int(m/wid+1+0.1)][n/widt]!=0&&lat[int(m/wid+1+0.1)][int(n/wid+0.9)]!=0&&m<=pacman.y){
            m+=speed;
            l+=speed;
        }
    else if(direct[i]==3)
        while(lat[m/widt][int(n/wid-0.1)]!=0&&lat[int(m/wid+0.9)][int(n/wid-0.1)]!=0&&lat[m/widt][int(n/wid-0.1)]!=8&&lat[int(m/wid+0.9)][int(n/wid-0.1)]!=8&&m>=pacman.x){
            n-=speed;
            l+=speed;
        }
    else if(direct[i]==4)
        while(lat[m/widt][int(n/wid+1+0.1)]!=0&&lat[int(m/wid+0.9)][int(n/wid+1+0.1)]!=0&&lat[g.y/widt][int(g.x/wid+1+0.1)]!=9&&lat[int(g.y/wid+0.9)][int(g.x/wid+1+0.1)]!=9&&g.x<=pacman.x){
            n+=speed;
            l+=speed;
        }
        length[i]=l+move(g,m,n,pacman);
                if(i==1){
                     length[0]=length[i];
                     p=1;
                }

                else if(length[i]<length[0]){
                    length[0]=length[i];
                    p=i;
                }
    }
    return direct[p];
}
void Widget::gmove(man &g, int incident)
{
    if(f3&&incident==0)
    {
        if(xr[int(g.y/wid)][int(g.x/wid)]==2)
        {
            p[incident]=incident1(g,pacman);
            f3=0;
        }
    }
    if(f4&&incident==2)
    {
        if(xr[int(g.y/wid)][int(g.x/wid)]==2)
        {
            p[incident]=incident0(g);
            f4=0;
        }
    }
    if(f5&&incident==1)
    {
        if(xr[int(g.y/wid)][int(g.x/wid)]==2)
        {
            p[incident]=incident1(g,pacman);
            f5=0;
        }
    }
    if(f6&&incident==3)
    {
        if(xr[int(g.y/wid)][int(g.x/wid)]==2)
        {
            p[incident]=incident0(g);
            f6=0;
        }
    }
    if(p[incident])//试图转向
    {
        int t=1;
        if(p[incident]==1)
        {
            if(lat[int(g.y/wid-0.1)][g.x/widt]==0||lat[int(g.y/wid-0.12)][int(g.x/wid+0.9)]==0)//撞墙
            {
                t=0;
            }
        }
        else if(p[incident]==2)
        {
            if(lat[int(g.y/wid+1+0.1)][g.x/widt]==0||lat[int(g.y/wid+1+0.1)][int(g.x/wid+0.9)]==0)//撞墙
            {
                t=0;
            }
        }
        else if(p[incident]==3)
        {
            if(lat[g.y/widt][int(g.x/wid-0.1)]==0||lat[int(g.y/wid+0.9)][int(g.x/wid-0.1)]==0||lat[g.y/widt][int(g.x/wid-0.1)]==8||lat[int(g.y/wid+0.9)][int(g.x/wid-0.1)]==8)//撞墙
            {
                t=0;
            }
        }
        else if(p[incident]==4)
        {
            if(lat[g.y/widt][int(g.x/wid+1+0.1)]==0||lat[int(g.y/wid+0.9)][int(g.x/wid+1+0.1)]==0)//撞墙
            {
                t=0;
            }
        }
        if(t)
        {
            g.orient=p[incident];
            p[incident]=0;
        }
    }

    if(g.orient==1)//上
    {
        if(lat[int(g.y/wid-0.1)][g.x/widt]==0||lat[int(g.y/wid-0.12)][int(g.x/wid+0.9)]==0)//撞墙
        {
            g.y=int(g.y/wid-0.1+1)*widt;
            g.x=g.x;
            if(incident==0||incident==2)
            {
                p[incident]=incident0(g);
            }
            else if(incident==1)
            {
                p[incident]=incident1(g,pacman);
            }
            else if(incident==3)
            {
                p[incident]=incident1(g,pacman);
            }
        }

        else //不撞墙
        {
            g.y-=5;
        }
    }
    else if(g.orient==2)//下
    {
        if(lat[int(g.y/wid+1+0.1)][g.x/widt]==0||lat[int(g.y/wid+1+0.1)][int(g.x/wid+0.9)]==0)//撞墙
        {
            g.y=int(g.y/wid+0.1)*widt;
            g.x=g.x;
            if(incident==0||incident==2)
            {
                p[incident]=incident0(g);
            }
            else if(incident==1)
            {
                p[incident]=incident1(g,pacman);
            }
            else if(incident==3)
            {
                p[incident]=incident1(g,pacman);
            }
        }
        else //不撞墙
        {
            g.y+=5;
        }
    }
    else if(g.orient==3)//左
    {
        if(lat[g.y/widt][int(g.x/wid-0.1)]==0||lat[int(g.y/wid+0.9)][int(g.x/wid-0.1)]==0||lat[g.y/widt][int(g.x/wid-0.1)]==8||lat[int(g.y/wid+0.9)][int(g.x/wid-0.1)]==8)//撞墙
        {
            g.x=int(g.x/wid-0.1+1)*widt;
            g.y=g.y;
            if(incident==0||incident==2)
            {
                p[incident]=incident0(g);
            }
            else if(incident==1)
            {
                p[incident]=incident1(g,pacman);
            }
            else if(incident==3)
            {
                p[incident]=incident1(g,pacman);
            }
        }
        else //不撞墙
        {
            g.x-=5;
        }
    }
    else if(g.orient==4)//右
    {

        if(lat[g.y/widt][int(g.x/wid+1+0.1)]==0||lat[int(g.y/wid+0.9)][int(g.x/wid+1+0.1)]==0)//撞墙
        {

            g.x=int(g.x/wid+0.1)*widt;
            g.y=g.y;
            if(incident==0||incident==2)
            {
                p[incident]=incident0(g);
            }
            else if(incident==1)
            {
                p[incident]=incident1(g,pacman);
            }
            else if(incident==3)
            {
                p[incident]=incident1(g,pacman);
            }
        }
        else //不撞墙
        {
            g.x+=5;
        }
    }
    update();
}
/*
void Widget::on_music_clicked()
{
    qDebug()<<1;
    mp=new QMediaPlayer;
    mp->setMedia(QMediaContent(QUrl::fromLocalFile("C:/Users/DELL/Desktop/pacman1/a/Boots Randolph - The Benny Hill Show (＂Yakety Sax＂).mp3")));
    mp->setVolume(100);
    mp->play();
}
void Widget::on_mute_clicked()
{
    return;
    mp=new QMediaPlayer;
    mp->setMedia(QUrl::fromLocalFile(":/a/Boots Randolph - The Benny Hill Show (＂Yakety Sax＂).mp3"));
    mp->setVolume(50);
    mp->play();
}
*/

void Widget::on_L1R_clicked()
{
    Level=1;
    read();
    ui->benci->hide();
    ui->stackedWidget->setCurrentIndex(2);
}

void Widget::on_fanhui_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_L2R_clicked()
{
    Level=2;
    read();
    ui->benci->hide();
    ui->stackedWidget->setCurrentIndex(2);
}

void Widget::on_L3R_clicked()
{
    Level=3;
    read();
    ui->benci->hide();
    ui->stackedWidget->setCurrentIndex(2);
}

void Widget::on_back_clicked()
{
    killTimer(this->timerId);
    ui->stackedWidget->setCurrentIndex(0);
    g1.lives=0;
    g2.lives=0;
    g3.lives=0;
    g4.lives=0;
    pacman.lives=3;
    pacman.x=9*35;
    pacman.y=9*35;
    pacman.orient=0;
    ui->gameover->hide();
    initialize();
    usedtime=0;
    pacman.score=0;
    for(int i=0;i<14;i++)
    {
        for(int j=0;j<19;j++)
        {
            if(lat[i][j]==1)
            {
                lat[i][j]=2;
            }
        }
    }
   int x2,y2;
   for(int i=0;i<3;i++)
   {
       do
       {
           x2=rand()%11+1;
           y2=rand()%16+1;
       }while(lat[x2][y2]!=2);
       lat[x2][y2]=3;
       do
       {
           x2=rand()%11+1;
           y2=rand()%16+1;
       }while(lat[x2][y2]!=2);
       lat[x2][y2]=4;
   }
}
