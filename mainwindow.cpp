#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setWindowTitle("");
  db = new DataBase;
  db->openDataBase();
  db->createTables();
  QVariantList data;
  data.append("Холоп 2");
  data.append(1);
  data.append(2);
  data.append(3);
  data.append(4);
  db->insertIntoFilms(data);
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
  qDebug() << "import";
}

void MainWindow::exportData()
{
  qDebug() << "export";
}
