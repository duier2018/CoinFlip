#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = 0);
    //normalImg代表正常显示的图片
    //pressImg代表按下后显示的图片,默认为空
    MyPushButton(QString normalImg,QString pressImg = "");

    //默认显示图片路径
    QString m_normalImgPath;
    //按下后显示图片路径
    QString m_pressedImgPath;

    //向上跳跃特效
    void zoom1();
    //向下跳跃特效
    void zoom2();

    //重写鼠标事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
