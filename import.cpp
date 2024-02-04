#include "import.h"
#include "ui_import.h"

Import::Import(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Import)
{
    ui->setupUi(this);
//    QListWidgetItem *item = new QListWidgetItem("Элемент с чекбоксом", ui->listWidget);
//    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
//    item->setCheckState(Qt::Unchecked);
}

Import::~Import()
{
    delete ui;
}

void Import::findImportFile()
{
    readImportFile(QFileDialog::getOpenFileName(this, tr("Импорт данных"), "/home" ,tr("pl, *.pl")));
}

void Import::on_pushButton_clicked()
{
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            qDebug() << QString("Элемент %1 отмечен").arg(i+1);
        }
    }
}

void Import::readImportFile(const QString& fileName)
{
    QFile *file = new QFile(fileName);
    file->open(QIODevice::ReadOnly);
    QXmlStreamReader xml(file);
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartElement && xml.name().toString() == "Playlist") {
            qDebug () << xml.readElementText();
         }
    }
}
