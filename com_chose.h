#ifndef COM_CHOSE_H
#define COM_CHOSE_H

#include <QWidget>
#include<QTimer>
namespace Ui {
class Com_chose;
}

class Com_chose : public QWidget
{
    Q_OBJECT

public:
    explicit Com_chose(QWidget *parent = nullptr);
    ~Com_chose();
public:
    void paintEvent(QPaintEvent *);
    int heroleft;
    int heroright;
    QTimer timer;
    QPixmap map;
    void hro();

signals:
    void success();
    void Close();
private slots:
    void on_A1_clicked();

    void on_A2_clicked();

    void on_A3_clicked();

    void on_A4_clicked();

    void on_A5_clicked();

    void on_pushButton_clicked();


    void on_pushButton_2_clicked();



private:
    Ui::Com_chose *ui;
};

#endif // COM_CHOSE_H
