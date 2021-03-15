/* ************************************************************************** */
// Copyright Anton Fateev, 2009.
// E-mail: antonfat@gmail.com
/* ************************************************************************** */
#include <math.h>

#pragma hdrstop

#include "Canny.h"
#include "Filter.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)


void CannyF (UBitmap &inpImg, UBitmap &outImg, UBitmap &outKon, int sigma, int Th, int Tl, int sklon)
{
bool N;
Filter(inpImg, outImg, "Гаусс", sigma, sklon);
Roberts(outImg, outKon, N);
Suppress(outImg, outKon, N);
int Area[4]= {0,0,1,1};
Area[2]= inpImg.GetWidth();
Area[3]= inpImg.GetHeight();
Detect(outImg, outKon, Th, Tl, Area);
}
//---------------------------------------------------
void Roberts (UBitmap &outImg, UBitmap &outKon, bool &degMask)
{
int Rx, Ry;
Rx=Ry=0; degMask = true;
int Width = outImg.GetWidth();
int Height = outImg.GetHeight();
for (int iY = 0; iY < Height; iY ++)
  {
	for (int iX = 0; iX < Width; iX ++)
	 {  if (iX==(Width-1)||iY==(Height-1)) {
		outKon(iX,iY).r = 0;
		outKon(iX,iY).b = 0;

		} else {
			 Rx = outImg(iX+1,iY).r - outImg(iX,iY+1).r;
			 Ry = outImg(iX,iY).r - outImg(iX+1,iY+1).r;
			 outKon(iX,iY).r = sqrt((Rx*Rx+Ry*Ry)/2);
			 if (Rx==0) {
			   outKon(iX,iY).b = 0;
			 }  else {  if (Ry < 0) {
			  outKon(iX,iY).b = atan2(Ry,Rx)*128/M_PI + 256;
						} else {
			 outKon(iX,iY).b = atan2(Ry,Rx)*128/M_PI;
			 }	}  }
	 }
  }
}
//----------------------------------------------------
void Suppress (UBitmap &outImg, UBitmap &outKon, bool degMask)
{
unsigned short int Napr = 0;
char dx, dy;
  int Width = outKon.GetWidth();
int Height = outKon.GetHeight();
for (int iY = 0; iY < Height; iY ++)
  {
	for (int iX = 0; iX < Width; iX ++)
	 {
	 Napr = ((outKon(iX,iY).b / 32)+degMask)%8;    //xy.quot;
	   Naprav (Napr, dx, dy);
		   outKon(iX,iY).g = outKon(iX,iY).r;
	   if ((iX!=0)&&(iX!=Width-1)&&(iY!=0)&&(iY!=Height-1)) {
		 if (outKon(iX,iY).r < outKon(iX+dx,iY+dy).r) {
			 outKon(iX,iY).g =0 ;
		 }
		 if (outKon(iX,iY).r < outKon(iX-dx,iY-dy).r) {
			 outKon(iX,iY).g =0 ;
		 }
			   } else {
				 if (iX+dx>=0&&iX+dx<Width&&iY+dy>=0&&iY+dy<Height) {
				 if (outKon(iX,iY).r < outKon(iX+dx,iY+dy).r) {
			 outKon(iX,iY).g =0 ;
									}	}
					if (iX-dx>=0&&iX-dx<Width&&iY-dy>=0&&iY-dy<Height) {
					  if (outKon(iX,iY).r < outKon(iX-dx,iY-dy).r) {
			 outKon(iX,iY).g =0 ;
									 }	 }
					  }
			 outImg(iX,iY).r= outImg(iX,iY).g=outImg(iX,iY).b=0;
		 }
  }
}

void Naprav (unsigned short int &Degri,char &deltaX,char &deltaY)
{
 //Degri = Degri%8;
 if (((Degri+2)%8)%4 == 0) {  deltaX = 0;  }  else {
		  deltaX = 1-((((Degri+2)%8)>>2) << 1);          }
	   if (Degri%4 == 0) { deltaY = 0;  }  else {
		  deltaY = 1-((Degri>>2) << 1);       }
}
//-----------------------------------------------------------
void Detect(UBitmap &outImg, UBitmap &outKon, int Th, int Tl, int Area[])
{

 //int Width = outKon.GetWidth();
//int Height = outKon.GetHeight();

for (int iY = Area[1]; iY < Area[3]; iY ++)
  {
	for (int iX = Area[0]; iX < Area[2]; iX ++)
	 {

	 if (outKon(iX,iY).g > Th) {

	   outImg(iX,iY).r = outImg(iX,iY).b= outImg(iX,iY).g = 255;
	   FollowD (outImg, outKon, iX, iY, Th, Tl, Area);
	 }
	  }   }

}

void FollowD(UBitmap &outImg, UBitmap &outKon, int iX, int iY, int Th, int Tl, int *Area)
{
  Tl = Th/2;
  char dx, dy;
 if ((iX>Area[0])&&(iX<Area[2]-1)&&(iY>Area[1])&&(iY<Area[3]-1)) {
   for (unsigned short int Napr = 0; Napr <= 8; Napr++) {
  Naprav (Napr, dx, dy);
	 if (outImg(iX+dx,iY+dy).r==0)  { if (outKon(iX+dx,iY+dy).g <= Th && outKon(iX+dx,iY+dy).g > Tl) {
								   outImg(iX+dx,iY+dy).r =outImg(iX+dx,iY+dy).g =outImg(iX+dx,iY+dy).b = 128;
	  FollowD(outImg, outKon, iX+dx, iY+dy, Th, Tl, Area);
									  } else {
											// outImg(iX+dx,iY+dy).r =outImg(iX+dx,iY+dy).g =outImg(iX+dx,iY+dy).b = 50;
											 }
									 }
		}
 } else{
	for (unsigned short int Napr = 0; Napr <= 8; Napr++) {
	Naprav (Napr, dx, dy);
	if ((iX+dx>=Area[0])&&(iX+dx<=Area[2]-1)&&(iY+dy>=Area[1])&&(iY+dy<=Area[3]-1)) {
if (outImg(iX+dx,iY+dy).r==0)  { if (outKon(iX+dx,iY+dy).g <= Th && outKon(iX+dx,iY+dy).g > Tl) {
								   outImg(iX+dx,iY+dy).r =outImg(iX+dx,iY+dy).g =outImg(iX+dx,iY+dy).b = 128;
	  FollowD(outImg, outKon, iX+dx, iY+dy, Th, Tl, Area);
									  } else {
										  //	 outImg(iX+dx,iY+dy).r =outImg(iX+dx,iY+dy).g =outImg(iX+dx,iY+dy).b = 50;
											 }
									 }
		 }

	}
 }


}


  //*/
