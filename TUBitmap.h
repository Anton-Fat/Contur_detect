#ifndef TUBITMAP_H
#define TUBITMAP_H

#include <vcl.h>
#include "UBitmap.h"
#pragma hdrstop

namespace Utilities {

// Отправляет данные объекта UBitmap в TBitmap
void operator >> (UBitmap &source, Graphics::TBitmap *target);

// Отправляет данные объекта TBitmap в UBitmap
void operator << (UBitmap &target, Graphics::TBitmap *source);

// Загружает изображение из файла с именем FileName
bool LoadBitmapFromFile(String FileName, UBitmap *target);

// Сохраняет изображение в файл с именем FileName
bool SaveBitmapToFile(String FileName, UBitmap *target);

}
#endif

