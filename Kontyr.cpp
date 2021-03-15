/* ************************************************************************** */
// Copyright Anton Fateev, 2009.
// E-mail: antonfat@gmail.com
/* ************************************************************************** */
//---------------------------------------------------------------------------

#include <string>

#pragma hdrstop

#include "Kontyr.h"
#include "Morf.h"
#include "Canny.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void Markir (UBitmap &inpImg, UBitmap &outImg, int &nmark, bool Stor )
{
int realmark = 1;   int de = 1;
vector<unsigned char> tempC;
unsigned char Col;
FillColor(outImg, "Red", 0 );
FillColor(outImg, "Green", 0 );
FillColor(outImg, "Blue", 0 );
int Area[4]= {0,0,1,1};
Area[2]= inpImg.GetWidth();
Area[3]= inpImg.GetHeight();
int N = 0;         //00
//nmark = 50;
int iY = 0;
int iX = 0;
unsigned char A, B;      //short int
  if (Stor!=(inpImg(iX,iY).r > N)){
   outImg(iX,iY).r = outImg(iX,iY).g =outImg(iX,iY).b  = nmark*de;
   }
	for (iX = 1; iX < Area[2]; iX ++)
	 { if (Stor!=(inpImg(iX,iY).r > N)){
	  if (outImg(iX-1,iY).r >0) {
	  outImg(iX,iY).r = outImg(iX,iY).g =outImg(iX,iY).b = outImg(iX-1,iY).r;
	  } else {
	   realmark+=1;            //nmark++;
	   if ( !tempC.empty() ) { Col = tempC.back() ; tempC.pop_back(); } else { Col = (nmark++)*de; }
	   outImg(iX,iY).r = outImg(iX,iY).g =outImg(iX,iY).b = Col;
	 }  }  }
for (iY = 1; iY < Area[3]; iY ++)
  {   iX = 0;
	if (Stor!=(inpImg(iX,iY).r > N)){
	if (outImg(iX,iY-1).r > 0) {
	outImg(iX,iY).r = outImg(iX,iY).g =outImg(iX,iY).b = outImg(iX,iY-1).r;
	} else { if (outImg(iX+1,iY-1).r > 0) {
	outImg(iX,iY).r = outImg(iX,iY).g =outImg(iX,iY).b = outImg(iX+1,iY-1).r;
	} else {
	realmark+=1;          //nmark++;
	if ( !tempC.empty() ) { Col = tempC.back() ; tempC.pop_back(); } else { Col = (nmark++)*de; }
	outImg(iX,iY).r = outImg(iX,iY).g =outImg(iX,iY).b = Col;
	}
	 }  }

	for (int iX = 1; iX < Area[2]-1; iX ++)
	 {
	  if (Stor!=(inpImg(iX,iY).r > N)){
	  if (outImg(iX-1,iY).r+outImg(iX-1,iY-1).r+outImg(iX,iY-1).r+outImg(iX+1,iY-1).r > 0)
	  {
		if ((outImg(iX-1,iY).r > 0)) {
	   A = outImg(iX-1,iY).r;
	   } else { if ((outImg(iX-1,iY-1).r > 0))
	   {
	   A = outImg(iX-1,iY-1).r;
	   }  else {
	   A=0;
	   }   }

	   if ((outImg(iX,iY-1).r > 0)) {
	   B = outImg(iX,iY-1).r;
	   } else { if ((outImg(iX+1,iY-1).r > 0)) {
	   B = outImg(iX+1,iY-1).r;
	   }  else {
	   B=0;
	   }   }

	   if (((A>0)&&(A==B))||((A>0)&&(B==0))) {
	   outImg(iX,iY).r = outImg(iX,iY).g =outImg(iX,iY).b = A;
	   } else { if ((B>0)&&(A==0)) {
	   outImg(iX,iY).r = outImg(iX,iY).g =outImg(iX,iY).b = B;       
		  } else { if ((A*B>0)&&(A!=B)) {
		   outImg(iX,iY).r = outImg(iX,iY).g =outImg(iX,iY).b = A;
		   tempC.push_back(B);
		 Remark (outImg, iY, A, B); realmark-=1;           // Переобозначение
			 }  }  }

		} else {
		realmark+=1;        //nmark++;
		if ( !tempC.empty() ) { Col = tempC.back() ; tempC.pop_back(); } else { Col = (nmark++)*de; }
		outImg(iX,iY).r = outImg(iX,iY).g =outImg(iX,iY).b = Col;
			 }
		}
	   }     // iX

	  iX = Area[2]-1;
	  if (Stor!=(inpImg(iX,iY).r > N)){
	  if (outImg(iX-1,iY-1).r+outImg(iX-1,iY).r+outImg(iX,iY-1).r > 0)
	  {
	  if (outImg(iX-1,iY-1).r > 0) {
	  outImg(iX,iY).r = outImg(iX,iY).g =outImg(iX,iY).b = outImg(iX-1,iY-1).r;
	  } else {
	   if (((outImg(iX-1,iY).r == outImg(iX,iY-1).r)&&(outImg(iX-1,iY).r != 0))||((outImg(iX-1,iY).r *outImg(iX,iY-1).r ==0)&&(outImg(iX-1,iY).r +outImg(iX,iY-1).r > 0)))
	   {
	  if ((outImg(iX,iY-1).r > 0)&&(outImg(iX-1,iY).r == 0))
	  {
	   outImg(iX,iY).r = outImg(iX,iY).g =outImg(iX,iY).b = outImg(iX,iY-1).r;
	   } if ((outImg(iX-1,iY).r > 0)&&(outImg(iX,iY-1).r == 0))
	   {
		 outImg(iX,iY).r = outImg(iX,iY).g =outImg(iX,iY).b = outImg(iX-1,iY).r;
		 } } else { if ((outImg(iX-1,iY).r > 0)&&(outImg(iX,iY-1).r > 0)&&(outImg(iX-1,iY).r != outImg(iX,iY-1).r))
		 {
		 A = outImg(iX-1,iY).r; B = outImg(iX,iY-1).r;
		 outImg(iX,iY).r = outImg(iX,iY).g =outImg(iX,iY).b = A;
           tempC.push_back(B);
		 Remark (outImg, iY, A, B); realmark-=1;     // Переобозначение
			}
	  } } } else {
	  realmark+=1;      //nmark++;
	  if ( !tempC.empty() ) { Col = tempC.back() ; tempC.pop_back(); } else { Col = (nmark++)*de; }
	  outImg(iX,iY).r = outImg(iX,iY).g =outImg(iX,iY).b = Col;
	   }
		}
	  }     // iY
	  nmark = realmark;
}
//-------------------------------------------------------
void Remark (UBitmap &outImg, int iY, short int A, short int B)
{
unsigned int Width = outImg.GetWidth();
for (int Y = 0; Y <= iY; Y ++)
  {
  for (int X = 0; X < Width; X ++)
   {  if (outImg(X,Y).r == B) {
		outImg(X,Y).r=outImg(X,Y).g=outImg(X,Y).b = A;
			   			}
		 }
	  }
}
//------------------------------------------------------
	  //С прослеживанием
