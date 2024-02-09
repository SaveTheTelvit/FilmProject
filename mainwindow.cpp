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
    import = new Import(this, db);
    ui->stackedWidget->addWidget(pll);
    ui->stackedWidget->addWidget(import);
    connect(import, &Import::toMain, this, [this](){ui->stackedWidget->setCurrentWidget(pll);});
    connect(import, &Import::toImport, this, [this](){ui->stackedWidget->setCurrentWidget(import);});
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
}

void MainWindow::exportData()
{
    qDebug() << "export";
}

void MainWindow::toPll()
{
    ui->stackedWidget->setCurrentWidget(pll);
}
