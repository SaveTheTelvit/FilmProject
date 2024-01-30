#include "database.h"

void DataBase::openDataBase()
{
  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("TestData.db");
  if (!db.open()) {
      qDebug() << "No opened.";
  } else qDebug() << "Open!";
}

