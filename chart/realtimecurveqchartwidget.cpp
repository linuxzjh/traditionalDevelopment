#include "realtimecurveqchartwidget.h"
#include <QDateTime>
#include <QLayout>

RealTimeCurveQChartWidget::RealTimeCurveQChartWidget(QWidget *parent)
    : QWidget(parent), minX(0), maxX(300), maxY(100), controlVal(5)
{
    initChart1View();
    //initChart2View();
    initLayout();
    timerId = startTimer(1000);
    qsrand(QDateTime::currentDateTime().toTime_t());
}

void RealTimeCurveQChartWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerId) {
    int newData = qrand() % (maxY + 1);
    dataReceived(newData);
    }
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
    axisX->setMinorTickCount(6);
    axisX->setTitleText("t/s");  //设置X坐标名字

    axisY = new QValueAxis;
    axisY->setRange(0,maxY);
    axisY->setTitleText("dis/m");

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
    barSeries = new QBarSeries();
    barSeries->setUseOpenGL(true);
    chart2 = new QChart();
    chart2->addSeries(barSeries);
    chart2->legend()->hide();
    chart2->setTitle(tr("Real Time Curve QChart"));

    axisY2 = new QValueAxis;
    axisY2->setRange(0,maxY);

    chart2->addAxis(axisX2, Qt::AlignBottom);
    chart2->addAxis(axisY2, Qt::AlignLeft);

    barSeries->attachAxis(axisX);
    barSeries->attachAxis(axisY);

    barSet =new QBarSet(tr("aaa"));
    barSet->setColor(Qt::blue);
    barSeries->append(barSet);

    QStringList list;
    list<<"在线"<<"离线"<<"报警"<<"总数";
    axisX2 = new QBarCategoryAxis;
    axisX2->append(list);
    chart2->setAxisX(axisX2,barSeries); // 将该坐标轴设置为图表的横坐标轴，并将它与条联系起来

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
    setLayout(layout);
}

void RealTimeCurveQChartWidget::dataReceived(int value)
{
    minX += controlVal;
    maxX += controlVal;
    data.append(QPointF(maxX, value));
    barSet->append(value);
    while (! data.isEmpty()  && data.first().rx() <= minX) {
        data.removeFirst();
        barSet->remove(0);
    }
    if (isVisible()) {
        splineSeries->append(data.last());
        scatterSeries->append(data.last());
        chart1->axisX()->setRange(minX, maxX);
        chart2->axisX()->setRange(minX, maxX);
    }
}
