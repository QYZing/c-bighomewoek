#ifndef START_H
#define START_H

#include <QWidget>
#include <QMovie>
#include<QTimer>
#include<QSoundEffect>
#include"ma.h"
#include"signin.h"
#include"people.h"
namespace Ui {
class Start;
}

class Start : public QWidget
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = nullptr);
    ~Start();
    QMovie *m;
    void output();
    QTimer WINtimer;//游戏帧数
    QSoundEffect *music;
    ma w;//主界面
    Signin s;//登录界面；
    people p;//人物信息


private slots:
    void on_push_clicked();

private:
    Ui::Start *ui;
};
#endif // START_H
