#ifndef UDP_CHOSE_H
#define UDP_CHOSE_H

#include <QWidget>
#include<QTimer>
#include<string>
using namespace std;
namespace Ui {
class Udp_chose;
}

class Udp_chose : public QWidget
{
    Q_OBJECT

public:
    explicit Udp_chose(QWidget *parent = nullptr);
    ~Udp_chose();
public:
    void paintEvent(QPaintEvent *);
    int hernum;
    int N;
    QTimer timer;
    QPixmap map;
    string str;
    QString read_ip_address();

  //  void hro();
signals:
    void success();
    void Close();
private slots:
    void on_pushButton_clicked();
    void on_A1_clicked();

    void on_A2_clicked();

    void on_A3_clicked();

    void on_A4_clicked();

    void on_A5_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Udp_chose *ui;
};

#endif // UDP_CHOSE_H
