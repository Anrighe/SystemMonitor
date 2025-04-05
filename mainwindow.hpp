#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "cpu_info.hpp"
#include "ui_mainwindow.h"
#include "cpu_usage_graph.hpp"
#include "cpu_usage_tracker.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CpuInfo cpuInfo;
};
#endif // MAINWINDOW_HPP
