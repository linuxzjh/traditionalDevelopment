#include "realtimecurveqchartwidget.h"
#include <QDateTime>
#include <QDebug>
#include <QLayout>

RealTimeCurveQChartWidget::RealTimeCurveQChartWidget(QWidget *parent)
    : QWidget(parent), minX(0), maxX(300), maxY(100), controlVal(1)
{
    initScene();
    initChart1View();
    initChart2View();
    initLayout();
    timerId = startTimer(100);
    qsrand(QDateTime::currentDateTime().toTime_t());
}

void RealTimeCurveQChartWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerId) {
    int newData = qrand() % (maxY + 1);
    dataReceived(newData);
    }
}

void RealTimeCurveQChartWidget::initScene()
{
//    scene = new QGraphicsScene(0, 0, 500, 400);
//    scene.addItem(chart);
//    QGraphicsView view(&scene);
//    view.show();
}

void RealTimeCurveQChartWidget::initChart1View()
{
    splineSeries = new QSplineSeries();
    scatterSeries = new QScatterSeries();
    splineSeries->setUseOpenGL(true);
    scatterSeries->setUseOpenGL(true);
    scatterSeries->setMarkerSize(8);
    chart1 = new QChart();
    chart1->addSeries(splineSeries);
    chart1->addSeries(scatterSeries);
    chart1->legend()->hide();
    chart1->setTitle(tr("Real Time Curve QChart"));

    axisX = new QValueAxis;
    axisX->setRange(minX,maxX);   //设置X坐标范围
    axisX->setMinorTickCount(2);
//    axisX->setTitleText("t/s");  //设置X坐标名字

    axisY = new QValueAxis;
    axisY->setRange(0,maxY);
//    axisY->setTitleText("dis/m");

    chart1->addAxis(axisX, Qt::AlignBottom);
    chart1->addAxis(axisY, Qt::AlignLeft);

    splineSeries->attachAxis(axisX);
    splineSeries->attachAxis(axisY);
    scatterSeries->attachAxis(axisX);
    scatterSeries->attachAxis(axisY);

    chartView1 = new QChartView(chart1);
    chartView1->chart()->setTheme(QChart::ChartThemeBlueCerulean);
    chartView1->setRenderHint(QPainter::Antialiasing);
}

void RealTimeCurveQChartWidget::initChart2View()
{
    chart2 = new QChart();
    stackedBarSeries = new QStackedBarSeries();
    stackedBarSeries->setUseOpenGL(true);

    chart2->addSeries(stackedBarSeries);
    chart2->legend()->hide();
    chart2->setTitle(tr("Real Time Curve QChart"));

    barSet =new QBarSet(tr(""));
    barSet->setColor(Qt::darkRed);

    axisY2 = new QValueAxis;
    axisY2->setRange(0,maxY);
    chart2->addAxis(axisY2, Qt::AlignLeft);

    qDebug () << "controlVal ==>" << (maxX - minX)/controlVal;
    for (int i = 0; i < (maxX - minX)/controlVal; ) {
        m_barXlist << QString::number(i);
        i += controlVal;
        barSet->append(0);
    }
    axisX2 = new QBarCategoryAxis;
    axisX2->append(m_barXlist);
    stackedBarSeries->append(barSet);
    chart2->setAxisX(axisX2,stackedBarSeries); // 将该坐标轴设置为图表的横坐标轴，并将它与条联系起来

    stackedBarSeries->attachAxis(axisX2);
    stackedBarSeries->attachAxis(axisY2);

    chartView2 = new QChartView(chart2);
    chartView2->chart()->setTheme(QChart::ChartThemeBlueCerulean);
    chartView2->setRenderHint(QPainter::Antialiasing);
}

void RealTimeCurveQChartWidget::initLayout()
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(chartView1);
    layout->addWidget(chartView2);
    layout->setMargin(0);
    setLayout(layout);
}

void RealTimeCurveQChartWidget::dataReceived(int value)
{
    minX += controlVal;
    maxX += controlVal;
    data.append(QPointF(maxX, value));

    barSet->append(value);
    barSet->remove(0);
    m_barXlist.append(QString::number(maxX));
    m_barXlist.removeFirst();
    axisX2->clear();
    axisX2->append(m_barXlist);
    qDebug() << m_barXlist.at(0);

    while (! data.isEmpty()  && data.first().rx() <= minX) {
        data.removeFirst();
    }
    if (isVisible()) {
        splineSeries->append(data.last());
        scatterSeries->append(data.last());
        chart1->axisX()->setRange(minX, maxX);
    }
}
