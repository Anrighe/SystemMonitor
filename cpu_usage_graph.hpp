#ifndef CPUUSAGEGRAPH_HPP
#define CPUUSAGEGRAPH_HPP

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>


class CpuUsageGraph : public QChartView {
    Q_OBJECT

public:
    CpuUsageGraph(QWidget *parent = nullptr);
    void updateChart(double cpuUsage);

private:
    QLineSeries *series;
    QChart *chart;

    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();
};

#endif // CPUUSAGEGRAPH_HPP
