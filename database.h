#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

#include "structs.h"

class DataBase
{
public:
    void openDataBase();
    void createTables();
    int insertIntoFilms(const QVariantList& data);
    int insertIntoTlrs(const QVariantList& data);
    int insertIntoPlaylists(const QString& name);
    void insertIntoPlaylistFilm(const QVariantList& data);
    void insertIntoPlaylistTlr(const QVariantList& data);
    void insertIntoFilmTlr(const QVariantList& data);
    bool importPlaylistData(const PlaylistInfo& playlist);

private:
    bool createFilmsTable();
    bool createTlrsTable();
    bool createPlaylistsTable();
    bool createFilmTlrTable();
    bool createPlaylistTlrFilmTable();
    QSqlDatabase db;
};

#endif // DATABASE_H

