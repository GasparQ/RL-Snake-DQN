#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SnakeWidget w;

    w.init();

    w.show();

    return a.exec();
}
