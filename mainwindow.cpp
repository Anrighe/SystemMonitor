#include "mainwindow.hpp"
#include "ui_mainwindow.h"

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
}

MainWindow::~MainWindow() {
    delete ui;
}
