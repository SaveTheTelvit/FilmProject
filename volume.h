#ifndef VOLUME_H
#define VOLUME_H

#include <QString>

#include "textcorrector.h"

class Volume
{
public:
  Volume();
  Volume(float vol);
  Volume(int vol);
  Volume(const QString& str);
  Volume(const char* str);
  QString toStr() const;
private:
  void toVolume(QString str);
  void validate();
  float volume = 0.0f;
};

#endif // VOLUME_H