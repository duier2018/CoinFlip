#include "mainscene.h"
#include <QApplication>
#include <QResource>
//#include "dataconfig.h"
//#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //注册外部二进制资源文件
    QResource::registerResource("./coinflip.rcc");

    MainScene w;
    w.show();

//    dataConfig config;
//    for(int i = 0;i < 4;i++)
//    {
//        for(int j = 0;j < 4;j++)
//        {
//            //打印第一关所有信息
//            qDebug() << config.mData[1][i][j];
//        }
//        qDebug() << "";
//    }

    return a.exec();
}
