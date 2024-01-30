#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QVector>

#include "database.h"
#include "filmtime.h"
#include "volume.h"

struct TlrInfo {
  QString name;
  FTime duration;
  Volume volume;
};

struct FilmInfo {
  QString name;
  FTime duration;
  FTime titleTime;
  Volume volume;
  QVector<TlrInfo> tlrs;
};

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
  Ui::MainWindow *ui;
  DataBase *db;
};
#endif // MAINWINDOW_H
