#include "cpu_usage_graph.hpp"


CpuUsageGraph::CpuUsageGraph(QWidget *parent) : QChartView(parent) {

    // Create the chart object
    chart = new QChart();

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
    axisY->setRange(0, 100); // Set range from 0 to 100%
    axisY->setLabelFormat("%1%"); // Label format to display percentage
    chart->addAxis(axisY, Qt::AlignLeft); // Add the Y-axis to the left

    // Set grid lines for the Y-axis
    axisY->setGridLineVisible(true); // Enable grid lines
    axisY->setMinorGridLineVisible(true); // Enable minor grid lines
    axisY->setMinorTickCount(1); // Increase the number of grid lines (minor grid lines)
    axisY->setLinePen(QPen(Qt::darkGray)); // Set grid line color to light gray
    axisY->setMinorGridLinePen(QPen(Qt::darkGray)); // Set minor grid line color

    // Remove axis labels by setting the labels to an empty list
    axisX->setLabelsVisible(false);  // Hide X-axis labels
    axisY->setLabelsVisible(false);  // Hide Y-axis labels

    // Create and configure X-axis
    axisX->setRange(0, 60); // Set the range for the X-axis
    chart->addAxis(axisX, Qt::AlignBottom); // Add the X-axis to the bottom

    // Set grid lines for the X-axis
    axisX->setGridLineVisible(true); // Enable grid lines
    axisX->setMinorGridLineVisible(true); // Enable minor grid lines
    axisX->setMinorTickCount(4); // Increase the number of grid lines (minor grid lines)
    axisX->setLinePen(QPen(Qt::darkGray)); // Set grid line color to light gray
    axisX->setMinorGridLinePen(QPen(Qt::darkGray)); // Set minor grid line color

    // Create the test series
    series = new QLineSeries();
    updateChart(0.0);
    chart->addSeries(series);

    // Attach axes to the series
    series->attachAxis(axisX); // Attach X-axis to the series
    series->attachAxis(axisY); // Attach Y-axis to the series

    // Make sure the chart view expands to the full size of the widget
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // Expand in both directions

    // Set the chart to the chart view
    setChart(chart);
    setRenderHint(QPainter::Antialiasing);
}

void CpuUsageGraph::updateChart(double cpuUsage) {
    // Updates the series with the new point
    series->append(graphXAxisInsertElementIndex++, cpuUsage);

    if (series->count() > 60) {
        series->remove(0);  // Remove the first (oldest) point
    }

    axisX->setRange(graphXAxisInsertElementIndex - 60, graphXAxisInsertElementIndex);
}
