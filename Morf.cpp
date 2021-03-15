/* ************************************************************************** */
// Copyright Anton Fateev, 2009.
// E-mail: antonfat@gmail.com
/* ************************************************************************** */
//---------------------------------------------------------------------------
#include <vcl.h>
#include <string>

#pragma hdrstop

#include "Morf.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


void FilterMorfP(UBitmap &inpImg, UBitmap &outImg, string ntype, bool Stor ,int N)
{
  if (N > 15) {
   ShowMessage("Недопустимый размер маски");
   return;
  }
  FillColor(outImg, "Red", 255*Stor);
  unsigned short int dx, dy, npoint;
  vector<int> Mm;
unsigned int Area[4]= {0,0,1,1};
Area[2]= inpImg.GetWidth();
Area[3]= inpImg.GetHeight();
  MorfMask (Mm, ntype, N, npoint);

		div_t xy;
  for (int iY = Area[1]; iY < Area[3]; iY ++)
  {
	for (int iX = Area[0]; iX < Area[2]; iX ++)
	 {
			int firstX = iX-(N-1)/2;
			int firstY = iY-(N-1)/2;
	   if (Stor!=(inpImg(iX,iY).r > 0 )) {
			 if (ntype == "Квадрат") {
			 for(int i=0;i<N*N;i++) //size_t
			  {
				xy = div(i,N);
				if ((firstY+xy.quot>=Area[1])&&(firstY+xy.quot<=Area[3]-1)&&(firstX+xy.rem >= Area[0])&&(firstX+xy.rem <= Area[2]-1)) {
				outImg(firstX+xy.rem, firstY+xy.quot).r = 255*(1-Stor);
										  }
			  }                      } else {  if (ntype != "") {
						for (int in = 0; in < npoint; in++) {
						  MorfInd (Mm, N, in, dx, dy);
						  if ((firstY+dy>=Area[1])&&(firstY+dy<=Area[3]-1)&&(firstX+dx >= Area[0])&&(firstX+dx <= Area[2]-1)) {
				outImg(firstX+dx, firstY+dy).r = 255*(1-Stor);
													}           }
						}
						  }                 }
	  }
  }
}
//-----------------------------------------------------
void MorfInd (vector<int> &Mm, int &height, int &index, unsigned short int &dmx, unsigned short int &dmy)
{
  dmy = Mm[index]/height;
  dmx = Mm[index]%height;
}
//--------------------------------------------------------
void FilterMorfM(UBitmap &inpImg, UBitmap &outImg, string ntype, bool Stor ,int N)
{
  if (N > 15) {
   ShowMessage("Недопустимый размер маски");
   return;
  }
  FillColor(outImg, "Red", 255*Stor);
  unsigned short int dx, dy, npoint;
  vector<int> Mm;
unsigned int Area[4]= {0,0,1,1};
Area[2]= inpImg.GetWidth();
Area[3]= inpImg.GetHeight();
  MorfMask (Mm, ntype, N, npoint);

		div_t xy;
  for (int iY = Area[1]; iY < Area[3]; iY ++)
  {
	for (int iX = Area[0]; iX < Area[2]; iX ++)
	 {
			int firstX = iX-(N-1)/2;
			int firstY = iY-(N-1)/2;
			bool Sum = true;
			if (ntype == "Квадрат") {
            for(int i=0;i<N*N;i++) //size_t
			  {
               xy = div(i,N);
				if ((firstY+xy.quot>Area[1])&&(firstY+xy.quot<Area[3]-1)&&(firstX+xy.rem > Area[0])&&(firstX+xy.rem < Area[2]-1)) {
				   Sum *= (Stor!=(inpImg(firstX+xy.rem, firstY+xy.quot).r > 100));
						}
			   }                   } else {  if (ntype != "") {
						for (int in = 0; in < npoint; in++) {
						  MorfInd (Mm, N, in, dx, dy);
						  if ((firstY+dy>Area[1])&&(firstY+dy<Area[3]-1)&&(firstX+dx > Area[0])&&(firstX+dx < Area[2]-1)) {
						  Sum *= (Stor!=(inpImg(firstX+dx, firstY+dy).r > 100));
											 }	  }
			   }                                              }
			  if (Sum) {
			   outImg(iX,iY).r = 255*(1-Stor);
			  }
	 }
   }
}
//-----------------------------------------------------
void MorfMask (vector<int> &Mm, string &ntype, int &h, unsigned short int &npoint)
{
  if (ntype == "Круг-3") {
	h = 3; npoint = 5;
	Mm.resize(npoint);
	Mm[0]=1;  Mm[1]=3; Mm[2]=4; Mm[3]=5; Mm[4]=7;
  }  else { if (ntype == "Круг-5") {
	h = 5; npoint = 21;
	Mm.resize(npoint);
	Mm[0]=1;  Mm[1]=2; Mm[2]=3;
	for (int im = 0; im < 15; im++) {
	Mm[im+3]=im+5;
	}
	 Mm[18]=21; Mm[19]=22; Mm[20]=23;
  }  else { if (ntype == "Круг-7") {
		  h = 7; npoint = 37;
	Mm.resize(npoint);
	Mm[0]=2;  Mm[1]=3; Mm[2]=4;
	Mm[3]=8;  Mm[4]=9; Mm[5]=10; Mm[6]=11;  Mm[7]=12;
	for (int im = 0; im < 21; im++) {
	Mm[im+8]=im+14;
	}
	Mm[29]=36;  Mm[30]=37; Mm[31]=38; Mm[32]=39;  Mm[33]=40;
	 Mm[34]=44; Mm[35]=45; Mm[36]=46;
  } else { if (ntype == "Рамка") {
	h = 3; npoint = 8;
	Mm.resize(npoint);
	Mm[0]=0;  Mm[1]=1; Mm[2]=2;
	Mm[3]=3;           Mm[4]=5;
	Mm[5]=6;  Mm[6]=7; Mm[7]=8;
  }  else { if (ntype == "Кольцо-3") {
	h = 3; npoint = 4;
	Mm.resize(npoint);
	Mm[0]=1;  Mm[1]=3; Mm[2]=5; Mm[3]=7;
  }  else { if (ntype == "Кольцо-5") {
	h = 5; npoint = 12;
	Mm.resize(npoint);
	Mm[0]=1;     Mm[1]=2;    Mm[2]=3;
	Mm[3]=5;                 Mm[4]=9;
	Mm[5]=10;                Mm[6]=14;
	Mm[7]=15;                Mm[8]=19;
	Mm[9]=21;  Mm[10]=22;  Mm[11]=23;
  }  else { if (ntype == "Кольцо-7") {
	h = 7; npoint = 16;
	Mm.resize(npoint);
	Mm[0]=2;  Mm[1]=3; Mm[2]=4;
		Mm[3]=8;          Mm[4]=12;
	Mm[5]=14;                Mm[6]=20;
	Mm[7]=21;                Mm[8]=27;
	Mm[9]=28;                Mm[10]=34;
		Mm[11]=36;        Mm[12]=40;
	Mm[13]=44; Mm[14]=45; Mm[15]=46;
  }


  }  }  }  }  }  } 
}
//-------------------------------   //*/
void FillColor (UBitmap &inpImg, string ncolor, int h)
{
unsigned int Area[4]= {0,0,1,1};
Area[2]= inpImg.GetWidth();
Area[3]= inpImg.GetHeight();
int temp;

for (int iY = Area[1]; iY < Area[3]; iY ++)
  {
	for (int iX = Area[0]; iX < Area[2]; iX ++)
	 {
	 if (ncolor == "Red") {
		inpImg(iX,iY).r = h;
		  } else { if (ncolor == "Blue") {
		inpImg(iX,iY).b = h;
		  } else { if (ncolor == "Green") {
		inpImg(iX,iY).g = h;
			} else { if (ncolor == "Move 1-2") {
		temp = inpImg(iX,iY).r;
		inpImg(iX,iY).r = inpImg(iX,iY).g;
		inpImg(iX,iY).g = temp;
			}  else { if (ncolor == "Move 1-3") {
		temp = inpImg(iX,iY).r;
		inpImg(iX,iY).r = inpImg(iX,iY).b;
		inpImg(iX,iY).b = temp;
			}  else { if (ncolor == "Move 2-3") {
		temp = inpImg(iX,iY).b;
		inpImg(iX,iY).b = inpImg(iX,iY).g;
		inpImg(iX,iY).g = temp;
			}

		}   }   }   }   }

	  }
   }
}

//-----------------------------------------------------
void MakeGrayIm (UBitmap &inpImg)
{
unsigned char temp;
for (int iY = 0; iY < inpImg.GetHeight(); iY ++)
  {
	for (int iX = 0; iX < inpImg.GetWidth(); iX ++)
	 {
	 temp = (inpImg(iX,iY).r + inpImg(iX,iY).g + inpImg(iX,iY).b)/3;
	 inpImg(iX,iY).r = inpImg(iX,iY).g = inpImg(iX,iY).b = temp;
	 }
  }

}

//------------------------------------------------------

//*/




