#ifndef WIDGET_H
#define WIDGET_H
#include<ctime>
//#include<QDebug>
#include <QMainWindow>
#include<QWidget>
#include<QString>
#include<QLabel>
#include<QPalette>
#include <QMainWindow>
#include<QPushButton>
#include<QMessageBox>
#include<QMenu>
#include<QMenuBar>
#include<QToolBar>
#include<QDialog>
#include<QInputDialog>
#include<QImage>
#include<QHBoxLayout>
#include<QPixmap>
#include<QPainter>
#include <QWidget>
#include<QKeyEvent>
#include<QTimer>
#include<QIcon>
#include <QCoreApplication>
#include<QMediaPlayer>
#include<QFileDialog>
#include<QStandardItemModel>
namespace Ui {
class Widget;
}
class man
{
private:
    int type;//人或鬼1人0鬼

public:
    int orient;//运动方位：0不动，1上2下3左4右
    int buff;//是否有加成
    int x,y;//位置
    int lives;//是否存活
    int score;
    man()
    {
        type=0;
        orient=0;
        buff=0;
        x=9*35;
        y=6*35;
        lives=0;
        score=0;
    }
    man(int t,int o,int b,int x1,int y1,int l,int s=0)
    {
        type=t;
        orient=o;
        buff=b;
        x=x1;
        y=y1;
        lives=l;
        score=s;
    }
};
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QString img(int i,int j);
    void initialize();
    void closeEvent(QCloseEvent *event);
    void read();
    void rank();
    int incident0(man &g);
    int incident1(man &g,man &pacman);
    int incident2(int &m,int &n,man &pacman);
    int incident3 (man &g,man &pacman);
    int move(man &g,  int &m,int &n, man &pacman);
    void gmove(man &g,int incident);
private:
    Ui::Widget *ui;
    int lat[14][19];
    int xr[14][19];
    int time1;
    int timerId;
    man pacman=man(1,0,0,9*35,9*35,3);
    man g1,g2,g3,g4;
    int widt=35;
    double wid=35.0;
    int speed=5;
    int preo=0;
    int sec=0;
    int turn;
    int f3=1;
    int f4=1;
    int f5=1;
    int f6=1;
    int sec1=0;
    int sec2=0;
    int sec3=0;
    int p[4]={0};
    QString presentname;
    double usedtime=0;
    QMediaPlayer *mp;
    QMediaPlaylist *mpl;
    QString name1[11];
    double score1[11];
    int Level;
private slots:
    void Level1();
    void Level2();
    void Level3();
    //void on_music_clicked();
    //void on_mute_clicked();
    void on_L1R_clicked();
    void on_fanhui_clicked();
    void on_L2R_clicked();
    void on_L3R_clicked();
    void on_back_clicked();

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *ev);
    void timerEvent(QTimerEvent *ev);
    QString exc(int i);
};

#endif // WIDGET_H



















