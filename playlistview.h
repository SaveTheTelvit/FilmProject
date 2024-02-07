#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QWidget>
#include <QSqlQuery>
#include <QDebug>
#include <QMap>


#include "database.h"
#include "structs.h"

namespace Ui {
  class PlaylistView;
}

class PlaylistView : public QWidget
{
  Q_OBJECT

public:
  explicit PlaylistView(QWidget *parent = nullptr);
  ~PlaylistView();

private:
  void test();
  Ui::PlaylistView *ui;
  DataBase *db;
  QMap<int, int> playlistIndex;
};

#endif // PLAYLISTVIEW_H
