#ifndef CPUUSAGEGRAPH_HPP
#define CPUUSAGEGRAPH_HPP

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

class CpuUsageGraph : public QChartView {
    Q_OBJECT

public:
    CpuUsageGraph(QWidget *parent = nullptr);
    void updateChart(double cpuUsage);

private:
    QLineSeries *series;
    QChart *chart;
};

#endif // CPUUSAGEGRAPH_HPP
