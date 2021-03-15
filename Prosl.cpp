/* ************************************************************************** */
// Copyright Anton Fateev, 2009.
// E-mail: antonfat@gmail.com
/* ************************************************************************** */
//---------------------------------------------------------------------------


#pragma hdrstop

#include "Prosl.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//void FollowK

//-----------------------------------------------------------------

void ProslK (UBitmap &inpImg, vector<int> &Xpoint1, vector<int> &Ypoint1, vector<int> &Type1, int Area[], unsigned char &ColK, int &pn, bool &AP)
{
 // GetKontType (KPoint1.Xp1, KPoint1.Yp1, KPoint1.Type1);
  vector<char> circleX, circleY; int Npointc = 40;
  makeCircle (circleX, circleY, Npointc);

  AP = false;
  while ((AP == false)&&(pn < Xpoint1.size()-1 ))
  {
  pn++;
  if ((Type1[pn] != 3)&&(true)) {
  ScanP (inpImg, Xpoint1, Ypoint1, Type1, pn, Area, ColK, AP, circleX, circleY, Npointc);
                                }
  }
  //pn--;
  if (AP) {
  Area[0]=Area[2]= Xpoint1[pn];
  Area[1]=Area[3]= Ypoint1[pn];
  char Num=0;
  char maxAreaP = 100;
  while ((AP == true)&&(Num++ < maxAreaP))
  {
  if ((Type1[pn] != 3)&&(true)) {
  ScanP (inpImg, Xpoint1, Ypoint1, Type1, pn, Area, ColK, AP, circleX, circleY, Npointc);  // Получили Area
  if (AP) { Type1[pn] = 3; }
								}
  pn++;
  }
  AP = true;
		} //Обнаружен участок
}
//-------------------------------------------------------------------

