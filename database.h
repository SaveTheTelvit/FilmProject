#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QSql>
#include <QSqlDatabase>

class DataBase
{
public:
  void openDataBase();
//  void createFilmsTable();
//  void createTlrsTable();
//  void insertIntoFilmsTable(const QVariantList &data);
//  void insertIntoTlrsTable(const QVariantList &data);
private:
  QSqlDatabase db;
};

#endif // DATABASE_H
