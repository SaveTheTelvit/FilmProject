#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new DataBase;
    db->openDataBase();
    setupMenu();
    pll = new PlaylistView(this);
    import = new Import(this);
    ui->stackedWidget->addWidget(pll);
    ui->stackedWidget->addWidget(import);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupMenu()
{
    QAction *importData = new QAction("Импорировать данные", this);
    QAction *exportData = new QAction("Экспортитровать данные", this);
    ui->menu->addAction(importData);
    ui->menu->addAction(exportData);
    connect(importData, &QAction::triggered, this, &MainWindow::importData);
    connect(exportData, &QAction::triggered, this, &MainWindow::exportData);
}

void MainWindow::importData()
{
    import->findImportFile();
    ui->stackedWidget->setCurrentWidget(import);
}

void MainWindow::exportData()
{
    qDebug() << "export";
}
