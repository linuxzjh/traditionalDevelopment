#-------------------------------------------------
#
# Project created by QtCreator 2017-12-13T08:40:36
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Animation
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    chart/themewidget.cpp \
    chart/realtimecurveqchartwidget.cpp
#    plugins/plugin_manager.cpp \
#    plugins/pluginmanagerprivate.cpp

HEADERS  += widget.h \
    chart/themewidget.h \
    chart/realtimecurveqchartwidget.h
#    plugins/plugin.h \
#    plugins/plugin_manager.h \
#    plugins/pluginmanagerprivate.h
