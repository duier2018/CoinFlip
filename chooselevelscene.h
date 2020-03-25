#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChooseLevelScene(QWidget *parent = 0);

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //游戏场景
    PlayScene *m_pScene = NULL;

signals:
    void chooseSceneBack();

public slots:
};

#endif // CHOOSELEVELSCENE_H
