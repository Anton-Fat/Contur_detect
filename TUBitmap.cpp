#ifndef TUBITMAP_CPP
#define TUBITMAP_CPP

#include "TUBitmap.h"

namespace Utilities {


// Отправляет данные объекта UBitmap в TBitmap
void operator >> (UBitmap &source, Graphics::TBitmap *target)
{
 UColorT c;
 struct {
  TLogPalette lpal;
  TPaletteEntry dummy[256];
 } SysPal;
 UBitmap img;

 unsigned char *targetbuf;

 if(!target)
  return;

 target->Height=source.GetHeight();
 target->Width=source.GetWidth();

 if(!source.GetWidth() || !source.GetHeight())
  return;

 switch(source.GetColorModel())
 {
  case ubmColor:
   target->HandleType=bmDIB;
   target->PixelFormat=pf32bit;

   memcpy(target->ScanLine[source.GetHeight()-1],source.GetData(),
		  source.GetLength()*sizeof(UColorT));  break;

  case ubmGray:
   target->HandleType=bmDIB;
   target->PixelFormat=pf32bit;

   memcpy(target->ScanLine[source.GetHeight()-1],source.GetData(),
		  source.GetLength()*sizeof(UColorT));  break;

  case ubmMath:
   img=source;
   img.SetColorModel(ubmGray);
   target->HandleType=bmDIB;
   target->PixelFormat=pf32bit;

   memcpy(target->ScanLine[source.GetHeight()-1],img.GetData(),
		  img.GetLength()*sizeof(UColorT));

/*   target->HandleType=bmDIB;
   target->PixelFormat=pf8bit;     
   SysPal.lpal.palVersion = 0x300;
   SysPal.lpal.palNumEntries = 256;
   for(int i=0;i<256;i++)
	SysPal.dummy[i].peRed=SysPal.dummy[i].peGreen=SysPal.dummy[i].peBlue=i;

   target->Palette = CreatePalette((const tagLOGPALETTE *)&SysPal.lpal);
   targetbuf=(unsigned char*)target->ScanLine[target->Height-1];
   UColorT cc=0;
   for(int i=0;i<source.GetLength();i++)
   {
    cc=source.GetData()[i].c;
    cc.d=0;
    targetbuf[i]=cc.c;
   }     */

  break;
 }
}

// Отправляет данные объекта TBitmap в UBitmap
void operator << (UBitmap &target, Graphics::TBitmap *source)
{
 if(!source)
  return;

 source->HandleType=bmDIB;
 source->PixelFormat=pf32bit;

 target.SetRes(source->Width,source->Height);
 target.SetColorModel(ubmColor,false);

 if(!source->Width || !source->Height)
  return;

 memcpy(target.GetData(),source->ScanLine[target.GetHeight()-1],
		target.GetLength()*sizeof(UColorT));
}


// Загружает изображение из файла с именем FileName
bool LoadBitmapFromFile(String FileName, UBitmap *target)
{
 Graphics::TBitmap *source=new Graphics::TBitmap;

 source->LoadFromFile(FileName);
 *target<<source;
 delete source;

/* unsigned char header[54];
 SizeT width,height,filesize;
 SizeT offset;
 TFileStream *stream=0;

 if(!target)
  return false;

 stream=new TFileStream(FileName, fmOpenRead);
 stream->ReadBuffer(header,54);

 memcpy(&filesize,header+2,4);
 memcpy(&offset,header+10,4);
 memcpy(&width,header+18,4);
 memcpy(&height,header+22,4);

 target->SetXYRes(width,height);
 stream->ReadBuffer(target->GetData(),filesize-offset);

 delete stream;   */
 return true;
}

// Сохраняет изображение в файл с именем FileName
bool SaveBitmapToFile(String FileName, UBitmap *target)
{
 Graphics::TBitmap *source=new Graphics::TBitmap;

 *target>>source;
 source->SaveToFile(FileName);
 delete source;

/* unsigned char header[54];
 SizeT filesize;
 SizeT value;
 TFileStream *stream=0;
 SizeT XRes,YRes;

 if(!target)
  return false;

 filesize=54+target->GetImageLength();
 XRes=target->GetXRes();
 YRes=target->GetYRes();

 // Создание заголовка файла
 memcpy(header,"BM",2);
 memcpy(header+2,&filesize,4);
 memset(header+6,0,4);
 value=54; memcpy(header+10,&value,4);

 // Создание заголовка bitmap
 value=40; memcpy(header+14,&value,4);
 memcpy(header+18,&XRes,4);
 memcpy(header+22,&YRes,4);
 value=1; memcpy(header+26,&value,2);
 value=32; memcpy(header+28,&value,2);
 value=0; memcpy(header+30,&value,4);
 memset(header+34,0,4);
 value=2835; memcpy(header+38,&value,4);
 value=2835; memcpy(header+42,&value,4);
 value=0; memcpy(header+46,&value,4);
 value=0; memcpy(header+50,&value,4);

 stream=new TFileStream(FileName, fmOpenWrite);

 stream->WriteBuffer(header,54);
 if(target->GetData())
  stream->WriteBuffer(target->GetData(),target->GetImageLength()*sizeof(ColorT));

 delete stream;      */
 return true;
}


}
#endif
