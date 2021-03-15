/* ************************************************************************** */
// Copyright Anton Fateev, 2009.
// E-mail: antonfat@gmail.com
/* ************************************************************************** */
//---------------------------------------------------------------------------

#ifndef CannyH
#define CannyH

#include "UBitmap.h"
	 #include <vector>
      using namespace std;  
using namespace Utilities;

void CannyF (UBitmap &inpImg, UBitmap &outImg, UBitmap &outKon, int sigma, int Th, int Tl,  int sklon=1);
void Roberts (UBitmap &outImg, UBitmap &outKon, bool &degMask);
void Suppress (UBitmap &outImg, UBitmap &outKon,  bool degMask);
void Naprav (unsigned short int &Degri,char &deltaX,char &deltaY);
void Detect(UBitmap &outImg, UBitmap &outKon, int Th, int Tl, int Area[]);
void FollowD(UBitmap &outImg, UBitmap &outKon, int iX, int iY, int Th, int Tl, int *Area);
//---------------------------------------------------------------------------
#endif
