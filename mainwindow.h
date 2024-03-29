#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QVector>

#include "database.h"
#include "import.h"
#include "playlistview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void importData();
    void exportData();
    void setupMenu();
    void toPll();
    Import *import;
    PlaylistView *pll;
    Ui::MainWindow *ui;
    DataBase *db;
};
#endif // MAINWINDOW_H
