#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QCloseEvent>
#include <QPainterPath>
#include <QPainter>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
public:
    enum Order {
        Ascending,
        Descending
    };
    void OpacityWindow(Order order, QWidget *target); //窗口渐隐
    void DropWindow(QWidget *target); //窗口下坠
    void CloseWindow(); //向中心闭合
    void ExpandWindow(int width, int height, QWidget *target); //窗口扩展打开
    void ShakeWindow();
public slots:
    void On_PushButton_expand_Pressed();
protected:
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    QPushButton *PushButton_expand;
    void initUI();
    void drawOutline(QPainter *painter, QPainterPath path);
    void drawPath(QPainter *painter, QPainterPath path);
};

#endif // WIDGET_H
