#ifndef KO_H
#define KO_H

#include <QWidget>
#include<QSoundEffect>
#include<QPixmap>
#include<QPaintEvent>
#include<QTimer>
namespace Ui {
class KO;
}

class KO : public QWidget
{
    Q_OBJECT

public:
    explicit KO(QWidget *parent = nullptr);
    ~KO();
    QSoundEffect *music;
    QPixmap map;//背景地图
    void paintEvent(QPaintEvent *);//画图
private slots:



private:
    Ui::KO *ui;
};

#endif // KO_H
