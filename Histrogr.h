/* ************************************************************************** */
// Copyright Anton Fateev, 2009.
// E-mail: antonfat@gmail.com
/* ************************************************************************** */
//---------------------------------------------------------------------------

#ifndef HistrogrH
#define HistrogrH
//---------------------------------------------------------------------------
#include "UBitmap.h"
	#include <vector>
    using namespace std;  
using namespace Utilities;

void MakeGistr (UBitmap &inpImg, string ncolor,  vector <int> &SumG);
void PolAreaN (UBitmap &inpImg, unsigned char &Intens);
void SmalKont (vector<int> &Xpoint1, vector<int> &Ypoint1, vector<int> &Napr1, vector<int> &Type1);
void PreobrGor (vector<int> &Xpoint1, vector<int> &Ypoint1, vector<int> &Xd1, vector<int> &Yd1, int &h, int &w);
void GetPloX (int &x, int &y, int &xd, double &A, double &B);
void GetPloY (int &y, int &yd, double &A, double &B);


#endif
