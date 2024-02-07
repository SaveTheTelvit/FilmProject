#ifndef STRUCTS_H
#define STRUCTS_H

#include <QString>

#include "filmtime.h"
#include "volume.h"

struct TlrInfo {
    QString name;
    FTime duration;
    Volume volume;
};

struct FilmInfo {
    unsigned short pos;
    unsigned short format;
    QString name;
    FTime duration;
    FTime titleTime;
    Volume volume;
    QVector<TlrInfo> tlrs;
};

struct PlaylistInfo {
    QString name;
    QVector<FilmInfo> films;
    QVector<TlrInfo> tlrs;
};

#endif // STRUCTS_H
