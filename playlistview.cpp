#include "playlistview.h"
#include "ui_playlistview.h"

PlaylistView::PlaylistView(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::PlaylistView)
{
  ui->setupUi(this);
  QSqlQuery query("SELECT * FROM PLAYLISTS ORDER BY name");
  query.exec();
  int i = 0;
  while (query.next()) {
    playlistIndex.insert(i,query.value(0).toInt());
    new QListWidgetItem(query.value(1).toString(), ui->Playlists);
    ++i;
  }
  connect(ui->Playlists, &QListWidget::currentItemChanged, this, &PlaylistView::test);
}

PlaylistView::~PlaylistView()
{
  delete ui;
}

void PlaylistView::test()
{
  qDebug() << playlistIndex[ui->Playlists->currentRow()];
}
