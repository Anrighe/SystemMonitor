#ifndef CPUUSAGEGRAPH_HPP
#define CPUUSAGEGRAPH_HPP

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QAreaSeries>


class CpuUsageGraph : public QChartView {
    Q_OBJECT

public:
    CpuUsageGraph(QWidget *parent = nullptr);
    void updateChart(double cpuUsage);

private:
    QLineSeries *series;
    QLineSeries *areaSeries;    // Series for the ground (Y=0)
    QAreaSeries *area;          // Series for filling the area under the CPU usage line
    QChart *chart;

    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();

    std::atomic<int> graphXAxisInsertElementIndex;
};

#endif // CPUUSAGEGRAPH_HPP
