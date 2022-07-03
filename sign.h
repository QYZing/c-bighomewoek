#ifndef SIGN_H
#define SIGN_H

#include <QWidget>
#include"people.h"
#include<QPixmap>
namespace Ui {
class sign;
}

class sign : public QWidget
{
    Q_OBJECT

public:
    explicit sign(QWidget *parent = nullptr);
    ~sign();
    people p;
    QPixmap map;
    void paintEvent(QPaintEvent *);
signals:
    void zhuce();//发送注册信号给登录界面
private slots:
    void on_push_clicked();

private:
    Ui::sign *ui;
};

#endif // SIGN_H
