#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QWidget *parent = 0);

    //butImag代表图片路径
    MyCoin(QString butImg);

    //x坐标
    int m_posX;
    //y坐标
    int m_posY;
    //正反标志
    bool m_flag;

    //改变标志，执行翻转效果
    void changeFlag();
    //正面翻反面 定时器
    QTimer * m_timer1;
    //反面翻正面 定时器
    QTimer * m_timer2;
    //最小图片
    int m_min = 1;
    //最大图片
    int m_max = 8;

    //胜利标志
    bool m_isWin = false;

    //做翻转动画的标志
    bool m_isAnimation = false;

    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // MYCOIN_H
