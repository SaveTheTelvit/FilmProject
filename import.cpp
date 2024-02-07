#include "import.h"
#include "ui_import.h"

Import::Import(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Import)
{
    ui->setupUi(this);
}

Import::~Import()
{
    delete ui;
}

void Import::findImportFile()
{
    readImportFile(QFileDialog::getOpenFileName(this, tr("Импорт данных"), "/home" ,tr("pl, *.pl")));
    qDebug() << "Я тута";
    for (int i = 0; i < playlists.size(); ++i) {
      QListWidgetItem *item = new QListWidgetItem(playlists[i].name, ui->listWidget);
      item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
      item->setCheckState(Qt::Unchecked);
      connect(ui->listWidget, &QListWidget::currentItemChanged, this, &Import::currentIndexChanged);
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
    PlaylistInfo playlist = playlists[index];
    for (int i = 0; i < playlist.films.size(); ++i) {
      playlist.tlrs.insert(playlist.films[i].pos, TlrInfo());
    }
    for (int i = 0, j = 0; i < playlist.tlrs.size(); i++) {
      QVector<QString> strings;
      if (playlist.films[j].pos == i) {
        FilmInfo& film = playlist.films[j];
        strings << ("Name: " + film.name) << ("Format: " + QString::number(film.format));
      } else {

      }
    }
}


void Import::readImportFile(const QString& fileName)
{
    QFile *file = new QFile(fileName);
    file->open(QIODevice::ReadOnly);
    QXmlStreamReader xml(file);
    while (!xml.atEnd() && !xml.hasError()) {
        qDebug() << xml.name();
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
  film.pos = xml.attributes()[0].value().toInt();
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
