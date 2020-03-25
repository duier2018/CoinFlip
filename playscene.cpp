#include "playscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QSound>

PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
{

}

PlayScene::PlayScene(int index)
{
    //设置当前等级
    m_levalIndex = index;
    //设置固定窗口大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("翻金币");
    //创建菜单栏
    QMenuBar * bar = menuBar();
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
        //返回按钮音效播放
        backSound->play();
        QTimer::singleShot(300,this,[=](){
            hide();
            //触发自定义信号，关闭自身，该信号写到signals下做声明
            emit playSceneBack();
        });
    });

    //当前关卡标题
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str = QString("Level: %1").arg(m_levalIndex);
    label->setText(str);
    //设置位置和大小
    label->setGeometry(QRect(100, height()-40, 150, 40));

    //胜利图片显示
    QLabel * winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5, -tmpPix.height());

    //初始化二维数组
    dataConfig config;
    for(int i = 0;i < 4;i++)
    {
        for(int j = 0;j < 4;j++)
        {
            m_gameArray[i][j] = config.mData[m_levalIndex][i][j];
        }
    }

    //翻金币音效
    QSound * flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利音效
    QSound * winSound = new QSound(":/res/LevelWinSound.wav",this);
    //创建金币的背景图片
    for(int i = 0;i < 4;i++)
    {
        for(int j = 0;j < 4;j++)
        {
            //绘制背景图片
            QLabel * label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->setParent(this);
            label->move(57+i*50, 200+j*50);
            //金币对象
            QString img;
            if(m_gameArray[i][j] == 1)
            {
                img = ":/res/Coin0001.png";
            }
            else
            {
                img = ":/res/Coin0008.png";
            }
            MyCoin * coin = new MyCoin(img);
            coin->setParent(this);
            coin->move(59+i*50, 204+j*50);
            //记录x坐标
            coin->m_posX = i;
            //记录y坐标
            coin->m_posY = j;
            //记录正反标志
            coin->m_flag = m_gameArray[i][j];
            //记录每隔按钮的位置
            m_coinBtn[i][j] = coin;

            connect(coin,&MyCoin::clicked,[=](){
                //翻金币音效播放
                flipSound->play();
                coin->changeFlag();
                //数组内部记录的标志同步修改
                m_gameArray[i][j] = m_gameArray[i][j] == 0 ? 1 : 0;

                //延时翻动其他周围金币
                QTimer::singleShot(300,this,[=](){
                    if(coin->m_posX+1 <= 3)
                    {
                        m_coinBtn[coin->m_posX+1][coin->m_posY]->changeFlag();
                        m_gameArray[coin->m_posX+1][coin->m_posY] =
                                m_gameArray[coin->m_posX+1][coin->m_posY] == 0 ? 1 : 0;
                    }
                    if(coin->m_posX-1 >= 0)
                    {
                        m_coinBtn[coin->m_posX-1][coin->m_posY]->changeFlag();
                        m_gameArray[coin->m_posX-1][coin->m_posY] =
                                m_gameArray[coin->m_posX-1][coin->m_posY] == 0 ? 1 : 0;
                    }
                    if(coin->m_posY+1 <= 3)
                    {
                        m_coinBtn[coin->m_posX][coin->m_posY+1]->changeFlag();
                        m_gameArray[coin->m_posX][coin->m_posY+1] =
                                m_gameArray[coin->m_posX][coin->m_posY+1] == 0 ? 1 : 0;
                    }
                    if(coin->m_posY-1 >= 0)
                    {
                        m_coinBtn[coin->m_posX][coin->m_posY-1]->changeFlag();
                        m_gameArray[coin->m_posX][coin->m_posY-1] =
                                m_gameArray[coin->m_posX][coin->m_posY-1] == 0 ? 1 : 0;
                    }

                    m_isWin = true;
                    for(int i = 0;i < 4;i++)
                    {
                        for(int j = 0;j < 4;j++)
                        {
                            if(m_coinBtn[i][j]->m_flag == false)
                            {
                                m_isWin = false;
                                break;
                            }
                        }
                    }

                    if(m_isWin == true)
                    {
                        //播放胜利音效
                        winSound->play();
                        QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),
                                                       winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,
                                                     winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();

                        //禁用所有金币的点击事件
                        for(int i = 0;i < 4;i++)
                        {
                            for(int j = 0;j < 4;j++)
                            {
                                m_coinBtn[i][j]->m_isWin = true;
                            }
                        }
                    }
                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    //绘制背景图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,width(),height(),pix);
    //绘制标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}

