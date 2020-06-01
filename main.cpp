#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
   //srand((int)time(NULL));
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
