#include "import.h"
#include "ui_import.h"

Import::Import(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Import)
{
    ui->setupUi(this);
    connect(ui->listWidget, &QListWidget::currentItemChanged, this, &Import::currentIndexChanged);
    connect(ui->listWidget, &QListWidget::itemActivated, this, [](QListWidgetItem* item)
    {if (item->checkState() == Qt::Unchecked) {item->setCheckState(Qt::Checked);} else item->setCheckState(Qt::Unchecked);});
}
Import::~Import()
{
    delete ui;
}

void Import::findImportFile()
{
    playlists.clear();
    ui->listWidget->clear();
    QString filePath = QFileDialog::getOpenFileName(this, tr("Импорт данных"), "/home" ,tr("tpls(*.tpls)"));
    if (filePath != "") {
        readImportFile(filePath);
        for (int i = 0; i < playlists.size(); ++i) {
            QListWidgetItem *item = new QListWidgetItem(playlists[i].name, ui->listWidget);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
        }
    }
}

void Import::on_pushButton_clicked()
{
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            qDebug() << QString("Элемент %1 отмечен " + item->text()).arg(i+1);
        }
    }
}

void Import::currentIndexChanged()
{
    int index = ui->listWidget->currentRow();
    if (index >= 0 && index < playlists.size()) {
        PlaylistInfo playlist = playlists[index];
        QVector<QString> strings;
        for (int i = 0, n = 0; i < playlist.tlrs.size(); i++) {
            if (n < playlist.films.size() && playlist.films[n].pos == i) {
                FilmInfo& film = playlist.films[n];
                strings << ("Name: " + film.name) << ("Format: " + film.format.toStr()) << ("Duration: " + film.duration.toStr())
                                                  << ("TitleTime: " + film.titleTime.toStr()) << ("Volume: " + film.volume.toStr());
                ++n;
                for (int j = 0; j < film.tlrs.size(); ++j) {
                    strings << ("Tlr " + QString::number(j + 1) + ":");
                    strings << ("Name: " + film.tlrs[j].name) << ("Duration: " + film.tlrs[j].duration.toStr())
                            << ("Volume: " + film.tlrs[j].volume.toStr());
                }
            } else {
                strings << ("Name: " + playlist.tlrs[i].name) << ("Duration: " + playlist.tlrs[i].duration.toStr())
                        << ("Volume: " + playlist.tlrs[i].volume.toStr());
            }
        }
        for (int i = 0; i < strings.size(); ++i) {
            qDebug() << strings[i];
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
        if (token == QXmlStreamReader::StartElement) {
          if (xml.name().toString() == "Playlist") {
              playlists.push_back(readPlaylistInfo(xml));
          }
        }
    }
}

PlaylistInfo Import::readPlaylistInfo(QXmlStreamReader &xml)
{
    PlaylistInfo pll;
        while (!xml.atEnd() && !xml.hasError()) {
            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartElement) {
                QString name = xml.name().toString();
                    if (name == "Name") {
                        pll.name = xml.readElementText();
                    } else if (name == "FilmInfo") {
                        pll.films.push_back(readFilmInfo(xml));
                        pll.tlrs.push_back(TlrInfo());
                        pll.films.last().pos = pll.tlrs.size() - 1;
                    } else if (name == "TlrInfo") {
                        pll.tlrs.push_back(readTlrInfo(xml));
                    }
            } else if (token == QXmlStreamReader::EndElement && xml.name().toString() == "Playlist") {
                return pll;
            }
        }
    return pll;
}

FilmInfo Import::readFilmInfo(QXmlStreamReader &xml)
{
    FilmInfo film;
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartElement) {
            QString name = xml.name().toString();
            if (name == "Name") {
                film.name = xml.readElementText();
            } else if (name == "Format") {
                film.format = xml.readElementText().toInt();
            } else if (name == "Duration") {
                film.duration = FTime(xml.readElementText());
            } else if (name == "TitleTime") {
                film.titleTime = FTime(xml.readElementText());
            } else if (name == "Volume") {
                film.volume = Volume(xml.readElementText());
            } else if (name == "TlrInfo") {
                film.tlrs.push_back(readTlrInfo(xml));
            }
        } else if (token == QXmlStreamReader::EndElement && xml.name().toString() == "FilmInfo") {
            return film;
        }
    }
    return film;
}

TlrInfo Import::readTlrInfo(QXmlStreamReader &xml)
{
    TlrInfo tlr;
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartElement) {
            QString name = xml.name().toString();
            if (name == "Name") {
                tlr.name = xml.readElementText();
            } else if (name == "Duration") {
                tlr.duration = FTime(xml.readElementText());
            } if (name == "Volume") {
                tlr.volume = Volume(xml.readElementText());
            }
        } else if (token == QXmlStreamReader::EndElement && xml.name().toString() == "TlrInfo") {
            return tlr;
        }
    }
    return tlr;
}
