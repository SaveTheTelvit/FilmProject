#include "database.h"

void DataBase::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("TestData.db");
    if (!db.open()) {
        qDebug() << "No opened.";
  } else {
        qDebug() << "Open!";
        QSqlQuery("PRAGMA foreign_keys = ON").exec();
        if (!db.tables(QSql::AllTables).contains("FILMS")) createTables();
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
                        "FOREIGN KEY (film_id) REFERENCES FILMS(id) ON UPDATE CASCADE ON DELETE CASCADE,"
                        "FOREIGN KEY (tlr_id) REFERENCES TLRS(id) ON UPDATE CASCADE ON DELETE CASCADE"
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
                        "FOREIGN KEY (playlist_id) REFERENCES PLAYLISTS(id) ON UPDATE CASCADE ON DELETE CASCADE,"
                        "FOREIGN KEY (film_id) REFERENCES FILMS(id) ON UPDATE CASCADE ON DELETE CASCADE,"
                        "FOREIGN KEY (tlr_id) REFERENCES TLRS(id) ON UPDATE CASCADE ON DELETE CASCADE"
                        ")");
        return !query.exec();
    } else return 1;
}

int DataBase::insertIntoFilms(const QVariantList& data)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM FILMS WHERE name = :name AND "
                  "format = :format AND duration = :duration AND titleTime = :titleTime AND volume = :volume");
    query.bindValue(":name", data[0].toString());
    query.bindValue(":format", data[1].toInt());
    query.bindValue(":duration", data[2].toInt());
    query.bindValue(":titleTime", data[3].toInt());
    query.bindValue(":volume", data[4].toInt());
    query.exec();
    if (!query.first()) {
        query.prepare("INSERT INTO FILMS VALUES (NULL, :name, :format, :duration, :titleTime, :volume)");
        query.bindValue(":name", data[0].toString());
        query.bindValue(":format", data[1].toInt());
        query.bindValue(":duration", data[2].toInt());
        query.bindValue(":titleTime", data[3].toInt());
        query.bindValue(":volume", data[4].toInt());
        query.exec();
        query.exec("SELECT last_insert_rowid()");
        if (query.first()) return query.value(0).toInt();
        return -1;
    }
    return query.value(0).toInt();
}

int DataBase::insertIntoTlrs(const QVariantList& data)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM TLRS WHERE name = :name AND "
                  "duration = :duration AND volume = :volume");
    query.bindValue(":name", data[0].toString());
    query.bindValue(":duration", data[1].toInt());
    query.bindValue(":volume", data[2].toInt());
    query.exec();
    if (!query.first()) {
        query.prepare("INSERT INTO TLRS VALUES (NULL, :name, :duration, :volume)");
        query.bindValue(":name", data[0].toString());
        query.bindValue(":duration", data[1].toInt());
        query.bindValue(":volume", data[2].toInt());
        query.exec();
        query.exec("SELECT last_insert_rowid()");
        if (query.first()) return query.value(0).toInt();
        return -1;
    }
    return query.value(0).toInt();
}

int DataBase::insertIntoPlaylists(const QString& name)
{
    QSqlQuery query("SELECT id FROM PLAYLISTS WHERE name = '" + name +"'");
    if (!query.first()) {
        query.exec("INSERT INTO PLAYLISTS VALUES (NULL,'" + name + "');");
        query.exec("SELECT last_insert_rowid()");
        if (query.first()) return query.value(0).toInt();
        return -1;
    }
    return -1;
}

void DataBase::insertIntoPlaylistFilm(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO PLAYLIST_VIDEO(playlist_id, video_pos, film_id) VALUES (:playlist_id, :pos, :film_id)");
    query.bindValue(":playlist_id", data[0].toInt());
    query.bindValue(":pos", data[1].toInt());
    query.bindValue(":film_id", data[2].toInt());
    query.exec();
}

void DataBase::insertIntoPlaylistTlr(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO PLAYLIST_VIDEO(playlist_id, video_pos, tlr_id) VALUES (:playlist_id, :pos, :tlr_id)");
    query.bindValue(":playlist_id", data[0].toInt());
    query.bindValue(":pos", data[1].toInt());
    query.bindValue(":tlr_id", data[2].toInt());
    query.exec();
}

void DataBase::insertIntoFilmTlr(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO FILM_TLR VALUES (:film_id, :pos, :tlr_id)");
    query.bindValue(":film_id", data[0].toInt());
    query.bindValue(":pos", data[1].toInt());
    query.bindValue(":tlr_id", data[2].toInt());
    query.exec();
}

bool DataBase::importPlaylistData(const PlaylistInfo& playlist)
{
   int playlistID = insertIntoPlaylists(playlist.name);
   if (playlistID != -1) {
       for (int i = 0, n = 0; i < playlist.tlrs.size(); ++i) {
          if (n < playlist.films.size() && playlist.films[n].pos == i) {
             QVariantList filmInfo;
             filmInfo.append(playlist.films[n].name);
             filmInfo.append(playlist.films[n].format.toInt());
             filmInfo.append(playlist.films[n].duration.duration());
             filmInfo.append(playlist.films[n].titleTime.duration());
             filmInfo.append(playlist.films[n].volume.toInt());
             int filmID = insertIntoFilms(filmInfo);
             QVariantList pllFilm;
             pllFilm << playlistID << playlist.films[n].pos << filmID;
             insertIntoPlaylistFilm(pllFilm);
             for (int j = 0; j < playlist.films[n].tlrs.size(); ++j) {
                 QVariantList tlrInfo;
                 tlrInfo.append(playlist.films[n].tlrs[j].name);
                 tlrInfo.append(playlist.films[n].tlrs[j].duration.duration());
                 tlrInfo.append(playlist.films[n].tlrs[j].volume.toInt());
                 int tlrID = insertIntoTlrs(tlrInfo);
                 QVariantList filmTlr;
                 filmTlr << filmID << j << tlrID;
                 insertIntoFilmTlr(filmTlr);
             }
             ++n;
          } else {
              QVariantList tlrInfo;
              tlrInfo.append(playlist.tlrs[i].name);
              tlrInfo.append(playlist.tlrs[i].duration.duration());
              tlrInfo.append(playlist.tlrs[i].volume.toInt());
              int tlrID = insertIntoTlrs(tlrInfo);
              QVariantList pllTlr;
              pllTlr << playlistID << i << tlrID;
              insertIntoPlaylistTlr(pllTlr);
          }
       }
       return true;
   } else return false;
}
