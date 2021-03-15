#ifndef TUBITMAP_H
#define TUBITMAP_H

#include <vcl.h>
#include "UBitmap.h"
#pragma hdrstop

namespace Utilities {

// ���������� ������ ������� UBitmap � TBitmap
void operator >> (UBitmap &source, Graphics::TBitmap *target);

// ���������� ������ ������� TBitmap � UBitmap
void operator << (UBitmap &target, Graphics::TBitmap *source);

// ��������� ����������� �� ����� � ������ FileName
bool LoadBitmapFromFile(String FileName, UBitmap *target);

// ��������� ����������� � ���� � ������ FileName
bool SaveBitmapToFile(String FileName, UBitmap *target);

}
#endif

