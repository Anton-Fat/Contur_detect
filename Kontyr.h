/* ************************************************************************** */
// Copyright Anton Fateev, 2009.
// E-mail: antonfat@gmail.com
/* ************************************************************************** */
//---------------------------------------------------------------------------
  
#ifndef KontyrH
#define KontyrH
//---------------------------------------------------------------------------
#include "UBitmap.h"
	#include <vector>
    using namespace std;  
using namespace Utilities;

void Markir (UBitmap &inpImg, UBitmap &outImg, int &nmark, bool Stor );
void Remark (UBitmap &outImg, int iY, short int A, short int B);
void MarkirF (UBitmap &inpImg, UBitmap &outImg, int &nmark, bool Stor );
void FollowM (UBitmap &inpImg, UBitmap &outImg,short int iX, short int iY, int &nmark, bool &Stor, int Area[]);
void KontyrV (UBitmap &inpImg, vector<int> &Xpoint1, vector<int> &Ypoint1, char &Ogib);
void KontyrP (UBitmap &inpImg, vector<int> &Xpoint1, vector<int> &Ypoint1, vector<int> &Napr1, char &Ogib, int &minY);
void GetKontType (vector<int> &Xpoint1, vector<int> &Ypoint1, vector<int> &Type1);

struct smark
{
 unsigned char Ncol;
 int Xc, Yc;
 int Npoint;
};
//void KontMark (UBitmap &inpImg, smark *konp);
//void ErSmall (UBitmap &inpImg, smark *konp, short int &H);
  void KontMark (UBitmap &inpImg, vector<smark> &konp);
  void ErSmall  (UBitmap &inpImg, vector<smark> &konp, short int &H);

#endif
