#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Set up application-wide QSettings
    init_localplot_settings();

    QApplication a(argc, argv);
    MainWindow w;

    // Open MainWindow
    w.show();

    // Required setup to pass custom item in signal/slot.
//    qRegisterMetaType<hpgl_obj>("hpgl_obj");
//    qRegisterMetaType<QList<hpgl_obj>>("QList<hpgl_obj>");

    return a.exec();
}
