/* ************************************************************************** */
// Copyright Anton Fateev, 2008-2009.
// E-mail: antonfat@gmail.com
/* ************************************************************************** */
#ifndef FilterH
#define FilterH

#include "UBitmap.h"
	 #include <vector>
      using namespace std;  
using namespace Utilities;

void Filter(UBitmap &inpImg, UBitmap &outImg, string ntype, int N=5,  int sklon=1);
void Mask(vector<int> &buff,char typeF,int &S,int n=3, int sklon=1);
void FilterPixel(UBitmap &inpImg, UBitmap &outImg,int iX,int iY,vector<int> &Mf, int Area[],int Sum,int h);
void FilterMedian(UBitmap &inpImg, UBitmap &outImg,int iX,int iY, int Area[],int h);
void Tone (UBitmap &inpImg, UBitmap &outImg, string ftype, double gamma = 1.0);
int elemsort(const void *v1,const void *v2);
//---------------------------------------------------------------------------
#endif
