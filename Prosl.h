/* ************************************************************************** */
// Copyright Anton Fateev, 2009.
// E-mail: antonfat@gmail.com
/* ************************************************************************** */
//---------------------------------------------------------------------------

#ifndef ProslH
#define ProslH
//---------------------------------------------------------------------------
#include "UBitmap.h"
	#include <vector>
    using namespace std;  
using namespace Utilities;

void ProslK (UBitmap &inpImg, vector<int> &Xpoint1, vector<int> &Ypoint1, vector<int> &Type1, int Area[], unsigned char &ColK, int &pn, bool &AP);
void ScanP (UBitmap &inpImg,  vector<int> &Xpoint1, vector<int> &Ypoint1, vector<int> &Type1, int &pn, int Area[], unsigned char &ColK, bool &AP, vector<char> &circleX, vector<char> &circleY, int &Npointc);
void CircleTr (int &Npc, int &xc, int &yc, int &pn, vector<int> &Xpoint1, vector<int> &Ypoint1, int &h, int &w, vector<char> &circleX, vector<char> &circleY, int &Npointc);
void circleTrp (int &Npc, int &xc, int &yc, int &pn, vector<int> &Xpoint1, vector<int> &Ypoint1, int &h, int &w, vector<char> &circleX, vector<char> &circleY, int &Npointc);
void MakeArea (int &Xa, int &Ya, int *Area);
void makeCircle (vector<char> &circleX, vector<char> &circleY, int &Npointc);
void plus1  (int &Num, int &Size);
void minus1 (int &Num, int &Size);
void getColorK (UBitmap &inpImg,  vector<int> &Xpoint1, vector<int> &Ypoint1, unsigned char &ColK);


//---------------------------------------------------------------------------
#endif