void ScanP (UBitmap &inpImg,  vector<int> &Xpoint1, vector<int> &Ypoint1, vector<int> &Type1, int &pn, int Area[], unsigned char &ColK, bool &AP,vector<char> &circleX, vector<char> &circleY, int &Npointc)
{

  int NpointK = Xpoint1.size();
 int M = 0; bool kp1 = false, kp2 = false;     int h = inpImg.GetHeight(), w = inpImg.GetWidth();
 int xc, yc, Npc, Npc2, ProvK ;                  //int Npointc = 40; //
 int pn2;    AP = false;
  int dist=0, dist2, pndist, pndist2;

	 pn2=pn;
 while ((kp1 == false))//&&(M++ < 1000))
   {
	   Npc = 0;
	 minus1 ( pn2, NpointK);

	 while ((kp1 == false)&&(Npc < Npointc))
	 {
	   CircleTr (Npc, xc, yc, pn, Xpoint1, Ypoint1, h, w, circleX, circleY, Npointc);
	   if ((xc == Xpoint1[pn2])&&(yc == Ypoint1[pn2])) { kp1 = true;  }
	   Npc++;
	 }
   }  // Npc- следующая на окружности

	  M=0;
	  pn2=pn;
  while ((kp2 == false))//&&(M++ < 1000))
   {
	  Npc2 = 0;
	 plus1 ( pn2, NpointK);
	 while ((kp2 == false)&&(Npc2 < Npointc))
	 {
	   CircleTr (Npc2, xc, yc, pn, Xpoint1, Ypoint1, h, w, circleX, circleY, Npointc);
	   if ((xc == Xpoint1[pn2])&&(yc == Ypoint1[pn2])) { kp2 = true;  }
	   Npc2++; 
	 }
   }      //Получили координаты KP2
				   //*/
	   //Npc--;
	   Npc2--;
   while ((true)&&(Npc != Npc2)&&(Npc < 10*Npointc))
   {
	 //plus1 ( Npc, Npointc);
	 M=0; dist = 0; dist2 = 0;  ProvK = 0;
	 CircleTr (Npc, xc, yc, pn, Xpoint1, Ypoint1, h, w, circleX, circleY, Npointc);

	  if ((inpImg(xc, yc).r != 0)||(inpImg(xc, yc).g != 0)||(inpImg(xc, yc).b != 0))
	  {
		if ((inpImg(xc, yc).g != ColK)&&(inpImg(xc, yc).r == inpImg(xc, yc).g))
		{
		AP = true;
		MakeArea (xc, yc, Area);
		} else {       /* неизвестная неточность
			 //if (inpImg(xc, yc).r == 101)  // Обнаружили точку контура
			 while (((xc != Xpoint1[ProvK])||(yc != Ypoint1[ProvK]))&&(ProvK < NpointK))
			 {   ProvK++;  	 }
			 if ((xc == Xpoint1[ProvK])&&(yc == Ypoint1[ProvK]))
			 { // Обнаружили точку контура

			   if (Npc != Npc2) {  //Проверили что не конечная
					  //
			   pn2 = pn;
			   while (((Xpoint1[pn2] != xc)||(Ypoint1[pn2] != yc))&&(M++ < 10000))
			   {
			   plus1 ( pn2, NpointK);
			   }   // Получили pn2 на точке К.
					   //* /
				pndist = pn;       dist  = 0;
				pndist2 = pn2;     dist2 = 0;

				while ((Type1[pndist] == 2)&&(pndist != pndist2)) {
				  dist2++;
				  minus1 ( pndist, NpointK);
				}
				while (pndist != pndist2) {
				  plus1 ( pndist2, NpointK);
				  if (Type1[pndist] == 1) {	  dist2++;	  }
									  }    // Получили dist2


				pndist = pn;  pndist2 = pn2;

				while ((Type1[pndist] == 2)&&(pndist != pndist2)) {
				  plus1 ( pndist, NpointK);
				  dist++;
				  if ((Xpoint1[pndist] == Xpoint1[pn])&&(Ypoint1[pndist] == Ypoint1[pn])) { dist = 0; }
														  }
				 while ((Type1[pndist2] == 2)&&(pndist != pndist2)) {
				   dist++;
				  minus1 ( pndist2, NpointK);
				 }      //Просмотрели 2 тип для dist

				 while (pndist != pndist2)  {
				   plus1 ( pndist, NpointK);
				   if (Type1[pndist] == 1) {  dist++;  }
									   }   // Получили dist
					  M = 10;
				 if ((dist2 > 5*Npointc )&&(dist > 5*Npointc)) {
				   AP = true;             //  Обасть расширена
				   MakeArea (xc, yc, Area);
									   }

						} // Проверка kp2
			  }  //*/   // Проверили точку контура

			 }     // Вышли если маркировка контура не совпадает с точкой
		}   // Проверили отличную точку
		plus1 ( Npc, Npointc);
   }      //Дошли до kp2

   if (AP) { MakeArea (Xpoint1[pn], Ypoint1[pn], Area);  }
}
//--------------------------------------------------------------------
	  /*
void CircleTr (int &Npc, int &xc, int &yc, int &pn, vector<int> &Xpoint1, vector<int> &Ypoint1, int &h, int &w, vector<char> &circleX, vector<char> &circleY, int &Npointc)
{
	int xc2, yc2;
	do {
	circleTrp(Npc, xc, yc, pn, Xpoint1, Ypoint1, h, w, circleX, circleY, Npointc);
	if (Npc < 1) { Npc = Xpoint1.size(); }
	circleTrp(Npc-1, xc2, yc2, pn, Xpoint1, Ypoint1, h, w, circleX, circleY, Npointc);
	Npc++;
	} while ((xc == xc2)&&(yc == yc2));
	Npc--;
}     //*/   // circleTrp
//--------------------------------------------------------------------
   // Функция используется только для CircleTr
void CircleTr (int &Npc, int &xc, int &yc, int &pn, vector<int> &Xpoint1, vector<int> &Ypoint1, int &h, int &w, vector<char> &circleX, vector<char> &circleY, int &Npointc)
{ 
  Npc = Npc%Npointc;
  xc = Xpoint1[pn]+ circleX[Npc];
  yc = Ypoint1[pn]+ circleY[Npc];
  if (xc < 0) { xc = 0; }
  if (yc < 0) { yc = 0; }
  if (xc >= w) { xc = w-1; }
  if (yc >= h) { yc = h-1; }

}
//--------------------------------------------------------------------