void MarkirF (UBitmap &inpImg, UBitmap &outImg, int &nmark, bool Stor )
{

FillColor(outImg, "Red", 0 );
int Area[4]= {0,0,1,1};
Area[2]= inpImg.GetWidth();
Area[3]= inpImg.GetHeight();
short int N = 100;
nmark = 0;
for (short int iY = 0; iY < Area[3]; iY ++)
  {
	for (short int iX = 0; iX < Area[2]; iX ++)
	 {

	 if (outImg(iX,iY).r== 0 ) {  if (Stor!=(inpImg(iX,iY).r > N))  {
	   nmark++;
	   if (nmark%256==0) {
	   nmark++;
	   }
	   outImg(iX,iY).r = outImg(iX,iY).g =outImg(iX,iY).b  = nmark*1;
	   FollowM (inpImg, outImg, iX, iY, nmark, Stor, Area);
	 }   }
	  }   }

}
//-------------------------------------------------------
void FollowM(UBitmap &inpImg, UBitmap &outImg,short int iX,short int iY, int &nmark, bool &Stor, int Area[])
{
 //short int N = 100;
  char dx, dy;
 if ((iX>Area[0])&&(iX<Area[2]-1)&&(iY>Area[1])&&(iY<Area[3]-1)) {
   for (unsigned short int Napr = 0; Napr <= 8; Napr++) {
  Naprav (Napr, dx, dy);     // от Кэнни
	 if (outImg(iX+dx,iY+dy).r== 0 ) {  if (Stor!=(inpImg(iX+dx,iY+dy).r > 100))  {
	  outImg(iX+dx,iY+dy).r = outImg(iX+dx,iY+dy).g =outImg(iX+dx,iY+dy).b  =nmark*1;
	  FollowM(inpImg, outImg, iX+dx, iY+dy, nmark, Stor, Area);
				   }	   }
													   }
	   } else {
	for (unsigned short int Napr = 0; Napr <= 8; Napr++)
	{
	Naprav (Napr, dx, dy);
	if ((iX+dx>=Area[0])&&(iX+dx<=Area[2]-1)&&(iY+dy>=Area[1])&&(iY+dy<=Area[3]-1))
	{
if (outImg(iX+dx,iY+dy).r== 0 ) {  if (Stor!=(inpImg(iX+dx,iY+dy).r > 100))
{
	outImg(iX+dx,iY+dy).r =outImg(iX+dx,iY+dy).g =outImg(iX+dx,iY+dy).b  = nmark*1;  //nmark
	  FollowM(inpImg, outImg, iX+dx, iY+dy, nmark, Stor, Area);
					}     }
				 }
											   }
			  }
}
//------------------------------------------------------

