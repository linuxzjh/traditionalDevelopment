#include "widget.h"
#include "chart/themewidget.h"
#include <QApplication>
#include <QMainWindow>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if 1
    QMainWindow window;
    ThemeWidget *widget = new ThemeWidget();
    window.setCentralWidget(widget);
    window.resize(900, 600);
    window.show();
#endif

#if 0
    Widget w;
    w.show();
#endif

    return a.exec();
}