void MakeArea (int &Xa, int &Ya, int *Area)
{
  if (Xa < Area[0]) { Area[0] = Xa; }
  if (Ya < Area[1]) { Area[1] = Ya; }
  if (Xa > Area[2]) { Area[2] = Xa; }
  if (Ya > Area[3]) { Area[3] = Ya; }
}
//--------------------------------------------------------------------
void makeCircle (vector<char> &circleX, vector<char> &circleY, int &Npointc)
{
  circleX.resize(Npointc); circleY.resize(Npointc);
  circleX[0]= 5   ;  circleY[0]= 0 ;
  circleX[1]= 5   ;  circleY[1]= 1 ;
  circleX[2]= 5   ;  circleY[2]= 2 ;
  circleX[3]= 4   ;  circleY[3]= 2 ;
  circleX[4]= 4   ;  circleY[4]= 3 ;
  circleX[5]= 4   ;  circleY[5]= 4 ;
  circleX[6]= 3   ;  circleY[6]= 4 ;
  circleX[7]= 2   ;  circleY[7]= 4 ;
  circleX[8]= 2   ;  circleY[8]= 5 ;
  circleX[9]= 1   ;  circleY[9]= 5 ;

  circleX[10]= 0  ;  circleY[10]= 5 ;
  circleX[11]= -1 ;  circleY[11]= 5 ;
  circleX[12]= -2 ;  circleY[12]= 5 ;
  circleX[13]= -2 ;  circleY[13]= 4 ;
  circleX[14]= -3 ;  circleY[14]= 4 ;
  circleX[15]= -4 ;  circleY[15]= 4 ;
  circleX[16]= -4 ;  circleY[16]= 3 ;
  circleX[17]= -4 ;  circleY[17]= 2 ;
  circleX[18]= -5 ;  circleY[18]= 2 ;
  circleX[19]= -5 ;  circleY[19]= 1 ;

  circleX[20]= -5 ;  circleY[20]= 0 ;
  circleX[21]= -5 ;  circleY[21]= -1 ;
  circleX[22]= -5 ;  circleY[22]= -2 ;
  circleX[23]= -4 ;  circleY[23]= -2 ;
  circleX[24]= -4 ;  circleY[24]= -3 ;
  circleX[25]= -4 ;  circleY[25]= -4 ;
  circleX[26]= -3 ;  circleY[26]= -4 ;
  circleX[27]= -2 ;  circleY[27]= -4 ;
  circleX[28]= -2 ;  circleY[28]= -5 ;
  circleX[29]= -1 ;  circleY[29]= -5 ;

  circleX[30]= 0  ;  circleY[30]= -5 ;
  circleX[31]= 1  ;  circleY[31]= -5 ;
  circleX[32]= 2  ;  circleY[32]= -5 ;
  circleX[33]= 2  ;  circleY[33]= -4 ;
  circleX[34]= 3  ;  circleY[34]= -4 ;
  circleX[35]= 4  ;  circleY[35]= -4 ;
  circleX[36]= 4  ;  circleY[36]= -3 ;
  circleX[37]= 4  ;  circleY[37]= -2 ;
  circleX[38]= 5  ;  circleY[38]= -2 ;
  circleX[39]= 5  ;  circleY[39]= -1 ;




}
//--------------------------------------------------------------------
void plus1 (int &Num, int &Size)
{
  if (Num == Size-1)
  { Num = 0;
  } else { Num++; }
}
//--------------------------------------------------------------------
void minus1 (int &Num, int &Size)
{
  if (Num == 0) { Num = Size-1;
   } else { Num--; }
}
//--------------------------------------------------------------------
void getColorK (UBitmap &inpImg,  vector<int> &Xpoint1, vector<int> &Ypoint1, unsigned char &ColK)
{
int w = inpImg.GetWidth(), h = inpImg.GetHeight(), i = 0, NpointK = Xpoint1.size();
while (((Xpoint1[i] == 0)||( Ypoint1[i] == 0)||(Xpoint1[i] == w-1)||(Ypoint1[i] == h-1))&&(i < NpointK-1))
{ i++; }
ColK = inpImg(Xpoint1[i], Ypoint1[i]).g;
}
 //--------------------------------------------------------------------


   //*/
