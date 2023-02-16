#include "serialassistant.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    serialAssistant w;
    w.show();
    return a.exec();
}
