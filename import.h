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

private:
    void readImportFile(const QString& fileName);
    Ui::Import *ui;
    QString importFile;
};

#endif // IMPORT_H
