#ifndef IMPORT_H
#define IMPORT_H

#include <QWidget>
#include <QFileDialog>
#include <QXmlStreamReader>

#include "structs.h"

namespace Ui {
class Import;
}

class Import : public QWidget
{
    Q_OBJECT

public:
    explicit Import(QWidget *parent = nullptr);
    ~Import();
    void findImportFile();

private slots:
    void on_pushButton_clicked();
    void currentIndexChanged();

private:
    void readImportFile(const QString& fileName);
    PlaylistInfo readPlaylistInfo(QXmlStreamReader& xml);
    FilmInfo readFilmInfo(QXmlStreamReader& xml);
    TlrInfo readTlrInfo(QXmlStreamReader& xml);
    Ui::Import *ui;
    QString importFile;
    QVector<PlaylistInfo> playlists;
};

#endif // IMPORT_H
