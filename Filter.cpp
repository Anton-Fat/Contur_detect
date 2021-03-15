/* ************************************************************************** */
// Copyright Anton Fateev, 2009.
// E-mail: antonfat@gmail.com
/* ************************************************************************** */
#include <vcl.h>
#include <string>
#include <math.h>
#include <stdlib.h>


	//#include <algorithm>

#pragma hdrstop

#include "Filter.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------

void Filter(UBitmap &inpImg, UBitmap &outImg, string ntype, int N, int sklon)
{
  if (N > 15) {
   ShowMessage("Недопустимый размер маски");
   return;
  }
int Area[4]= {0,0,1,1};
Area[2]= inpImg.GetWidth();//-100;
Area[3]= inpImg.GetHeight();//-100;
unsigned short int h;
char filter;
vector<int> Mf;
int Sum=0;
 if (ntype == "Гаусс") {
	 filter='1'; h = N;
	 Mask(Mf,filter,Sum,N,sklon);
 }   else { if (ntype == "Гауссиан") {
	 filter='2'; h = N;
	 Mask(Mf,filter,Sum,N,sklon);
 }   else {  if (ntype == "Гаусс-3") {
		h=3;  filter='1';
		Mask(Mf,filter,Sum,h,sklon);
			}   else { if (ntype == "Гаусс-5") {
			h=5;  filter='1';
			Mask(Mf,filter,Sum,h,sklon);
			}  else { if (ntype == "Гаусс-7") {
			h=7;  filter='1';
			Mask(Mf,filter,Sum,h,sklon);
			}  else { if (ntype == "Собель Y") {
			h=3;  filter='3';
			Mask(Mf,filter,Sum,h);
			}  else { if (ntype == "Собель X") {
			h=3;  filter='4';
			Mask(Mf,filter,Sum,h);
			}  else { if (ntype == "Лог фильтр") {
			h=3;  filter='7';
			Mask(Mf,filter,Sum,h);
			}  else { if (ntype == "Медиана") {
			h=N;
			}  else {
					 h=N;  filter='S';
					 Mask(Mf,filter,Sum,h);
					}
		  }  }  }  }  }  }  }  }
  //
		  outImg=inpImg;
  for (int iY = Area[1]; iY < Area[3]; iY ++)
  {
	for (int iX = Area[0]; iX < Area[2]; iX ++)
	 {

       if (ntype == "Медиана") {
			FilterMedian(inpImg,outImg,iX,iY,Area,h);
			}  else {
	   FilterPixel(inpImg,outImg,iX,iY,Mf,Area,Sum,h);
		  //outImg(iX,iY)=inpImg(iX,iY);
					 }
	 }
  }
  }