void KontyrV (UBitmap &inpImg, vector<int> &Xpoint1, vector<int> &Ypoint1, char &Ogib)
{       /*
Xpoint1.resize(n*n);
	for(size_t i=0;i<n*n;i++)
	Xpoint1[i]=
	 //*/
Xpoint1.clear();
Ypoint1.clear();

unsigned short int Napr = 6;
char dx, dy, dxf, dyf, dnapr, Nw;
int pX , pY, pX0 , pY0;
bool ugol;
pX = inpImg.GetWidth()/2;
pY = 100;
unsigned char tek;
tek = inpImg(pX, pY).r;
int Nloop = 0;
Nw = 0;
while ( (pY > 0)&&(tek == inpImg(pX, pY-1).r)&&(++Nloop < 1000))
{
pY--;
}
if (pY != 0) {
inpImg(pX, pY-1).r = 101;
}
pX0 = pX; pY0 = pY;
Xpoint1.push_back(pX) ; Ypoint1.push_back(pY) ;   // Perim 1
int i2=0;
do  {             // начало while
 //for (int i=0; i < 3000; i++) {
if (pY == 0) {
  Napr = 0;  }
if (pX == inpImg.GetWidth()-1) {
  Napr = 2;                    }
if (pY == inpImg.GetHeight()-1) {
  Napr = 4;                     }
if (pX == 0) {
  Napr = 6;
  if (pY == 0) {
   Napr = 0;   }
}

Naprav (Napr, dx, dy);
Naprav ((Napr+1)%8, dxf, dyf);
while ((tek != inpImg(pX+dx, pY+dy).r)||((Napr%2 == 1)&&(tek != inpImg(pX+dxf, pY+dyf).r)))
 {
 if (tek != inpImg(pX+dx, pY+dy).r) {
 inpImg(pX+dx, pY+dy).r = 101;    
 }
 Napr++;
 Naprav (Napr%8, dx, dy);
 Naprav ((Napr+1)%8, dxf, dyf);
 }      // конец while
 Napr = Napr%8;
 /*    Работает не стабильно
 dnapr = Napr - Nw + 8;// dnapr = int(dnapr);
 Nw = Napr;
 if ((dnapr>>2)%2 == (dnapr>>3)%2) {
  //int f2r = 9;
  dnapr = (dnapr&~(1<<3))|((1<<3)&~dnapr);
 }
 //int fr = 9;
 dnapr -= 8;
 Ogib = Ogib + dnapr;  //*/
 pX += dx; pY += dy;
 Xpoint1.push_back(pX) ; Ypoint1.push_back(pY) ;  // Perim n
 Napr = (((Napr & ~1)+7)%8);

} while (((pX0 != pX)||(pY0 != pY))&&(++i2 < 5000));  // конец while

 //*/
	//xy.quot;
  //int f=9;

}
//--------------------------------------------------------
void KontyrP (UBitmap &inpImg, vector<int> &Xpoint1, vector<int> &Ypoint1, vector<int> &Napr1, char &Ogib, int &minY)
{
Xpoint1.clear();    //2
Ypoint1.clear();
Napr1.clear();

unsigned short int Napr = 3;
char dx, dy;
int pX , pY, pX0 , pY0;
bool endk = 1, rep = 0, ugol = 0;
pX = inpImg.GetWidth()/2;
pY = minY;
unsigned char tek;
tek = inpImg(pX, pY).r;
int Nloop = 0;
while ( (pY > 0)&&(tek == inpImg(pX, pY).r)&&(++Nloop < 1000))
{
pY--;
}     //pX , pY - 101
inpImg(pX, pY).r = 101;   // Первая точка контура
pX0 = pX; pY0 = pY;
Xpoint1.push_back(pX) ; Ypoint1.push_back(pY) ;   // Perim 1

minY = pY;  Ogib = 0;
int i2=0;
do  {             // начало while     //2

Naprav ((Napr+0)%8, dx, dy);

	   //*/
if ((pX == 0)||(pX == inpImg.GetWidth()-1)||(pY == 0)||(pY == inpImg.GetHeight()-1))
{  // Контур у границы
 if ((pX == inpImg.GetWidth()/2)&&(pY == 0)) {minY = 0; Ogib = 0; }
 while ((0 < pX+dx)&&(pX+dx <inpImg.GetWidth()-1)&&(0 < pY+dy)&&(pY+dy < inpImg.GetHeight()-1)&&(tek == inpImg(pX+dx, pY+dy).r)&&(Napr < 1000))
 {
 Napr++;
 Naprav (Napr%8, dx, dy);
 }
} else{
 ugol =0;
 if ((pX == inpImg.GetWidth()/2)&&(pY <= minY)) {
  if (Napr==2) {  Ogib = 0;   }
  if (Napr==6) {  Ogib = 1; ugol =1; }
 }
 while ((tek == inpImg(pX+dx, pY+dy).r)&&(pX+dx != 0)&&(pX+dx != inpImg.GetWidth()-1)&&(pY+dy !=0)&&(pY+dy !=inpImg.GetHeight()-1)&&(Napr < 1000))
 {
 if ((pX == inpImg.GetWidth()/2)&&(pY <= minY)) {
  minY = pY;
  if ((Napr==2)&&(ugol !=1)) {  Ogib = 0;   }
  if (Napr==6) {  Ogib = 1; ugol =1; }
 }
 Napr++;
 Naprav (Napr%8, dx, dy);
 }      // конец while      //2
   }              //конец else      // Получили напр точки
 Napr = Napr%8;
 if (((pX0 == pX)&&(pY0 == pY))&&(Xpoint1.size()>1)) {
  endk = false;   }
 pX += dx; pY += dy;
 inpImg(pX, pY).r = 101;  // Найденную точку обозначаем
 if ((!endk)&&((pX != Xpoint1[1])||(pY != Ypoint1[1]))) {
   endk = true; rep = true; }
 if (endk) {
  Napr1.push_back(Napr);
  Xpoint1.push_back(pX) ; Ypoint1.push_back(pY) ;  // Perim n
  }
  Napr = ((Napr + 5)%8);

} while (endk &&(++i2 < 15000));  // конец while
if ((minY == pY0)&&((Xpoint1[1]==Xpoint1[Xpoint1.size()-2])||(rep)))
 {  Ogib = 1;   }
}
//---------------------------------------------------------
void GetKontType (vector<int> &Xpoint1, vector<int> &Ypoint1, vector<int> &Type1)
//void GetKontType (spkont *KPoint1)
{
 Type1.assign(Xpoint1.size(),0);
  for (size_t i = 0; i < Xpoint1.size(); i++) {
	if (Type1[i] != 2) {                              //
	 for (size_t j = i+1; j < Xpoint1.size(); j++)
	 {   if ((Xpoint1[i]==Xpoint1[j])&&(Ypoint1[i]==Ypoint1[j])&&(i!=j))    //
		 {
		 Type1[i]=2; Type1[j]=2;
	 }   }
	 if (Type1[i] != 2)
	 {  Type1[i]=1;      }

					   }
	}
}

