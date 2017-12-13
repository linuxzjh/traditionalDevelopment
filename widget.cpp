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
    ExpandWindow(100, 100, this);
}

void Widget::closeEvent(QCloseEvent *event)
{
    CloseWindow();
    event->accept();
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

