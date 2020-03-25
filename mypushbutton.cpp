#include "mypushbutton.h"
#include <QPixmap>
#include <QDebug>
#include <QPropertyAnimation>
#include <QDebug>
#include <QPushButton>

MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
{

}

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    //成员变量m_normalImgPath 保存正常显示图片路径
    m_normalImgPath = normalImg;
    //成员变量m_pressedImgPath 保存按下后显示图片
    m_pressedImgPath = pressImg;
    //创建QPixmap对象
    QPixmap pixmap;
    //判断是否能够加载正常显示图片，若不能，提示加载失败
    bool ret = pixmap.load(m_normalImgPath);
    if(ret == false)
    {
        qDebug() << normalImg << "加载图片失败！";
    }
    //设置图片尺寸
    setFixedSize(pixmap.width(),pixmap.height());
    //设置不规则图片样式
    setStyleSheet("QPushButton{border:0px}");
    //设置图标
    setIcon(pixmap);
    //设置大小
    setIconSize(QSize(pixmap.width(),pixmap.height()));
}

void MyPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation * animationl = new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    animationl->setDuration(200);
    //创建起始位置
    animationl->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //创建结束位置
    animationl->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
    animationl->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animationl->start();
}

void MyPushButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation * animationl = new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    animationl->setDuration(200);
    //创建开始位置
    animationl->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //创建结束位置
    animationl->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
    animationl->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animationl->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    //选中路径不为空，显示选中图片
    if(m_pressedImgPath != "")
    {
        QPixmap pixmap;\
        bool ret = pixmap.load(m_pressedImgPath);
        if(ret == false)
        {
            qDebug() << m_pressedImgPath << "加载图片失败！";
        }
        setFixedSize(pixmap.width(),pixmap.height());
        setStyleSheet("QPushButton{border:0px}");
        setIcon(pixmap);
        setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    //交给父类执行按下事件
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    //选中路径不为空，显示选中图片
    if(m_normalImgPath != "")
    {
        QPixmap pixmap;\
        bool ret = pixmap.load(m_normalImgPath);
        if(ret == false)
        {
            qDebug() << m_normalImgPath << "加载图片失败！";
        }
        setFixedSize(pixmap.width(),pixmap.height());
        setStyleSheet("QPushButton{border:0px}");
        setIcon(pixmap);
        setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    //交给父类执行释放事件
    return QPushButton::mouseReleaseEvent(e);
}

