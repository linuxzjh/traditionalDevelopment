#include "widget.h"
#include "chart/themewidget.h"
#include <QApplication>
#include <QMainWindow>
#include <QPainter>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if 0
    QMainWindow window;
    ThemeWidget *widget = new ThemeWidget();
    window.setCentralWidget(widget);
    window.resize(900, 600);
    window.show();
#endif

#if 1
    Widget w;
    w.show();
#endif

    return a.exec();
}
