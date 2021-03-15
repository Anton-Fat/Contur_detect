/* ************************************************************************** */
// Copyright Anton Fateev, 2009.
// E-mail: antonfat@gmail.com
/* ************************************************************************** */

#include <math.h>
#include <string>

#pragma hdrstop

#include "Histrogr.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void MakeGistr (UBitmap &inpImg, string ncolor,  vector<int> &SumG)
  {
 SumG.assign(256,0);
 UColorT* pbuf=inpImg.GetData();
for(int i = 0;i<inpImg.GetLength();i++,pbuf++) {
if (ncolor == "Red") {
  ++SumG[pbuf->r];
} else {  if (ncolor == "Blue") {
  ++SumG[pbuf->b];
} else {  if (ncolor == "Green") {
	   ++SumG[pbuf->g];
		}  }  }  }

   }
//-------------------------------------------------------------
void PolAreaN (UBitmap &inpImg, unsigned char &Intens)
{

	int Np = 0;
	vector<int> SumG;
	int r = 0, g = 0, b = 0;
	MakeGistr (inpImg, "Red", SumG);
	while ((Np < inpImg.GetLength()/2)&&(r <= 255))
	{  Np += SumG[r];  r++;   }    // Получили n точек для red
	 Np = 0;  MakeGistr (inpImg, "Green", SumG);
	while ((Np < inpImg.GetLength()/2)&&(g <= 255))
	{  Np += SumG[g];  g++;   }
	 Np = 0;	MakeGistr (inpImg, "Blue", SumG);
	while ((Np < inpImg.GetLength()/2)&&(b <= 255))
	{  Np += SumG[b];  b++;  }          //*/
	//Intens = r;
	Intens = (r+g+b)/3;   // Для цветного не точно.

}
//----------------------------------------------------------------------------
void SmalKont (vector<int> &Xpoint1, vector<int> &Ypoint1, vector<int> &Napr1, vector<int> &Type1)
{
vector<int> Xpoint2, Ypoint2, Napr2, Type2;
Xpoint2.push_back(Xpoint1[0]);
Ypoint2.push_back(Ypoint1[0]);
Napr2.push_back(Napr1[0]);
Type2.push_back(Type1[0]);
int size = Xpoint1.size()-1;
for (int i = 1; i < size; i++)
{   if (Napr1[i] != Napr1[i-1]) {
    
	Xpoint2.push_back(Xpoint1[i]);
	Ypoint2.push_back(Ypoint1[i]);
	Napr2.push_back(Napr1[i]);
	Type2.push_back(Type1[i]);
	  }				  }
 Xpoint1.clear();  Ypoint1.clear();  Napr1.clear(); Type1.clear();
 size = Xpoint2.size();
 Xpoint1.resize(size);  Ypoint1.resize(size);  Napr1.resize(size); Type1.resize(size);
 Xpoint1 = Xpoint2;  Ypoint1 = Ypoint2;  Napr1 = Napr2;  Type1 = Type2;
}
//----------------------------------------------------------------------------
void PreobrGor (vector<int> &Xpoint1, vector<int> &Ypoint1, vector<int> &Xd1, vector<int> &Yd1, int &h, int &w)
{
 Xd1.clear();     Yd1.clear();
 Xd1.resize(Xpoint1.size());  Yd1.resize(Ypoint1.size());

 int H = 100;     //Высота, см
 double alfa = 60;   //Угол наклона к горизонту, градусы
 int R = 300;     //Фокусное расстояние, см
 int Lpk, H0dy, H1dy, W1dx;
 double k = 0, Ax, Bx, Ay, By;

 alfa = alfa*M_PI/180;
 Ax = cos(alfa)*R/H;  Bx = sin(alfa)/H;
 Ay = Ax*cos(alfa);   By = Bx*cos(alfa);
 Lpk = (R/tan(alfa)) - 120;

 GetPloY( -h/2, H0dy, Ay, By);
 if (Lpk > h/2) { Lpk = h/2;  }
 GetPloY(  Lpk, H1dy, Ay, By);
 GetPloX(  w/2, Lpk, W1dx, Ax, Bx);
 //GetPloX(  50, 50, W1dx, Ax, Bx);

 k = cos(alfa);

 for (int j = 0; j < Ypoint1.size(); j++) {

 Yd1[j] = Ypoint1[j] - h/2;
 GetPloY(Yd1[j], Yd1[j], Ay, By);
 Yd1[j] = Yd1[j] - H0dy;

 }
 for (int i = 0; i < Xpoint1.size(); i++) {

 Xd1[i] = Xpoint1[i] - w/2;
 GetPloX(  Xd1[i], Ypoint1[i] - h/2, Xd1[i], Ax, Bx);
 Xd1[i] = Xd1[i] + W1dx;
 
 }

 w = 2*W1dx; h = H1dy - H0dy;

}
//-------------------------------------------------------------
void GetPloX (int &x, int &y, int &xd, double &A, double &B)
{
xd = x/(A - B*y);
}
//-------------------------------------------------------------
void GetPloY (int &y, int &yd, double &A, double &B)
{
yd = y/(A - B*y);
}
//-------------------------------------------------------------
		  

//--------------------------------------------------------------
//void MoveToBmp
















//--------------------------------------------------------------
		 //*/
		 /*
 vector<int> SumG;
 SumG.assign(255,0);

 UColorT* pbuf=Bmp1.GetData();
for(int i = 0;i<Bmp1.GetLength();i++,pbuf++) {
++SumG[pbuf->b];
		}



		//*/


// переход в плоскость пола


