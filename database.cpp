#include "database.h"

void DataBase::openDataBase()
{
  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("TestData.db");
  if (!db.open()) {
      qDebug() << "No opened.";
  } else {
      qDebug() << "Open!";
      QSqlQuery query("PRAGMA foreign_keys = ON");
      query.exec();
  }
}

void DataBase::createTables()
{
    createFilmsTable();
    createTlrsTable();
    createPlaylistsTable();
    createFilmTlrTable();
    createPlaylistTlrFilmTable();
}

bool DataBase::createFilmsTable()
{
    if (!db.tables(QSql::AllTables).contains("FILMS")) {
    QSqlQuery query("CREATE TABLE FILMS ("
                    "id INTEGER,"
                    "name TEXT NOT NULL,"
                    "format INTEGER,"
                    "duration INTEGER,"
                    "titleTime INTEGER,"
                    "volume INTEGER,"
                    "PRIMARY KEY (id AUTOINCREMENT)"
                    ")");
    return !query.exec();
    } else return 1;
}

bool DataBase::createTlrsTable()
{
    if (!db.tables(QSql::AllTables).contains("TLRS")) {
        QSqlQuery query("CREATE TABLE TLRS ("
                        "id INTEGER,"
                        "name TEXT NOT NULL,"
                        "duration INTEGER,"
                        "volume INTEGER,"
                        "PRIMARY KEY (id AUTOINCREMENT)"
                        ")");
        return !query.exec();
    } else return 1;
}

bool DataBase::createPlaylistsTable()
{
    if (!db.tables(QSql::AllTables).contains("PLAYLISTS")) {
        QSqlQuery query("CREATE TABLE PLAYLISTS ("
                        "id INTEGER,"
                        "name TEXT NOT NULL,"
                        "PRIMARY KEY (id AUTOINCREMENT)"
                        ")");
        return !query.exec();
    } else return 1;
}

bool DataBase::createFilmTlrTable()
{
    if (!db.tables(QSql::AllTables).contains("FILM_TLR")) {
        QSqlQuery query("CREATE TABLE FILM_TLR ("
                        "film_id INTEGER,"
                        "video_pos INTEGER,"
                        "tlr_id INTEGER,"
                        "PRIMARY KEY (film_id, video_pos),"
                        "FOREIGN KEY (film_id) REFERENCES FILMS(id),"
                        "FOREIGN KEY (tlr_id) REFERENCES TLRS(id)"
                        ")");
        return !query.exec();
    } else return 1;
}

bool DataBase::createPlaylistTlrFilmTable()
{
    if (!db.tables(QSql::AllTables).contains("PLAYLIST_VIDEO")) {
        QSqlQuery query("CREATE TABLE PLAYLIST_VIDEO ("
                        "playlist_id INTEGER,"
                        "video_pos INTEGER,"
                        "film_id INTEGER,"
                        "tlr_id INTEGER,"
                        "PRIMARY KEY (playlist_id, video_pos),"
                        "FOREIGN KEY (playlist_id) REFERENCES PLAYLISTS(id),"
                        "FOREIGN KEY (film_id) REFERENCES FILMS(id),"
                        "FOREIGN KEY (tlr_id) REFERENCES TLRS(id)"
                        ")");
        return !query.exec();
    } else return 1;
}

void DataBase::insertIntoFilms(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO FILMS VALUES (NULL, :name, :format, :duraton, :titlTime, :volume)");
    query.bindValue(":name", data[0].toString());
    query.bindValue(":format", data[1].toInt());
    query.bindValue(":duration", data[2].toInt());
    query.bindValue(":titleTime", data[3].toInt());
    query.bindValue(":volume", data[4].toInt());
    query.exec();
}
