#include "game_main.h"
#include"herores.h"
#include <QApplication>
#include"ko.h"
#include"start.h"
#include"signin.h"
int main(int argc, char *argv[])
{

   QApplication a(argc, argv);

    Start w;
    w.show();


    return a.exec();

}
