/* ************************************************************************** */
// Copyright Alexander Bakhshiev, 2005-2008
// E-mail: alexab@ailab.ru
/* ************************************************************************** */
#ifndef UAGRAPHICS_H
#define UAGRAPHICS_H

#include "UBitmap.h"
#include <string>

namespace Utilities {

using namespace std;

class UAGraphics
{
protected: // Данные

protected: // Атрибуты инструментов рисования
// Цвет пера
UColorT PenColor;

// Толщина пера
int PenWidth;

// Координаты пера
int PenX, PenY;

protected: // Временные переменные
// Прямой указатель на данные канвы рисования
UColorT *CData;

// Разрешение канвы рисования
int CWidth, CHeight;

// Половина толщины пера
int HalfPenWidth;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UAGraphics(void);
virtual ~UAGraphics(void);
// --------------------------

// --------------------------
// Методы доступа к данным
// --------------------------
// --------------------------

// --------------------------
// Методы доступа к атрибутам инструментов рисования
// --------------------------
// Возвращает цвет пера
const UColorT& GetPenColor(void) const;

// Возвращает толщину пера
const int GetPenWidth(void) const;

// Возвращает X координату пера
const int GetPenX(void) const;

// Возвращает Y координату пера
const int GetPenY(void) const;

// Устанавливает цвет пера
void SetPenColor(UColorT &color);

// Устанавливает толщину пера
bool SetPenWidth(int width);

// Позиционирует перо в точку x,y
void SetPenPos(int x, int y);
// --------------------------

// --------------------------
// Графические примитивы
// --------------------------
// Отображает пиксель
// если ispos == true позиционирует перо в заданную позицию
virtual void Pixel(int x, int y, bool ispos=true)=0;

// Отображает линию по координатам концов
virtual void Line(int x1, int y1, int x2, int y2)=0;

// Отображает линию относительно позиции пера
// Перемещает перо в позицию x,y
virtual void LineTo(int x, int y)=0;

// Отображает окружность с центром x,y и радиусом r
// Если fill == true - то рисуем с заливкой
virtual void Circle(int x, int y, int r, bool fill=false)=0;

// Отображает круговой сектор с центром x,y и радиусом r
// Раствор сектора fi, повернут на угол teta
// против часовой стрелки от горизонтальной оси
// углы задаются в градусах
virtual void Sector(int x, int y, int r, int fi, int teta, bool fill=false)=0;

// Отображает эллипс с центром x,y и радиусами hor, vert
// Если fill == true - то рисуем с заливкой
virtual void Ellipse(int x, int y, int hor, int vert, bool fill=false)=0;

// Отображает прямоугольник с координатами
// x1,y1 - верхнего левого угла
// x2,y2 - правого нижнего угла
// Если fill == true - то рисуем с заливкой
virtual void Rect(int x1, int y1, int x2, int y2, bool fill=false)=0;

// Отображает прямоугольник с координатами вершин
// с заливкой цветом color
// Если fill == true - то рисуем с заливкой
virtual void Triangle(int x1, int y1, int x2, int y2, int x3, int y3, bool fill=false)=0;

// Простейшая заливка произвольной области
virtual void Fill(int x, int y, UColorT BorderColor)=0;
// --------------------------

// --------------------------
// Вывод текста
// --------------------------
// Устанавливает текущим новый шрифт
virtual bool SetFont(const string &fontname,
					 bool isbold=false, bool isitalic=false, bool isunder=false)=0; 

// Выводит текст str высотой в size пикселей
virtual void TextOut(const string &str, int x, int y, int size, UColorT Color)=0;
// --------------------------

protected: // Вспомогательные методы
// --------------------------
// Вспомогательные графические примитивы
// --------------------------
// Отрисовывает пиксель в координатах x,y без проверок
virtual void DrawPixel(int x, int y)=0;
// --------------------------
};

}
#endif

