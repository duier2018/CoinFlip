#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = 0);

    //成员变量 记录关卡索引
    int m_levalIndex;

    //重载构造函数
    PlayScene(int index);

    //重载绘图事件
    void paintEvent(QPaintEvent *);

    //二维数组数据
    int m_gameArray[4][4];

    //金币按钮数组
    MyCoin * m_coinBtn[4][4];

    //是否胜利标志
    bool m_isWin = true;

signals:
    //返回信号声明
    void playSceneBack();

public slots:
};

#endif // PLAYSCENE_H
