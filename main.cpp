#include "widget.h"
#include "chart/themewidget.h"
#include "chart/realtimecurveqchartwidget.h"
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

#if 0
    Widget w;
    w.show();
#endif

#if 1
    RealTimeCurveQChartWidget w;
    w.resize(700, 600);
    w.show();
#endif
    return a.exec();
}
