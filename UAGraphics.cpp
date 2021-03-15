/* ************************************************************************** */
// Copyright Alexander Bakhshiev, 2005-2008
// E-mail: alexab@ailab.ru
/* ************************************************************************** */
#ifndef UAGRAPHICS_CPP
#define UAGRAPHICS_CPP

#include "UAGraphics.h"
#include <cmath>
#include <cstdlib>
#include <list>

namespace Utilities {

using namespace std;

/* ***************************************************************************
 ���������� UAGraphics
*************************************************************************** */

// --------------------------
// ������������ � �����������
// --------------------------
UAGraphics::UAGraphics(void)
{
 PenColor.c=0;
 PenWidth=1;
 HalfPenWidth=0;
 PenX=PenY=0;

 CWidth=CHeight=0;
}

UAGraphics::~UAGraphics(void)
{
}
// --------------------------

// --------------------------
// ������ ������� � ��������� ������������ ���������
// --------------------------
// ���������� ���� ����
const UColorT& UAGraphics::GetPenColor(void) const
{
 return PenColor;
}

// ���������� ������� ����
const int UAGraphics::GetPenWidth(void) const
{
 return PenWidth;
}

// ���������� X ���������� ����
const int UAGraphics::GetPenX(void) const
{
 return PenX;
}

// ���������� Y ���������� ����
const int UAGraphics::GetPenY(void) const
{
 return PenY;
}

// ������������� ���� ����
void UAGraphics::SetPenColor(UColorT &color)
{
 if(PenColor == color)
  return;

 PenColor=color;
}

// ������������� ������� ����
bool UAGraphics::SetPenWidth(int width)
{
 if(PenWidth == width)
  return true;

 if(width <=0)
  return false;

 PenWidth=width;
 HalfPenWidth=PenWidth>>1;
 return true;
}

// ������������� ���� � ����� x,y
void UAGraphics::SetPenPos(int x, int y)
{
 PenX=x;
 PenY=y;
}
// --------------------------

}
#endif


