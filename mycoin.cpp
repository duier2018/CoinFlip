#include "mycoin.h"
#include <QDebug>

MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
{

}

MyCoin::MyCoin(QString butImg)
{
    QPixmap pixmap;
    bool ret = pixmap.load(butImg);
    if(ret == false)
    {
        qDebug() << butImg << "加载图片失败！";
    }
    setFixedSize(pixmap.width(),pixmap.height());
    setStyleSheet("QPushButton{border:0px;}");
    setIcon(pixmap);
    setIconSize(QSize(pixmap.width(),pixmap.height()));
    //初始化定时器
    m_timer1 = new QTimer(this);
    m_timer2 = new QTimer(this);
    //监听正面翻转的信号
    connect(m_timer1,&QTimer::timeout,[=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg(m_min++);
        pixmap.load(str);
        setFixedSize(pixmap.width(),pixmap.height());
        setStyleSheet("QPushButton{border:0px}");
        setIcon(pixmap);
        setIconSize(QSize(pixmap.width(),pixmap.height()));
        //如果图片路径的最小值大于最大值，重置最小值并停止计时器
        if(m_min > m_max)
        {
            m_min = 1;
            m_timer1->stop();
            m_isAnimation = false;
        }
    });

    //监听反面翻转的信号
    connect(m_timer2,&QTimer::timeout,[=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg(m_max--);
        pixmap.load(str);
        setFixedSize(pixmap.width(),pixmap.height());
        setStyleSheet("QPushButton{border:0px}");
        setIcon(pixmap);
        setIconSize(QSize(pixmap.width(),pixmap.height()));
        //如果图片路径的最大值小于最小值，重置最大值并停止计时器
        if(m_max < m_min)
        {
            m_max = 8;
            m_timer2->stop();
            m_isAnimation = false;
        }
    });
}

void MyCoin::changeFlag()
{
    m_isAnimation = true;
    if(m_flag == true)
    {
        //如果是正面
        m_timer1->start(30);
        m_flag = false;
    }
    else
    {
        //如果是反面
        m_timer2->start(30);
        m_flag = true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(m_isAnimation == true || m_isWin == true)
    {
        //如果正在翻转或者已经胜利 直接返回
        return ;
    }
    else
    {
        //如果没有翻转，交给父类处理
        return QPushButton::mousePressEvent(e);
    }
}

