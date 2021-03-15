/* ************************************************************************** */
// Copyright Anton Fateev, 2009.
// E-mail: antonfat@gmail.com
/* ************************************************************************** */
//---------------------------------------------------------------------------

#ifndef MorfH
#define MorfH

#include "UBitmap.h"
      #include <vector>
	  using namespace std;
using namespace Utilities;


void FilterMorfP(UBitmap &inpImg, UBitmap &outImg, string ntype,bool Stor ,int N);
void FilterMorfM(UBitmap &inpImg, UBitmap &outImg, string ntype,bool Stor ,int N);
void MorfInd (vector<int> &Mm, int &height, int &index, unsigned short int &dmx, unsigned short int &dmy);
void MorfMask (vector<int> &Mm, string &ntype, int &h, unsigned short int &npoint);
void FillColor (UBitmap &inpImg, string ncolor, int h);
void MakeGrayIm (UBitmap &inpImg);

//---------------------------------------------------------------------------
#endif
