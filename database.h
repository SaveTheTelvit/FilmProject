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
    void insertIntoFilms(const QVariantList& data);
    void insertIntoTlrs(const QVariantList& data);
    void insertIntoPlaylists(const QString& name);
    void importPlaylistData(const QVariantList& data);

private:
    bool createFilmsTable();
    bool createTlrsTable();
    bool createPlaylistsTable();
    bool createFilmTlrTable();
    bool createPlaylistTlrFilmTable();
    QSqlDatabase db;
};

#endif // DATABASE_H

