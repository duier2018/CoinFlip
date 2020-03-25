#include "chooselevelscene.h"
#include <QPixmap>
#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //设置窗口固定大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("选择关卡");
    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    //创建按钮菜单项
    QAction * quitAction = startMenu->addAction("退出");
    //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        close();
    });

    //返回按钮
    MyPushButton * closeBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    closeBtn->setParent(this);
    closeBtn->move(width()-closeBtn->width(),height()-closeBtn->height());
    //返回按钮音效
    QSound * backSound = new QSound(":/res/BackButtonSound.wav",this);
    //返回按钮功能实现
    connect(closeBtn,&MyPushButton::clicked,[=](){
        QTimer::singleShot(300,this,[=](){
            //返回按钮音效播放
            backSound->play();
            hide();
            emit chooseSceneBack();
        });
    });

    //选择关卡按钮音效
    QSound * chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    //创建关卡按钮
    for(int i = 0;i < 20;i++)
    {
        qDebug() << i;
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+(i%4)*70, 130+(i/4)*70);
        //按钮上显示的文字
        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        //设置居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->move(25+(i%4)*70, 130+(i/4)*70);
        //鼠标穿透事件
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);

        //监听选择关卡按钮的信号
        connect(menuBtn,&MyPushButton::clicked,[=](){
            //选择关卡按钮音效
            chooseSound->play();
            //游戏场景最好不要复用，直接移除掉创建新的场景
            if(m_pScene == NULL)
            {
                hide();
                //将用户所选的关卡号传入PlayScene
                m_pScene = new PlayScene(i+1);
                m_pScene->setGeometry(geometry());
                m_pScene->show();

                //监听PlayScene的返回信号,删除该scene并将指针置空
                connect(m_pScene,&PlayScene::playSceneBack,[=](){
                    setGeometry(m_pScene->geometry());
                    show();
                    delete m_pScene;
                    m_pScene = NULL;
                });
            }
        });
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    //绘制背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,width(),height(),pix);
    //绘制标题
    pix.load(":/res/Title.png");
    painter.drawPixmap( (width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}

