#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>
#include <QTcpSocket>
#include<string>
#include"people.h"
#include"sign.h"
namespace Ui {
class Signin;
}

class Signin : public QWidget
{
    Q_OBJECT

public:
    explicit Signin(QWidget *parent = nullptr);
    ~Signin();
    QTcpSocket* tcpSocket;//远程发送套接字
    people p;//基本信息
    sign s;//注册信息
signals:
    void success();//登录信号
private slots:
    void on_sign_clicked();
    void connect_success();//发送连接成功信号
    void read_data();//接受登录信息

    void on_push_clicked();

private:
    Ui::Signin *ui;
};

#endif // SIGNIN_H
