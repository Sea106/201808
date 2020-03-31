#ifndef RANK_H
#define RANK_H
#include<ctime>
#include<QDebug>
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
#include <QWidget>
#include<QFileDialog>
class rank : public QWidget
{
    Q_OBJECT

public:
    explicit rank(QWidget *parent = nullptr);
    QPushButton close;
    void showrank();
    void rank1(int x,QString presentname);
signals:

public slots:
};

#endif // RANK_H