//-------------------------------------------------------------------------

  void Mask(vector<int> &buff,char typeF,int &S,int n, int sklon)
{
buff.resize(n*n);
 // либо buff.assign(n,0); для создания забитого нулями массива
  switch (typeF) {
		case '1':
		 div_t xy;
		 unsigned short int gauss;
		for(size_t i=0;i<n*n;i++)
	  {
		xy = div(i,n);
		gauss = n*n*exp(-10.0*((xy.rem -(n-1)/2)*(xy.rem -(n-1)/2)+(xy.quot -(n-1)/2)*(xy.quot -(n-1)/2))/(sklon*n*n));
		buff[i]=gauss;
	  }
		break;
		case '2':
		 div_t xy2;
		 short int gauss2;
		for(size_t i=0;i<n*n;i++)
	  {
		xy2 = div(i,n);
		gauss2 = ((n-1)*(n-1)/4-(xy2.rem -(n-1)/2)*(xy2.rem -(n-1)/2)-(xy2.quot -(n-1)/2)*(xy2.quot -(n-1)/2))*exp(-10.0*((xy2.rem -(n-1)/2)*(xy2.rem -(n-1)/2)+(xy2.quot -(n-1)/2)*(xy2.quot -(n-1)/2))/(sklon*n*n));
		buff[i]=gauss2;
	  }
		break;
		case '3':   // Собель Y
		buff[0]= 1 ;  buff[1]= 2 ; buff[2]= 1 ;
		buff[3]= 0 ;  buff[4]= 0 ; buff[5]= 0 ;
		buff[6]= -1 ;  buff[7]= -2 ; buff[8]= -1 ;
		break;
		case '4':   // Собель X
		buff[0]= -1 ;  buff[1]= 0 ; buff[2]= 1 ;
		buff[3]= -2 ;  buff[4]= 0 ; buff[5]= 2 ;
		buff[6]= -1 ;  buff[7]= 0 ; buff[8]= 1 ;
		break;
		case '5':   // Roberts X
		buff[0]= 0 ;  buff[1]= 1 ;
		buff[2]= -1 ;  buff[3]= 0 ;
		break;
		case '6':   // Roberts Y
		buff[0]= 1 ;  buff[1]= 0 ;
		buff[2]= 0 ;  buff[3]= -1 ;
		break;
		case '7':   // Лог фильтр
		buff[0]= 0 ;  buff[1]= -1 ; buff[2]= 0 ;
		buff[3]= -1 ;  buff[4]= 4 ; buff[5]= -1 ;
		buff[6]= 0 ;  buff[7]= -1 ; buff[8]= 0 ;
		break;
	  default:
	  for(size_t i=0;i<buff.size();i++)
	  {
		buff[i]=1;
	  }
				 }
 for(size_t i=0;i<buff.size();i++)
	{
	if (buff[i]>0) {
	S += buff[i];
	}
	}
}
//-----------------------------------------------------------------------------
  void FilterPixel(UBitmap &inpImg, UBitmap &outImg,int iX,int iY,vector<int> &Mf, int Area[],int Sum,int h)
  {
   int OutR, OutG, OutB;
	OutR=OutG=OutB=0;
	int firstX = iX-(h-1)/2;
	int firstY = iY-(h-1)/2;
	int firstJY;
	unsigned short int hmal;
	hmal= (h-1)/2;
   for (unsigned short int j = 0; j < h; j++) {
	 firstJY= firstY+j;
	 for (unsigned short int i = 0; i < h; i++) {
	 if ((firstJY<Area[1])||(firstJY>Area[3]-1)||(firstX+i < Area[0])||(firstX+i > Area[2]-1)) {
	   OutR += inpImg(iX,iY).r*Mf[i+h*j];
	   OutG += inpImg(iX,iY).g*Mf[i+h*j];
	   OutB += inpImg(iX,iY).b*Mf[i+h*j];
	 } else {
	 OutR += inpImg(firstX+i,firstJY).r*Mf[i+h*j];
	 OutG += inpImg(firstX+i,firstJY).g*Mf[i+h*j];
	 OutB += inpImg(firstX+i,firstJY).b*Mf[i+h*j];
			}
	 }
   }
   outImg(iX,iY).r=abs(OutR)/Sum;
   outImg(iX,iY).g=abs(OutG)/Sum;
   outImg(iX,iY).b=abs(OutB)/Sum;
   }
