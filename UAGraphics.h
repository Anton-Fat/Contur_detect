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
protected: // ������

protected: // �������� ������������ ���������
// ���� ����
UColorT PenColor;

// ������� ����
int PenWidth;

// ���������� ����
int PenX, PenY;

protected: // ��������� ����������
// ������ ��������� �� ������ ����� ���������
UColorT *CData;

// ���������� ����� ���������
int CWidth, CHeight;

// �������� ������� ����
int HalfPenWidth;

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
UAGraphics(void);
virtual ~UAGraphics(void);
// --------------------------

// --------------------------
// ������ ������� � ������
// --------------------------
// --------------------------

// --------------------------
// ������ ������� � ��������� ������������ ���������
// --------------------------
// ���������� ���� ����
const UColorT& GetPenColor(void) const;

// ���������� ������� ����
const int GetPenWidth(void) const;

// ���������� X ���������� ����
const int GetPenX(void) const;

// ���������� Y ���������� ����
const int GetPenY(void) const;

// ������������� ���� ����
void SetPenColor(UColorT &color);

// ������������� ������� ����
bool SetPenWidth(int width);

// ������������� ���� � ����� x,y
void SetPenPos(int x, int y);
// --------------------------

// --------------------------
// ����������� ���������
// --------------------------
// ���������� �������
// ���� ispos == true ������������� ���� � �������� �������
virtual void Pixel(int x, int y, bool ispos=true)=0;

// ���������� ����� �� ����������� ������
virtual void Line(int x1, int y1, int x2, int y2)=0;

// ���������� ����� ������������ ������� ����
// ���������� ���� � ������� x,y
virtual void LineTo(int x, int y)=0;

// ���������� ���������� � ������� x,y � �������� r
// ���� fill == true - �� ������ � ��������
virtual void Circle(int x, int y, int r, bool fill=false)=0;

// ���������� �������� ������ � ������� x,y � �������� r
// ������� ������� fi, �������� �� ���� teta
// ������ ������� ������� �� �������������� ���
// ���� �������� � ��������
virtual void Sector(int x, int y, int r, int fi, int teta, bool fill=false)=0;

// ���������� ������ � ������� x,y � ��������� hor, vert
// ���� fill == true - �� ������ � ��������
virtual void Ellipse(int x, int y, int hor, int vert, bool fill=false)=0;

// ���������� ������������� � ������������
// x1,y1 - �������� ������ ����
// x2,y2 - ������� ������� ����
// ���� fill == true - �� ������ � ��������
virtual void Rect(int x1, int y1, int x2, int y2, bool fill=false)=0;

// ���������� ������������� � ������������ ������
// � �������� ������ color
// ���� fill == true - �� ������ � ��������
virtual void Triangle(int x1, int y1, int x2, int y2, int x3, int y3, bool fill=false)=0;

// ���������� ������� ������������ �������
virtual void Fill(int x, int y, UColorT BorderColor)=0;
// --------------------------

// --------------------------
// ����� ������
// --------------------------
// ������������� ������� ����� �����
virtual bool SetFont(const string &fontname,
					 bool isbold=false, bool isitalic=false, bool isunder=false)=0; 

// ������� ����� str ������� � size ��������
virtual void TextOut(const string &str, int x, int y, int size, UColorT Color)=0;
// --------------------------

protected: // ��������������� ������
// --------------------------
// ��������������� ����������� ���������
// --------------------------
// ������������ ������� � ����������� x,y ��� ��������
virtual void DrawPixel(int x, int y)=0;
// --------------------------
};

}
#endif

