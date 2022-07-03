#ifndef CHOPEO_H
#define CHOPEO_H

#include <QWidget>
#include<QPixmap>
#include"game_main.h"
#include<QTimer>
namespace Ui {
class Chopeo;
}

class Chopeo : public QWidget
{
    Q_OBJECT

public:
    explicit Chopeo(QWidget *parent = nullptr);
    ~Chopeo();
    void paintEvent(QPaintEvent *);
    QPixmap map;
    QPixmap map2;
    int heroleft;
    int heroright;
    QTimer timer;
    void hro();
signals:
    void success();
    void Close();

private slots:


    void on_B2_clicked();

    void on_A3_clicked();

    void on_A4_clicked();

    void on_A5_clicked();

    void on_B3_clicked();

    void on_B4_clicked();

    void on_B5_clicked();

    void on_B1_clicked();

    void on_A1_clicked();

    void on_A2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Chopeo *ui;
};

#endif // CHOPEO_H