//---------------------------------------------------------

//void KontMark (UBitmap &inpImg, skont *konp)
void KontMark (UBitmap &inpImg, vector<smark> &konp)
{
 int Xs=0, Ys=0;
 for (int i = 0; i <= 255; i++) {
   //konp.
   konp[i].Npoint = 0;
   konp[i].Ncol = i;               // Цвет области
	 for (int iY = 0; iY < inpImg.GetHeight(); iY ++)
	 {
	   for (int iX = 0; iX < inpImg.GetWidth(); iX ++)
	   {
	if (inpImg(iX,iY).r == i) {
		 konp[i].Npoint++;            // Точек в области
		 Xs += iX; Ys += iY;
		   }
		}
	 }
   if (konp[i].Npoint != 0) {
    konp[i].Xc = Xs / konp[i].Npoint;
	konp[i].Yc = Ys / konp[i].Npoint;
   } else {
   konp[i].Xc = 0 ;
   konp[i].Yc = 0 ;   }
 }
}
//-----------------------------------------------------------

//void ErSmall (UBitmap &inpImg, skont *konp,short int &H)
void ErSmall  (UBitmap &inpImg, vector<smark> &konp, short int &H)
{
   
vector<unsigned char> Vcol;
Vcol.resize(0);
 for (int i = 0; i <= 255; i++)
  {
   if ((konp[i].Npoint < H)&&(konp[i].Npoint != 0))
   {  Vcol.push_back(i);  }
  }

   size_t size=Vcol.size();

   UColorT* data=inpImg.GetData();
   unsigned char *pvcol=0;

   int length=inpImg.GetLength();

   for (int i = 0; i < length; i++,data++)
   {
	  if(size)
		pvcol=&Vcol[0];
		for (size_t i2=0; i2 < size; i2++,pvcol++)
		{
		 if (data->r == *pvcol)
		 {
		 data->c = 0;
		 break;
		 }
	}
   }

}
//-------------------------------------------------------------------

