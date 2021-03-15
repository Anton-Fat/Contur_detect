/* ************************************************************************** */
// Copyright Alexander Bakhshiev, 2005-2008
// E-mail: alexab@ailab.ru
/* ************************************************************************** */
#ifndef UGRAPHICS_CPP
#define UGRAPHICS_CPP

#include "UGraphics.h"
#include <cmath>
#include <cstdlib>
#include <list>

namespace Utilities {

using namespace std;

/* ***************************************************************************
 Реализация UGraphics
*************************************************************************** */

// --------------------------
// Конструкторы и деструкторы
// --------------------------
UGraphics::UGraphics(UBitmap *canvas)
{
 if(!canvas)
  throw "";

 Canvas=canvas;
 PenColor.c=0;
 PenWidth=1;
 HalfPenWidth=0;
 PenX=PenY=0;
}

UGraphics::~UGraphics(void)
{
}
// --------------------------

// --------------------------
// Методы доступа к данным
// --------------------------
// Возвращает текущую канву рисования
UBitmap* UGraphics::GetCanvas(void)
{
 return Canvas;
}

// Задает канву рисования
bool UGraphics::SetCanvas(UBitmap *canvas)
{
 if(!canvas)
  return false;

 Canvas=canvas;
 return true;
}
// --------------------------

// --------------------------
// Перегруженные операторы
// --------------------------
// Оператор присваивания
UGraphics& UGraphics::operator = (UGraphics &tool)
{
 PenColor=tool.PenColor;
 PenWidth=tool.PenWidth;
 return *this;
}
// --------------------------

// --------------------------
// Графические примитивы
// --------------------------
// Отображает пиксель
// если ispos == true позиционирует перо в заданную позицию
void UGraphics::Pixel(int x, int y, bool ispos)
{
 CWidth=Canvas->GetWidth();
 CHeight=Canvas->GetHeight();

 DrawPixel(x,y);

 if(ispos)
  {
   PenX=x;
   PenY=y;
  }
}

// Отображает линию по координатам концов
void UGraphics::Line(int x1, int y1, int x2, int y2)
{
 int tmp;
 int dx,dy,y,x;

 CWidth=Canvas->GetWidth();
 CHeight=Canvas->GetHeight();

 if(x1>x2 && y1>y2)
  {
   tmp=x1; x1=x2; x2=tmp;
   tmp=y1; y1=y2; y2=tmp;
  }

 if(x1 >= CWidth || y1 >= CHeight)
  return;

 dx=x2-x1;
 dy=y2-y1;

 if(!dx && !dy)
  {
   DrawPixel(x1,y1);
   return;
  }

 x1=(x1<0)?0:x1;
 x2=(x2>=CWidth)?CWidth-1:x2;
 y1=(y1<0)?0:y1;
 y2=(y2>=CHeight)?CHeight-1:y2;

 if(!dx)
  {
   CData=Canvas->GetData()+y1*CWidth+x1;
   for(int i=y1;i<=y2;i++)
    DrawPixel(x1,i);
  }
 else
 if(!dy)
  {
   CData=Canvas->GetData()+y1*CWidth+x1;
   for(int i=x1;i<=x2;i++)
    DrawPixel(i,y1);
  }
 else
 if(dy<dx)
  {
   for(int i=x1;i<=x2;i++)
    {
     y=dy*(i-x1)/dx+y1;
     if(y >= 0 && y < CHeight)
      DrawPixel(i,y);
    }
  }
 else
  {
   for(int i=y1;i<=y2;i++)
    {
     x=dx*(i-y1)/dy+x1;
     if(x >= 0 && x < CWidth)
      DrawPixel(x,i);
    }
  }      
}

// Отображает линию относительно позиции пера
// Перемещает перо в позицию x,y
void UGraphics::LineTo(int x, int y)
{
 Line(PenX,PenY,x,y);
 PenX=x;
 PenY=y;
}

// Отображает окружность с центром x,y и радиусом r
// Если fill == true - то рисуем с заливкой
void UGraphics::Circle(int x, int y, int r, bool fill)
{
 int r2=r*r, r4=(double)(r*1.414/2.0);
 int x0,y0;
 int x1,x2,y1;

 CWidth=Canvas->GetWidth();
 CHeight=Canvas->GetHeight();

 if(!fill)
  {
   for(int i=-r4-1; i <=r4+1; i++)
    {
     y0=sqrt((float)r2-i*i);
     DrawPixel(x+i,y+y0);
     DrawPixel(x+i,y-y0);
     DrawPixel(x+y0,y+i);
     DrawPixel(x-y0,y+i);
    }
/*
   for(int i=-r4-1; i <=r4+1; i++)
    {
     x0=sqrt((float)r2-i*i);
     DrawPixel(x+x0,y+i);
     DrawPixel(x-x0,y+i);
    }*/
  }
 else
  {
   for(int i=-r; i <=r; i++)
    {
     x0=sqrt((float)r2-i*i);
     x1=x-x0; x2=x+x0;
     y1=y+i;

     if(y1>=0 && y1 <CHeight)
      {
       if(x1<0) x1=0;
       if(x2>=CWidth) x2=CWidth-1;

       CData=Canvas->GetData()+y1*CWidth;
       for(int j=x1;j<=x2;j++)
        *(CData+j)=PenColor;
      }
    }  
  }
}

// Отображает круговой сектор с центром x,y и радиусом r
// Раствор сектора fi, повернут на угол teta 
// против часовой стрелки от горизонтальной оси
// углы задаются в градусах
void UGraphics::Sector(int x, int y, int r, int fi, int teta, bool fill)
{
// int r2=r*r, r4=(double)(r*1.414/2.0);
// int x0,y0;
 int x1,y1;
 double Pi2=3.1415/180.0;
 double Alpha=asin(1.0/r);
 double Teta=teta*Pi2,Fi=fi*Pi2;

 CWidth=Canvas->GetWidth();
 CHeight=Canvas->GetHeight();

 x1=x+r*cos(Teta);
 y1=y+r*sin(Teta);
 Line(x,y,x1,y1);
 x1=x+r*cos(Teta+Fi);
 y1=y+r*sin(Teta+Fi);
 Line(x,y,x1,y1);
 for(double i=Teta;i<Teta+Fi;i+=Alpha)
  DrawPixel(x+r*cos(i),y+r*sin(i));

 if(fill)
 {
  x1=x+r*cos(Teta+Fi/2)/2.0;
  y1=y+r*sin(Teta+Fi/2)/2.0;
  Fill(x1, y1, PenColor);
 }
}

// Отображает эллипс с центром x,y и радиусами hor, vert
// Если fill == true - то рисуем с заливкой
void UGraphics::Ellipse(int x, int y, int hor, int vert, bool fill)
{
 int hor2=hor*hor;//, hor4=(double)(hor*1.414/2.0);
 int vert2=vert*vert;//, vert4=(double)(vert*1.414/2.0);
 int x0,y0;
 int x1,x2,y1;

 CWidth=Canvas->GetWidth();
 CHeight=Canvas->GetHeight();

 if(!fill)
  {
   for(int i=-hor; i <=hor; i++)
    {
     y0=sqrt((float)vert2-i*i*vert2/hor2);
     DrawPixel(x+i,y+y0);
     DrawPixel(x+i,y-y0);
    }

   for(int i=-vert; i <=vert; i++)
    {
     x0=sqrt((float)hor2-i*i*hor2/vert2);
     DrawPixel(x+x0,y+i);
     DrawPixel(x-x0,y+i);
    }
  }
 else
  {
   for(int i=-vert; i <=vert; i++)
    {
     x0=sqrt((float)hor2-i*i*hor2/vert2);
     x1=x-x0; x2=x+x0;
     y1=y+i;

     if(y1>=0 && y1 <CHeight)
      {
       if(x1<0) x1=0;
       if(x2>=CWidth) x2=CWidth-1;

       CData=Canvas->GetData()+y1*CWidth;
       for(int j=x1;j<=x2;j++)
        *(CData+j)=PenColor;
      }
    }   
  }
}

// Отображает прямоугольник с координатами
// x1,y1 - верхнего левого угла
// x2,y2 - правого нижнего угла
// Если fill == true - то рисуем с заливкой
void UGraphics::Rect(int x1, int y1, int x2, int y2, bool fill)
{
 int width;
 int dx,dy;

 if(!fill)
  {
   Line(x1,y1,x1,y2);
   Line(x1,y1,x2,y1);
   Line(x2,y1,x2,y2);
   Line(x1,y2,x2,y2);
  }
 else
  {
   CWidth=Canvas->GetWidth();
   CHeight=Canvas->GetHeight();


   if(x2<x1)
    {
     dx=x1; x1=x2; x2=dx;
    }

   if(y2<y1)
    {
     dy=y1; y1=y2; y2=dy;
    }

   if(x1>=CWidth || y1 >=CHeight)
    return;

   if(x1<0) x1=0;
   if(y1<0) y1=0;
   if(x2>=CWidth) x2=CWidth-1;
   if(y2>=CHeight) y2=CHeight-1;

   dx=x2-x1+1;
   dy=y2-y1+1;
   width=PenWidth;
   SetPenWidth(1);

   CData=Canvas->GetData()+y1*CWidth+x1;
   for(int i=0;i<dx;i++)
    *(CData+i)=PenColor;

   for(int i=0;i<dy;i++)
    memcpy(CData+i*CWidth, CData, dx*sizeof(UColorT));

   SetPenWidth(width);
  }
}

// Отображает прямоугольник с координатами вершин
// Если fill == true - то рисуем с заливкой
void UGraphics::Triangle(int x1, int y1, int x2, int y2, int x3, int y3,
                         bool fill)
{
 Line(x1,y1,x2,y2);
 Line(x1,y1,x3,y3);
 Line(x2,y2,x3,y3);

 if(fill)
 {
  Fill((x1+x2+x3)/3, (y1+y2+y3)/3, PenColor);
 }

}


// Простейшая заливка произвольной области
void UGraphics::Fill(int x, int y, UColorT BorderColor)
{
 list<int> points;
 int pos=y*CWidth+x;

 if(pos<0 || pos>=CWidth*CHeight)
  return;

 (*Canvas)(pos)=PenColor;
 points.push_back(pos);

 do{
  pos=points.front();
  // Поиск соседних точек
  int y=pos/CWidth;
  int x=pos-y*CWidth;

  if(x-1>=0)
  {
   if((*Canvas)(pos-1).c != BorderColor.c)
   {
    (*Canvas)(pos-1)=PenColor;
    points.push_back(pos-1);
   }
  }
  if(x+1<CWidth)
  {
   if((*Canvas)(pos+1).c != BorderColor.c)
   {
    (*Canvas)(pos+1)=PenColor;
    points.push_back(pos+1);
   }
  }
  if(y+1<CHeight)
  {
   if((*Canvas)(pos+CWidth).c != BorderColor.c)
   {
    (*Canvas)(pos+CWidth)=PenColor;
    points.push_back(pos+CWidth);
   }
  }
  if(y-1>=0)
  {
   if((*Canvas)(pos-CWidth).c != BorderColor.c)
   {
    (*Canvas)(pos-CWidth)=PenColor;
    points.push_back(pos-CWidth);
   }
  }
  
  points.pop_front();
 }while(points.size()>0);

}
// --------------------------

// --------------------------
// Вывод текста
// --------------------------
// Устанавливает текущим новый шрифт
bool UGraphics::SetFont(const string &fontname,
                     bool isbold, bool isitalic, bool isunder)
{
 return false;
}

// Выводит текст str высотой в size пикселей
void UGraphics::TextOut(const string &str, int x, int y, int size, UColorT Color)
{
}
// --------------------------


// Вспомогательные методы
// --------------------------
// Вспомогательные графические примитивы
// --------------------------
// Отрисовывает пиксель в координатах x,y без проверок
void UGraphics::DrawPixel(int x, int y)
{
 int x1,y1,x2,y2,dx,dy;

 if(PenWidth == 1)
  {
   if(x<0 || x>=CWidth || y<0 || y>=CHeight)
    return;
   *(Canvas->GetData()+y*CWidth+x)=PenColor;
  }
 else
  {
   if(PenWidth % 2)
    {
     x1=x-HalfPenWidth;
     y1=y-HalfPenWidth;
    }
   else
    {
     x1=x;
     y1=y;
    }

   x2=x+HalfPenWidth;
   y2=y+HalfPenWidth;

   if(x1<0) x1=0;
   if(y1<0) y1=0;
   if(x2>=CWidth) x2=CWidth-1;
   if(y2>=CHeight) y2=CHeight-1;

   CData=Canvas->GetData()+y1*CWidth+x1;

   dx=x2-x1+1;
   dy=y2-y1+1;

   if(PenWidth > 4)
    {
     for(int i=0;i<dx;i++)
      *(CData+i)=PenColor;
     for(int j=0;j<dy;j++)
      memcpy(CData+j*CWidth,CData,dx*sizeof(UColorT));
    }
   else
    {
     for(int j=0;j<dy;j++,CData+=CWidth)
      for(int i=0;i<dx;i++)
       *(CData+i)=PenColor;
    } 

  }
}


// Формирует набор точек смежных с заданной
// список точек заносится в конец списка points
// координаты точек рассматриваются как одномерные
/*void UGraphics::FindNearPoints(int pos, list<int> &points)
{
 if(pos<0 || pos>=CWidth*CHeight)
  return;

 int y=pos/CWidth;
 int x=pos-y*CWidth;

 if(x-1>=0)
  points.push_back(pos-1);
 if(x+1<CWidth)
  points.push_back(pos+1);
 if(y+1<CHeight)
  points.push_back(pos+CWidth);
 if(y-1>=0)
  points.push_back(pos-CWidth);
}*/
// --------------------------

}
#endif


