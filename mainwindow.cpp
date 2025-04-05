#include "mainwindow.hpp"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    CpuInfo cpuInfo;

    ui->setupUi(this);

    connect(ui->btnCpu, &QPushButton::clicked, this, [=]() {
        ui->content->setCurrentWidget(ui->pageCpu);
    });

    connect(ui->btnMemory, &QPushButton::clicked, this, [=]() {
        ui->content->setCurrentWidget(ui->pageMemory);
    });

    ui->cpuName->setText(cpuInfo.getCpuName());
    ui->cpuName->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    CpuUsageGraph *cpuGraph = new CpuUsageGraph(ui->cpuUsageGraph);
    cpuGraph->resize(ui->cpuUsageGraph->size());

    CpuUsageTracker& cpuUsageTracker = CpuUsageTracker::getInstance(cpuGraph);
    cpuUsageTracker.startReadingThread();
}

MainWindow::~MainWindow() {
    delete ui->cpuUsageGraph;
    delete ui;
}
