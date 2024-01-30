#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setWindowTitle("Ухади");
  QAction *importData = new QAction("Импорировать данные", this);
  QAction *exportData = new QAction("Экспортитровать данные", this);
  ui->menu->addAction(importData);
  ui->menu->addAction(exportData);
  connect(importData, &QAction::triggered, this, &MainWindow::importData);
  connect(exportData, &QAction::triggered, this, &MainWindow::exportData);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::importData()
{
  qDebug() << "it's import";
}

void MainWindow::exportData()
{
  qDebug() << "it's export";
}
