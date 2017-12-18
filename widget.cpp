#include "widget.h"
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
//    OpacityWindow(Order::Ascending, this);
//    DropWindow(this);
    initUI();
}

Widget::~Widget()
{

}

void Widget::OpacityWindow(Order order, QWidget *target)
{
    QPropertyAnimation *pAnimation = new QPropertyAnimation(target, "windowOpacity");
        pAnimation->setDuration(1000);
        if (order == Order::Ascending) {
            pAnimation->setKeyValueAt(0, 0.2);
            pAnimation->setKeyValueAt(0.5, 0.5);
            pAnimation->setKeyValueAt(1, 1);
        } else {
            pAnimation->setKeyValueAt(0, 1);
            pAnimation->setKeyValueAt(0.3, 0.8);
            pAnimation->setKeyValueAt(0.5, 0.5);
            pAnimation->setKeyValueAt(0.85, 0.3);
            pAnimation->setKeyValueAt(1, 0);
        }

        pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Widget::DropWindow(QWidget *target)
{
    QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "geometry");

    QDesktopWidget *pDesktopWidget = QApplication::desktop();
    int x = (pDesktopWidget->availableGeometry().width() - target->width()) / 2;
    int y = (pDesktopWidget->availableGeometry().height() - target->height()) / 2;

    pAnimation->setDuration(1000);
    pAnimation->setStartValue(QRect(x, 0, target->width(), target->height()));
    pAnimation->setEndValue(QRect(x, y, target->width(), target->height()));
    pAnimation->setEasingCurve(QEasingCurve::OutElastic);
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Widget::CloseWindow()
{
#if 0
    int h = target->height();
    int preH = h;
    int cnt = 5;

    while (preH > 2*cnt) {
        preH = preH - 2*cnt;
        move(target->x(), target->y() + cnt);
        resize(this->x(), preH);
    }
    resize(0, 0);
#endif

#if 1
    setMinimumSize(0,0);
    QPropertyAnimation* closeAnimation = new QPropertyAnimation(this,"geometry");
    closeAnimation->setStartValue(geometry());
    closeAnimation->setEndValue(QRect(geometry().x(),geometry().y()+height()/2,width(),0));
    closeAnimation->setDuration(200);
    connect(closeAnimation,SIGNAL(finished()),this,SLOT(close()));
    closeAnimation->start(QAbstractAnimation::DeleteWhenStopped);
#endif
}

void Widget::ExpandWindow(int width, int height, QWidget *target)
{
    QDesktopWidget *pDesktopWidget = QApplication::desktop();
    int x = (pDesktopWidget->availableGeometry().width() - target->width()) / 2;
    int y = (pDesktopWidget->availableGeometry().height() - target->height()) / 2;

    target->setGeometry(x, y, target->width() + width, target->height() + height);

    QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "geometry");
    pAnimation->setStartValue(QRect(pDesktopWidget->availableGeometry().width()/2, pDesktopWidget->availableGeometry().height()/2,
                                    0, 0));
    pAnimation->setEndValue(QRect(x, y, target->width(), target->height()));
    pAnimation->setDuration(300);
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Widget::On_PushButton_expand_Pressed()
{
//    ExpandWindow(100, 100, this);
    ShakeWindow();
}

void Widget::closeEvent(QCloseEvent *event)
{
    CloseWindow();
    event->accept();
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 矩形 300 * 200
    QRectF rect(50, 50, 300, 200);
    QPainterPath path;
    path.addRect(rect);

    // 绘制轮廓
    drawOutline(&painter, path);

    // 绘制原始路径
    drawPath(&painter, path);
}

void Widget::drawOutline(QPainter *painter, QPainterPath path)
{
    // 生成可填充的轮廓
    QPainterPathStroker stroker;
    stroker.setCapStyle(Qt::RoundCap);  // 端点风格
    stroker.setJoinStyle(Qt::RoundJoin);  // 连接样式
    stroker.setDashPattern(Qt::DashLine);  // 虚线图案
    stroker.setWidth(10);  // 宽度

    // 生成一个新路径（可填充区域），表示原始路径 path 的轮廓
    QPainterPath outlinePath = stroker.createStroke(path);

    // 绘制轮廓时所用的画笔（轮廓外边框灰色部分）
    QPen pen = painter->pen();
    pen.setColor(QColor(0, 160, 230));
    pen.setWidth(10);

    // 用指定的画笔 pen 绘制 outlinePath
    // painter->strokePath(outlinePath, pen);
    painter->setPen(pen);
    painter->drawPath(outlinePath);

    // 用指定的画刷 brush 填充路径 outlinePath
    painter->fillPath(outlinePath, QBrush(Qt::yellow));
}


void Widget::drawPath(QPainter *painter, QPainterPath path)
{
    QPen pen = painter->pen();
    pen.setWidth(1);

    // 设置画笔、画刷
    painter->setPen(pen);
    painter->setBrush(QColor(35, 175, 75));

    // 绘制路径
    painter->drawPath(path);
}

void Widget::ShakeWindow()
{
    QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "pos");
    pAnimation->setDuration(400);
    pAnimation->setLoopCount(2);
    pAnimation->setKeyValueAt(0, QPoint(geometry().x() - 3, geometry().y() - 3));
    pAnimation->setKeyValueAt(0.1, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.2, QPoint(geometry().x() - 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.3, QPoint(geometry().x() + 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.4, QPoint(geometry().x() - 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.5, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.6, QPoint(geometry().x() - 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(0.7, QPoint(geometry().x() + 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.8, QPoint(geometry().x() - 6, geometry().y() - 6));
    pAnimation->setKeyValueAt(0.9, QPoint(geometry().x() + 6, geometry().y() + 6));
    pAnimation->setKeyValueAt(1, QPoint(geometry().x() - 3, geometry().y() - 3));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Widget::initUI()
{
    PushButton_expand = new QPushButton(tr("expand"), this);
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(PushButton_expand);
    this->setLayout(hlayout);

    connect(PushButton_expand, SIGNAL(pressed()), this, SLOT(On_PushButton_expand_Pressed()));
}

//void Widget::changeEvent(QEvent *event)
//{
//    if(event->type()!=QEvent::WindowStateChange) return;
//    if(this->windowState()==Qt::WindowMaximized)
//    {
//        expandWindow(this);
//    } else {
//       QWidget::changeEvent(event);
//    }

//}

