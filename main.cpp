#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString locale = QLocale::system().name();

    QTranslator* translator = new QTranslator(0);
    if(translator->load("WordConverter_"+locale, ":")){
        a.installTranslator(translator);
    }

    MainWindow w;
    w.show();
    return a.exec();
}
