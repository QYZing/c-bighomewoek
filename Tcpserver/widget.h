//widget.h
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <vector>
#include<fstream>
#include"people.h"
#include<QString>
#include<string>
using namespace std;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    QTcpServer* tcpServer;
    vector<QTcpSocket*> socketArr;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    fstream file;//文件存储
    vector<people> p;//读取文件的内容

  int ipa1,ipb1;
    string ipa,ipb;

    void lookofid();//发送找id的信号
    void SGIN();//发送注册信号
public slots:
    void new_connect();
    void read_data();
    //void send_data();
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
