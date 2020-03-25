#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPixmap>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置固定大小
    setFixedSize(320,588);
    //设置应用图片
    setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置窗口标题
    setWindowTitle("duier带你翻金币");

    //点击退出，退出程序
    connect(ui->actionActionQuit,&QAction::triggered,[=](){
        close();
    });

    //创建开始按钮
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(width()*0.5 - startBtn->width()*0.5,height()*0.7);
    //添加开始按钮音效
    QSound * startSound = new QSound(":/res/TapButtonSound.wav",this);

    //选择关卡场景
    ChooseLevelScene * chooseScene = new ChooseLevelScene;

    //监听按钮的点击事件,执行特效
    connect(startBtn,&MyPushButton::clicked,[=](){
        //播放音效
        startSound->play();
        startBtn->zoom1(); //向下跳跃
        startBtn->zoom2(); //向上跳跃

        //延时0.3秒后，进入选择场景
        QTimer::singleShot(300,this,[=](){
            hide();
            chooseScene->setGeometry(geometry());
            chooseScene->show();
        });
        //监听选择场景的返回按钮
        connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
            setGeometry(chooseScene->geometry());
            show();
        });
    });

}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/res/PlayLevelSceneBg.png");
    //绘制背景图
    painter.drawPixmap(0,0,width(),height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    //缩放图片
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    //绘制标题
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
