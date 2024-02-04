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
    QString name;
    FTime duration;
    FTime titleTime;
    Volume volume;
    QVector<TlrInfo> tlrs;
};

struct PlaylistInfo {
    QString name;
    FilmInfo film;
    unsigned short filmPos;
    QVector<TlrInfo> tlrs;
};

#endif // STRUCTS_H