/*

size_t size=Vcol.size();
int w= inpImg.GetWidth();
int h= inpImg.GetHeight();

ColorT* data=inpImg.GetData();
ColorT pixel;
unsigned char *pvcol=0;


for (int iY = 0; iY < h; iY ++)
{
  for (int iX = 0; iX <w; iX ++,data++)
  {
   pixel=*data;
   if(size)
	pvcol=&Vcol[0];
	for (size_t i2=0; i2 < size; i2++,pvcol++)
    {  
	 if (pixel.r == *pvcol)
	 {
	   pixel.r = pixel.g = pixel.b = 0;
	 }
    }
  }
}

*/
/*   Было
vector<unsigned char> Vcol;
Vcol.resize(0);
 for (int i = 0; i <= 255; i++)
  {
   if (konp[i].Npoint < H)
   {  Vcol.push_back(i);  }
  }

	for (int iY = 0; iY < h; iY ++)
	 {
	   for (int iX = 0; iX < w; iX ++)
	   {

	 for (size_t i2=0; i2 < size; i2++)
		 {
			if (inpImg(iX,iY).r == Vcol[i2])
			{ inpImg(iX,iY).r = inpImg(iX,iY).g = inpImg(iX,iY).b = 0;  }
		 }
	 } }
//*/
//--------------------------------------------------------------------

	 /*
int length=inpImg.GetLength();

for (int i = 0; i < length; i++,data++)
{
   if(size)
	pvcol=&Vcol[0];
	for (size_t i2=0; i2 < size; i2++,pvcol++)
	{
	 if (data->r == *pvcol)
	 {
	   data->c = 0;
	 }
	}
}





//*/
//--------------------------------------------------------------------
