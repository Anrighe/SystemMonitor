#include "cpu_usage_graph.hpp"
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

CpuUsageGraph::CpuUsageGraph(QWidget *parent) : QChartView(parent) {

    // Create the chart object
    chart = new QChart();
    chart->createDefaultAxes();

    // Set background color
    QColor backgroundColor = parent ? parent->palette().color(QPalette::Window) : QPalette::ColorRole::Dark;
    chart->setBackgroundBrush(backgroundColor);

    // Hide the legend
    chart->legend()->setVisible(false);

    // Remove margins and background from the chart view
    setContentsMargins(0, 0, 0, 0);
    chart->setMargins(QMargins(0, 0, 0, 0));
    chart->setBackgroundVisible(false);

    // Create and configure Y-axis (percentage)
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100); // Set range from 0 to 100%
    axisY->setLabelFormat("%1%"); // Label format to display percentage
    chart->addAxis(axisY, Qt::AlignLeft); // Add the Y-axis to the left

    // Set grid lines for the Y-axis
    axisY->setGridLineVisible(true); // Enable grid lines
    axisY->setMinorGridLineVisible(true); // Enable minor grid lines
    axisY->setMinorTickCount(1); // Increase the number of grid lines (minor grid lines)
    axisY->setLinePen(QPen(Qt::darkGray)); // Set grid line color to light gray
    axisY->setMinorGridLinePen(QPen(Qt::darkGray)); // Set minor grid line color

    // Create and configure X-axis
    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, 60); // Set the range for the X-axis
    chart->addAxis(axisX, Qt::AlignBottom); // Add the X-axis to the bottom

    // Set grid lines for the X-axis
    axisX->setGridLineVisible(true); // Enable grid lines
    axisX->setMinorGridLineVisible(true); // Enable minor grid lines
    axisX->setMinorTickCount(4); // Increase the number of grid lines (minor grid lines)
    axisX->setLinePen(QPen(Qt::darkGray)); // Set grid line color to light gray
    axisX->setMinorGridLinePen(QPen(Qt::darkGray)); // Set minor grid line color

    // Remove axis labels by setting the labels to an empty list
    axisX->setLabelsVisible(false);  // Hide X-axis labels
    axisY->setLabelsVisible(false);  // Hide Y-axis labels

    // Create the test series
    series = new QLineSeries();
    series->append(99, 99);  // Sample data
    series->append(89, 78);  // Sample data
    series->append(15, 45);  // Sample data
    series->append(0, 0);  // Sample data
    chart->addSeries(series);

    // Attach axes to the series
    series->attachAxis(axisX); // Attach X-axis to the series
    series->attachAxis(axisY); // Attach Y-axis to the series

    // Make sure the chart view expands to the full size of the widget
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // Expand in both directions
    setAlignment(Qt::AlignCenter);  // Center the chart within the widget

    // Set the chart to the chart view
    setChart(chart);
    setRenderHint(QPainter::Antialiasing);
}

void CpuUsageGraph::updateChart(double cpuUsage) {
    // Update the series with new data points, for example:
    static int x = 0;
    series->append(x++, cpuUsage);
}