//-----------------------------------------------------------------------------
 void FilterMedian(UBitmap &inpImg, UBitmap &outImg,int iX,int iY, int Area[],int h)
  {
   int OutR, OutG, OutB;
	OutR=OutG=OutB=0;
	vector<int> Mfr, Mfg, Mfb;
	Mfr.resize(h*h);
	Mfg.resize(h*h);
	Mfb.resize(h*h);
	unsigned short int hmal;
	hmal= (h-1)/2;
	int firstX = iX-hmal;
	int firstY = iY-hmal;
	 div_t xy;

		for(size_t i=0;i<h*h;i++)
	  {
		xy = div(i,h);
		if ((firstY+xy.quot<Area[1])||(firstY+xy.quot>Area[3]-1)||(firstX+xy.rem < Area[0])||(firstX+xy.rem > Area[2]-1)) {
	   Mfr[i] = inpImg(iX,iY).r;
	   Mfg[i] = inpImg(iX,iY).g;
	   Mfb[i] = inpImg(iX,iY).b;
	 } else {
	 Mfr[i] = inpImg(firstX+xy.rem, firstY+xy.quot).r;
	 Mfg[i] = inpImg(firstX+xy.rem, firstY+xy.quot).g;
	 Mfb[i] = inpImg(firstX+xy.rem, firstY+xy.quot).b;
			}
	  }
	 qsort(&Mfr[0],Mfr.size(),sizeof(int),elemsort);
	 qsort(&Mfg[0],Mfg.size(),sizeof(int),elemsort);
	 qsort(&Mfb[0],Mfb.size(),sizeof(int),elemsort);
 
	 outImg(iX,iY).r=Mfr[(h*h-1)/2];
	 outImg(iX,iY).g=Mfg[(h*h-1)/2];
	 outImg(iX,iY).b=Mfb[(h*h-1)/2];

	/*	 if (firstY==50&&firstX==50){ int a1,a2,a3,a4,a5,a6,a7,a8,a9;
	  a1=Mfr[0]; a2=Mfr[1]; a3=Mfr[2];
	   a4=Mfr[3]; a5=Mfr[4];a6=Mfr[5];
	a7=Mfr[6];a8=Mfr[7];a9=Mfr[8];
		int b=5;
		}//*/

   }     //*/
//----------------------------------------------------------------

int elemsort(const void *v1,const void *v2)
{
int vv1,vv2;

memcpy(&vv1,v1,sizeof(int));
memcpy(&vv2,v2,sizeof(int));
if(vv1<vv2)
return -1;

if(vv1>vv2)
return 1;

return 0;
}
//-------------------------------------------------------
void Tone (UBitmap &inpImg, UBitmap &outImg, string ftype, double gamma)
{
int Width = outImg.GetWidth();
int Height = outImg.GetHeight();
int iY , iX;
if (ftype == "Негатив") {
for ( iY = 0; iY < Height; iY ++)
  {
	for ( iX = 0; iX < Width; iX ++)
	 {
	 outImg(iX,iY).r = 255 - inpImg(iX,iY).r;
	 outImg(iX,iY).g = 255 - inpImg(iX,iY).g;
	 outImg(iX,iY).b = 255 - inpImg(iX,iY).b;
	 }
   }
	} else {
	if (ftype == "Логарифм") {
	for ( iY = 0; iY < Height; iY ++)
  {
	for ( iX = 0; iX < Width; iX ++)
	 {
	 outImg(iX,iY).r = 256*log(inpImg(iX,iY).r/256.0+1)/log(2);
	 outImg(iX,iY).g = 256*log(inpImg(iX,iY).g/256.0+1)/log(2);
	 outImg(iX,iY).b = 256*log(inpImg(iX,iY).b/256.0+1)/log(2);
	 }
   }
	} else {
	if (ftype == "Показатель") {
	for ( iY = 0; iY < Height; iY ++)
  {
	for ( iX = 0; iX < Width; iX ++)
	 {
	 outImg(iX,iY).r = 256*(exp(inpImg(iX,iY).r/256.0)-1)/(M_E - 1);
	 outImg(iX,iY).g = 256*(exp(inpImg(iX,iY).g/256.0)-1)/(M_E - 1);
	 outImg(iX,iY).b = 256*(exp(inpImg(iX,iY).b/256.0)-1)/(M_E - 1);
	 }
   }
	} else {
	if (ftype == "Гамма") {
	for ( iY = 0; iY < Height; iY ++)
  {
	for ( iX = 0; iX < Width; iX ++)
	 {
	 outImg(iX,iY).r = 256*pow(inpImg(iX,iY).r/256.0, gamma);
	 outImg(iX,iY).g = 256*pow(inpImg(iX,iY).g/256.0, gamma);
	 outImg(iX,iY).b = 256*pow(inpImg(iX,iY).b/256.0, gamma);
	 }
   }
	}
	}   }   }

}
//-------------------------------------------------------

