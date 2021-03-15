/* ************************************************************************** */
// Copyright Alexander Bakhshiev, 2005-2008.
// E-mail: alexab@ailabe.ru
/* ************************************************************************** */
#ifndef UBITMAP_CPP
#define UBITMAP_CPP

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <vector>
#include <list>
#include <memory.h>
#include <time.h>
#include "UBitmap.h"

namespace Utilities {

// ������ UBitmap
// --------------------------
// ������������ � �����������
// --------------------------
UBitmap::UBitmap(void)
{
 Width=0;
 Height=0;
 Length=0;
 Data=0;
 ColorModel=ubmColor;
}

UBitmap::UBitmap(const UBitmap &bitmap)
{
 Width=bitmap.Width;
 Height=bitmap.Height;
 Length=Width*Height;
 ColorModel=bitmap.ColorModel;
 Data=new UColorT[Width*Height];
 memcpy(Data,bitmap.Data,Length*sizeof(UColorT));
}

UBitmap::UBitmap(UBMColorModel cmodel)
{
 Width=0;
 Height=0;
 Length=0;
 Data=0;
 ColorModel=cmodel;
}

UBitmap::UBitmap(int width, int height, UColorT color,
                UBMColorModel cmodel)
{
 if(width >= 0 && height >=0)
  {
   Width=Width;
   Height=Height;
   Length=Width*Height;
   ColorModel=cmodel;
   Data=new UColorT[Length];
   Fill(color);
  }
 else
  UBitmap(cmodel);
}

UBitmap::UBitmap(int width, int height, const unsigned* data,
                UBMColorModel cmodel)
{
 if(width >= 0 && height >=0)
  {
   Width=Width;
   Height=Height;
   Length=Width*Height;
   ColorModel=cmodel;
   if(data)
    {
     Data=new UColorT[Length];
     memcpy(Data,data,Length*sizeof(UColorT));
    } 
  }
 else
  UBitmap(cmodel);  
}

UBitmap::~UBitmap(void)
{
 if(Data) delete[] Data;
 Data=0;
}
// --------------------------

// -------------------------
// ������ ���������� �������
// -------------------------
// ������ ������� ����� �����������
// ���� isupdate == true �� ������������ ����������� �������������
void UBitmap::SetColorModel(UBMColorModel cmodel, bool isupdate)
{
 if(ColorModel == cmodel)
  return;

 if(isupdate)
  {
   switch(cmodel)
   {
   case ubmColor:
    if(ColorModel == ubmMath)
     for(int i=0;i<Length;i++)
      {
       Data[i].r=Data[i].g=Data[i].b=Data[i].c;
       Data[i].d=0;
      }
   break;

   case ubmGray:
    if(ColorModel == ubmColor)
     for(int i=0;i<Length;i++)
      Data[i].r=Data[i].g=Data[i].b=
       ((unsigned)Data[i].r+(unsigned)Data[i].g+(unsigned)Data[i].b)/3;
    else
    if(ColorModel == ubmMath)
     for(int i=0;i<Length;i++)
      {
       Data[i].g=Data[i].b=Data[i].r=Data[i].c;
       Data[i].d=0;
      }
   break;

   case ubmMath:
    if(ColorModel == ubmColor)
     for(int i=0;i<Length;i++)
      {
       Data[i].c=((unsigned)Data[i].r+(unsigned)Data[i].g+(unsigned)Data[i].b)/3;
      }
    else
    if(ColorModel == ubmGray)
     for(int i=0;i<Length;i++)
      Data[i].c=Data[i].r;
   break;
   }
  }
 ColorModel=cmodel;
}

void UBitmap::SetAutoCModelConvert(bool acmodel)
{
 if(AutoCModelConvert == acmodel)
  return;

 AutoCModelConvert = acmodel;
}

// ������� ���������� �����
void UBitmap::SetRes(int width, int height)
{
 if(width < 0 || height < 0)
  return;

 if(Width != width || Height != height)
  {
   delete[] Data;
   Width=width;
   Height=height;
   Length=Width*Height;
   Data=new UColorT[Length];
  }
}

// �������� ����� ����������� �� ������ data
// � �������� ���������
void UBitmap::SetImage(const UColorT* data)
{
 memcpy(Data,data,Length*sizeof(UColorT));
}

// �������� ����� ����������� �� ������ data
// � ������ ���������
void UBitmap::SetImage(int width, int height, const UColorT* data)
{
 if(!data)
  return;

 if(Width != width || Height != height)
  {
   delete[] Data;
   Width=width;
   Height=height;
   Length=Width*Height;
   Data=new UColorT[Width*Height];
  }
 memcpy(Data,data,Length*sizeof(UColorT));
}

// ������������� ���������� ��������� �� ����� data
// �������� ������� ���������� � ��������
void UBitmap::SetPImage(UColorT* data)
{
 delete[] Data;
 Data=data;
 if(!Data)
  Width=Height=Length=0;
}

// ������������� ���������� ��������� �� ����� data
// �������� ���������� � ��������
void UBitmap::SetPImage(int width, int height, UColorT* data)
{
 Width=width;
 Height=height;
 Length=Width*Height;
 delete[] Data;
 Data=data;

 if(!Data)
  Width=Height=Length=0; 
}

// ��������� ����������� ������ color
void UBitmap::Fill(UColorT color)
{
 if(!Data || Width == 0 || Height == 0)
  return;
  
 if(color.c == 0 ||
      (color.r == color.g && color.r == color.b && color.r==color.d))
  memset(Data,color.r,Length*sizeof(UColorT));
 else
  {
   for(int i=0;i<Width;i++)
    *(Data+i)=color;

   for(int i=1;i<Height;i++)
    memcpy(Data+i*Width,Data,Width*sizeof(UColorT));
  }
}

// �������� ����������� � 'target' � �������,
// ������������ ��� x,y
// ���� ����������� �� ��������� �������, �� ��� ���������
// ����������� ������ ������������� � �������� ������ ���� 'target'
void UBitmap::CopyTo(int x, int y, UBitmap &target)
{
 int xsize,ysize;
 UColorT *data,*tardata;

 if(x < 0 || y < 0 || x >= target.Width || y >= target.Height)
  return;

 xsize=(Width<target.Width-x)?Width:target.Width-x;
 ysize=(Height<target.Height-y)?Height:target.Height-y;

 if(ColorModel == target.ColorModel ||
    (ColorModel == ubmGray && target.ColorModel == ubmColor))
  for(int j=0;j<ysize;j++)
   memcpy(target.Data+(j+y)*target.Width+x,Data+j*Width,xsize*sizeof(UColorT));
 else
  {
   switch(target.ColorModel)
    {
     case ubmColor:
      if(ColorModel == ubmMath)
       {
        for(int j=0;j<ysize;j++)
         {
          data=Data+j*Width;
          tardata=target.Data+(j+y)*target.Width+x;
          for(int i=0;i<xsize;i++)
           (tardata+i)->r=(tardata+i)->g=(tardata+i)->b=(data+i)->b;
         }
       }
     break;

     case ubmGray:
      if(ColorModel == ubmColor)
	   {
        for(int j=0;j<ysize;j++)
         {
          data=Data+j*Width;
          tardata=target.Data+(j+y)*target.Width+x;
          for(int i=0;i<xsize;i++)
           (tardata+i)->r=(tardata+i)->g=(tardata+i)->b=
          ((unsigned)(data+i)->r+(unsigned)(data+i)->g+(unsigned)(data+i)->b)/3;
         }
       }
      else
      if(ColorModel == ubmMath)
       {
        for(int j=0;j<ysize;j++)
         {
          data=Data+j*Width;
          tardata=target.Data+(j+y)*target.Width+x;
          for(int i=0;i<xsize;i++)
           (tardata+i)->r=(tardata+i)->g=(tardata+i)->b=(data+i)->b;
         }
       }
     break;

     case ubmMath:
      if(ColorModel == ubmColor)
       {
        for(int j=0;j<ysize;j++)
         {
          data=Data+j*Width;
          tardata=target.Data+(j+y)*target.Width+x;
          for(int i=0;i<xsize;i++)
           {
            (tardata+i)->b=
             ((unsigned)(data+i)->r+(unsigned)(data+i)->g+(unsigned)(data+i)->b)/3;
            (tardata+i)->g=(tardata+i)->r=(tardata+i)->d=0;
           }
         }
       }
      else
      if(ColorModel == ubmGray)
	   {
        for(int j=0;j<ysize;j++)
         {
          data=Data+j*Width;
          tardata=target.Data+(j+y)*target.Width+x;
          for(int i=0;i<xsize;i++)
           {
            (tardata+i)->b=(data+i)->b;
            (tardata+i)->g=(tardata+i)->r=(tardata+i)->d=0;
           }
         }
       }
     break;
     }
  }
}

// �������� ����������� � 'target' � �������,
// ������������ ��� x,y
// ���� ����������� �� ��������� �������, �� ��� ���������
// ����������� ������ ������������� � �������� ������ ���� 'target'
// �������� ����������� ��������� � ������ 'transp' �� �����������
// (������ ������������)
void UBitmap::CopyTo(int x, int y, UBitmap &target, UColorT transp)
{
 int xsize,ysize;
 UColorT *data,*tardata;

 if(x < 0 || y < 0 || x >= target.Width || y >= target.Height)
  return;

 xsize=(Width<target.Width-x)?Width:target.Width-x;
 ysize=(Height<target.Height-y)?Height:target.Height-y;

 if(ColorModel == target.ColorModel ||
    (ColorModel == ubmGray && target.ColorModel == ubmColor))
  for(int j=0;j<ysize;j++)
   {
    tardata=target.Data+(j+y)*target.Width+x;
    data=Data+j*Width;
	for(int k=0;k<xsize;k++,tardata++,data++)
     if(data->c != transp.c)
      tardata->c=data->c;
   }
 else
  {
   switch(target.ColorModel)
    {
     case ubmColor:
      if(ColorModel == ubmMath)
       {
        for(int j=0;j<ysize;j++)
         {
          data=Data+j*Width;
          tardata=target.Data+(j+y)*target.Width+x;
          for(int i=0;i<xsize;i++)
           if((data+i)->c != transp.c)
            (tardata+i)->r=(tardata+i)->g=(tardata+i)->b=(data+i)->b;
         }
       }
     break;

     case ubmGray:
      if(ColorModel == ubmColor)
       {
        for(int j=0;j<ysize;j++)
         {
          data=Data+j*Width;
          tardata=target.Data+(j+y)*target.Width+x;
          for(int i=0;i<xsize;i++)
           if((data+i)->c != transp.c)
           (tardata+i)->r=(tardata+i)->g=(tardata+i)->b=
            ((unsigned)(data+i)->r+(unsigned)(data+i)->g+(unsigned)(data+i)->b)/3;
         }
       }
      else
      if(ColorModel == ubmMath)
       {
        for(int j=0;j<ysize;j++)
         {
		  data=Data+j*Width;
          tardata=target.Data+(j+y)*target.Width+x;
          for(int i=0;i<xsize;i++)
           if((data+i)->c != transp.c)
            (tardata+i)->r=(tardata+i)->g=(tardata+i)->b=(data+i)->b;
         }
       }
     break;

     case ubmMath:
      if(ColorModel == ubmColor)
       {
        for(int j=0;j<ysize;j++)
         {
          data=Data+j*Width;
          tardata=target.Data+(j+y)*target.Width+x;
          for(int i=0;i<xsize;i++)
           if((data+i)->c != transp.c)
            {
             (tardata+i)->b=
              ((unsigned)(data+i)->r+(unsigned)(data+i)->g+(unsigned)(data+i)->b)/3;
             (tardata+i)->g=(tardata+i)->r=(tardata+i)->d=0;
            }
         }
       }
      else
      if(ColorModel == ubmGray)
       {
        for(int j=0;j<ysize;j++)
         {
          data=Data+j*Width;
          tardata=target.Data+(j+y)*target.Width+x;
          for(int i=0;i<xsize;i++)
           if((data+i)->c != transp.c)
            {
             (tardata+i)->b=(data+i)->b;
             (tardata+i)->g=(tardata+i)->r=(tardata+i)->d=0;
            }
         }
       }
	 break;
     }
  }
}

// ���������� ������� ����������� � ������������
// ������ �������� ���� x,y � ������� � ������
// ��������������� �������� 'target'
bool UBitmap::GetRect(int x, int y, UBitmap &target)
{
 int width,height;
 bool res=true;
 UBMColorModel cmodel=target.ColorModel;

 width=(target.Width > Width)?Width:target.Width;
 height=(target.Height > Height)?Height:target.Height;
 target.SetRes(width,height);
 target.SetColorModel(ColorModel,false);

 if(x < 0)
  { x=0; res=false; }

 if(y < 0)
  { y=0; res=false; }

 if(target.Width > Width-x)
  { x=Width-target.Width; res=false; }

 if(target.Height > Height-y)
  { y=Height-target.Height; res=false; }


 for(int i=0;i<target.Height;i++)
  memcpy(target.Data+i*target.Width, Data+(y+i)*Width+x,
         target.Width*sizeof(UColorT));

 if(AutoCModelConvert)
  target.SetColorModel(cmodel);         

 return res;
}


// ��������� ������� ����������� �� RGB �������� ������
// ������ ����������� � ������������ � �������� ������� 'cmodel'
// �������� ������ ����������� �������������� ubmColor
void UBitmap::Separate(UBitmap &red, UBitmap &green, UBitmap &blue,
              UBMColorModel cmodel)
{
 red.SetColorModel(cmodel,false);
 green.SetColorModel(cmodel,false);
 blue.SetColorModel(cmodel,false);

 red.SetRes(Width,Height);
 green.SetRes(Width,Height);
 blue.SetRes(Width,Height);

 if(cmodel == ubmColor || cmodel == ubmGray)
  {
   for(int i=0;i<Length;i++)
    {
     (red.Data+i)->r=(red.Data+i)->g=(red.Data+i)->b=(Data+i)->r;
     (green.Data+i)->r=(green.Data+i)->g=(green.Data+i)->b=(Data+i)->g;
     (blue.Data+i)->r=(blue.Data+i)->g=(blue.Data+i)->b=(Data+i)->b;
    }
  }
 else
  {
   red.Fill(0);
   green.Fill(0);
   blue.Fill(0);
   for(int i=0;i<Length;i++)
    {
     (red.Data+i)->r=(Data+i)->r;
     (green.Data+i)->r=(Data+i)->g;
     (blue.Data+i)->r=(Data+i)->b;
    }
  }
}
// -------------------------


// -------------------------
// ������ ����� ����������
// -------------------------
// ���������� ����������� � ������������ �������� ��������
void UBitmap::FindColorRange(UColorT &minval, UColorT &maxval)
{
 minval.c=maxval.c=0;

 switch(ColorModel)
 {
  case ubmColor:
   for(int i=0;i<Length;i++)
    {
     if(minval.r > (Data+i)->r)
      minval.r=(Data+i)->r;

     if(minval.g > (Data+i)->g)
      minval.g=(Data+i)->g;

     if(minval.b > (Data+i)->b)
      minval.b=(Data+i)->b;

     if(maxval.r < (Data+i)->r)
      maxval.r=(Data+i)->r;

     if(maxval.g < (Data+i)->g)
      maxval.g=(Data+i)->g;

     if(maxval.b < (Data+i)->b)
      maxval.b=(Data+i)->b;
    }
  break;

  case ubmGray:
   for(int i=0;i<Length;i++)
    {
     if(minval.r > (Data+i)->r)
      minval.r=(Data+i)->r;

     if(maxval.r < (Data+i)->r)
      maxval.r=(Data+i)->r;
    }
  break;

  case ubmMath:
   for(int i=0;i<Length;i++)
    {
     if(minval.c > (Data+i)->c)
      minval.c=(Data+i)->c;

     if(maxval.c < (Data+i)->c)
      maxval.c=(Data+i)->c;
    }
  break;
 }
}

// ��������� ���������������� ����� �������� ���� ������� ������� �����������
// ���� 'width' ��� 'height' < 0 ��� ��������� ��������
// �� ������� ������� ����������� �� ����� �����������
UColorT UBitmap::FindAverageColor(int x, int y, int width,int height)
{
 UColorT result=0;
 unsigned r=0,g=0,b=0;
 UColorT *data=0;    
 int length;

 if(x < 0) x=0;
 if(y < 0) y=0;
 if(width < 0)
  width=Width;
 if(height < 0)
  height=Height;
 if(x+width >= Width)
  width=Width-x;
 if(y+height >= Height)
  height=Height-y;
            
 length=width*height;
 switch(ColorModel)
 {
  case ubmColor:
   for(int j=y;j<height;j++)
    {
     data=Data+j*Width+x;
     for(int i=0;i<width;i++)
      {
       r+=data->r;
       g+=data->g;
       b+=data->b;
          ++data;
      }
    }

   result.r=r/length;
   result.g=g/length;
   result.b=b/length;
  break;

  case ubmGray:
   for(int j=y;j<height;j++)
    {
     data=Data+j*Width+x;
     for(int i=0;i<width;i++)
      {
       r+=data->r;
       ++data;
      }
    }

   result.r=result.g=result.b=r/length;
  break;

  case ubmMath:
   for(int j=y;j<height;j++)
    {
     data=Data+j*Width+x;
     for(int i=0;i<width;i++)
	  {
       result.c+=data->c;
       ++data;
      }
    }

   result.c/=length;
  break;
 }

 return result;
}

// ��������� ��������� ������� �� ������ ����������� � ������� y
unsigned int UBitmap::CalcBrightnessByRow(int y)
{
 unsigned int res=0;

 if(!Length || !Data || y<0 || y>=Height)
  return 0;

 switch(ColorModel)
 {
 case ubmColor:
  for(int i=0;i<Width;i++)
   res+=(Data[y*Width+i].b+Data[y*Width+i].g+Data[y*Width+i].r)/3;
 break;

 case ubmGray:
  for(int i=0;i<Width;i++)
   res+=Data[y*Width+i].b;
 break;

 case ubmMath:
  for(int i=0;i<Width;i++)
   res+=Data[y*Width+i].c;
 break;
 }

 return res;
}

// ��������� ��������� ������� �� ������� ����������� � ������� x
unsigned int UBitmap::CalcBrightnessByCol(int x)
{
 unsigned int res=0;

 if(!Length || !Data || x<0 || x>=Height)
  return 0;

 switch(ColorModel)
 {
 case ubmColor:
  for(int i=0;i<Height;i++)
   res+=(Data[i*Width+x].b+Data[i*Width+x].g+Data[i*Width+x].r)/3;
 break;

 case ubmGray:
  for(int i=0;i<Height;i++)
   res+=Data[i*Width+x].b;
 break;

 case ubmMath:
  for(int i=0;i<Height;i++)
   res+=Data[i*Width+x].c;
 break;
 }

 return res;
}

// ��������� ��������� ������� ��������� �� �������� � �������� ����������� �� 
// ������� x1 �� x2, � �� ������ y1 �� y2. 
// � x_result �������� ��������, � y_result - �����, ������ ������ ���� ��������
void UBitmap::Histogram(unsigned *x_result, unsigned *y_result, 
                                   int x1, int x2, int y1, int y2)
{                                                            
 if(!Length || !Data || !x_result || !y_result)
  return;
 
 if(x1<0 || x1>=Width)
  x1=0;

 if(x2<0 || x2>=Width)
  x2=Width-1;

 if(y1<0 || y1>=Height)
  y1=0;

 if(y2<0 || y2>=Height)
  y2=Height-1;
  
 int temp;
 if(x1>x2)
 {
  temp=x1;
  x1=x2;
  x2=temp;
 }
 if(y1>y2)
 {
  temp=y1;
  y1=y2;
  y2=temp;
 }


 memset(x_result,0,(x2-x1+1)*sizeof(unsigned));
 memset(y_result,0,(y2-y1+1)*sizeof(unsigned));
 UColorT *p=Data+y1*Width+x1;

 switch(ColorModel)
 {
 case ubmColor:
  for(int j=y1,k=0;j<=y2;j++,k++)
  {
   for(int i=x1,l=0;i<=x2;i++,l++)
   {
	y_result[k]+=(p->b+p->g+p->r)/3;
	x_result[l]+=(p->b+p->g+p->r)/3;
	++p;
   }
   p+=Width-x2+x1;
  }
 break;

 case ubmGray:
  for(int j=y1,k=0;j<=y2;j++,k++)
  {
   for(int i=x1,l=0;i<=x2;i++,l++)
   {
	y_result[k]+=(*this)(i,j).b;//p->b;
	x_result[l]+=(*this)(i,j).b;//p->b;
	++p;
   }
   p+=Width-x2+x1;
  }
 break;

 case ubmMath:
  for(int j=y1,k=0;j<=y2;j++,k++)
  {
   for(int i=x1,l=0;i<=x2;i++,l++)
   {
	y_result[k]+=(*this)(i,j).c;//p->c;
	x_result[l]+=(*this)(i,j).c;//p->c;
	++p;
   }
   p+=Width-x2+x1;
  }
 break;
 } 
}                     

                                   
// ��������� ������������� ��������� ������������� ��������� �� �������� � 
// �������� ����������� �� ������� x1 �� x2, � �� ������ y1 �� y2. 
// ������������� ��������� ��������� �� ������� � ����������� �� �������� ������
// � x_result �������� ��������, � y_result - �����, ������ ������ ���� ��������
void UBitmap::Histogram(UColorT *x_result, UColorT *y_result, 
								   int x1, int x2, int y1, int y2)
{
 if(!Length || !Data || !x_result || !y_result)
  return;
 
 if(x1<0 || x1>=Width)
  x1=0;

 if(x2<0 || x2>=Width)
  x2=Width-1;

 if(y1<0 || y1>=Height)
  y1=0;

 if(y2<0 || y2>=Height)
  y2=Height-1;
  
 int temp;
 if(x1>x2)
 {
  temp=x1;
  x1=x2;
  x2=temp;
 }
 if(y1>y2)
 {
  temp=y1;
  y1=y2;
  y2=temp;
 }
        
 UColorT *p=Data+y1*Width+x1;

 // ��������� ������ ��� �������� �����������
 unsigned* x_buf[3]={0,0,0};
 unsigned* y_buf[3]={0,0,0};
 

 switch(ColorModel)
 {
 case ubmColor:
  for(int i=0;i<3;i++)            
  {
   x_buf[i]=new unsigned[x2-x1+1];
   memset(x_buf,0,(x2-x1+1)*sizeof(unsigned));
  }

  for(int i=0;i<3;i++)
  {
   y_buf[i]=new unsigned[y2-y1+1];
   memset(y_buf,0,(y2-y1+1)*sizeof(unsigned));
  }

  for(int j=y1,k=0;j<=y2;j++,k++)
  {         
   for(int i=x1,l=0;i<=x2;i++,l++)
   {
    y_buf[0][k]+=p->b;
    y_buf[1][k]+=p->g;
    y_buf[2][k]+=p->r;
    x_buf[0][l]+=p->b;
    x_buf[1][l]+=p->g;
    x_buf[2][l]+=p->r;
    ++p;
   }    
   p+=Width-x2+x1;
  }

  for(int i=0;i<=x2-x1;i++)
  {
   x_result[i].b=x_buf[0][i]/(y2-y1+1);
   x_result[i].g=x_buf[1][i]/(y2-y1+1);
   x_result[i].r=x_buf[2][i]/(y2-y1+1);
  }

  for(int i=0;i<=y2-y1;i++)
  {
   y_result[i].b=y_buf[0][i]/(x2-x1+1);
   y_result[i].g=y_buf[1][i]/(x2-x1+1);
   y_result[i].r=y_buf[2][i]/(x2-x1+1);
  }

  for(int i=0;i<3;i++)
   delete []x_buf[i];

  for(int i=0;i<3;i++)
   delete []y_buf[i];
 break;

 case ubmGray:
  memset(x_result,0,(x2-x1+1)*sizeof(unsigned));
  memset(y_result,0,(y2-y1+1)*sizeof(unsigned));
  for(int j=y1,k=0;j<=y2;j++,k++)
  {
   for(int i=x1,l=0;i<=x2;i++,l++)
   {
    y_result[k].c+=p->b;
    x_result[l].c+=p->b;
    ++p;
   }
   p+=Width-x2+x1;
  }

  for(int i=0;i<=x2-x1;i++)
   x_result[i].r=x_result[i].g=x_result[i].b=x_result[i].c/(y2-y1+1);

  for(int i=0;i<=y2-y1;i++)
   y_result[i].r=y_result[i].g=y_result[i].b=y_result[i].c/(x2-x1+1);
 break;

 case ubmMath:
  memset(x_result,0,(x2-x1+1)*sizeof(unsigned));
  memset(y_result,0,(y2-y1+1)*sizeof(unsigned));
  for(int j=y1,k=0;j<=y2;j++,k++)
  {
   for(int i=x1,l=0;i<=x2;i++,l++)
   {
    y_result[k].c+=p->c;
    x_result[l].c+=p->c;
    ++p;
   }
   p+=Width-x2+x1;
  }                   

  for(int i=0;i<=x2-x1;i++)
   x_result[i].c/=(y2-y1+1);

  for(int i=0;i<=y2-y1;i++)
   y_result[i].c/=(x2-x1+1);
 break;
 }
}
// -------------------------

// -------------------------
// ������ ��������� �����������
// -------------------------
// ��������� �� ���������
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
// � �������� ������ 'target' ���������� ������� ���������
void UBitmap::ReflectionX(UBitmap *target)
{
 int i;
 UColorT *buf; // �������� ������
 UColorT *beg, *fin; // ��������� �� ������ � ����� �����������

 if(target)
 {
  target->SetRes(Width,Height);
  target->SetColorModel(ColorModel,false);
  beg=Data;
  fin=target->GetData()+Length-Width;
  for(i=0; i<Height; i++)
  {
   memcpy(fin,beg,Width*sizeof(UColorT));
   beg+=Width;
   fin-=Width;
  }
 }
 else
 {
  buf=new UColorT[Width];
  beg=Data;
  fin=Data+Length-Width;
  for(i=0; i<(Height>>1); i++)
  {
   memcpy(buf,beg,Width*sizeof(UColorT));
   memcpy(beg,fin,Width*sizeof(UColorT));
   memcpy(fin,buf,Width*sizeof(UColorT));
   beg+=Width;
   fin-=Width;
  }
  delete []buf;
 }
}

// �������� ����������� � ��������� ������� �� 'pixels' ��������
// ����������� ������������ 'direction'
// 1 - Up
// 2 - Down
// 3 - Left
// 4 - Right
// ��� ���� ��������� 'direction' ��� ������������� ��������� pixels
// ����� �� ������ ������
// ������ ����� ����������� ������ 'color'
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
void UBitmap::Move(int pixels, int direction, UColorT color, UBitmap *target)
{
 UColorT *pout;
 UBMColorModel cmodel=(target)?target->ColorModel:ColorModel;

 if(direction < 1 || direction > 4 || pixels <= 0)
  return;

 if(!Length)
  return;

 if(!target)
  pout=Data;
 else
  {
   target->SetRes(Width,Height);
   target->SetColorModel(ColorModel,false);
   pout=target->Data;
  }

 switch(direction)
  {
/*  case ubmUp:
   if(pixels > Height)
    {
     if(!target)
      Fill(color);
     else
      {
       target->Fill(color);

       if(AutoCModelConvert)
        target->SetColorModel(cmodel);
      }

     return;
    }

   if(!target)
    memmove(pout,Data+Width*pixels,(Length-Width*pixels)*sizeof(UColorT));
   else
    memcpy(pout,Data+Width*pixels,(Length-Width*pixels)*sizeof(UColorT));


   for(int i=0;i<Width;i++)
    (pout+Length-Width*pixels+i)->c=color.c;
   for(int i=1;i<pixels-1;i++)
    memcpy(pout+Length-Width*(pixels+i),pout+Length-Width*pixels,Width*sizeof(UColorT));
  break;         */
  
case ubmUp:
   if(pixels > Height)
    {
     if(!target)
	  Fill(color);
     else
      {
       target->Fill(color);

//       if(AutoCModelConvert)
//        target->SetColorModel(cmodel);
      }

     return;
    }

   if(!target)
    memmove(pout,Data+Width*pixels,(Length-Width*pixels)*sizeof(UColorT));
   else
    memcpy(pout,Data+Width*pixels,(Length-Width*pixels)*sizeof(UColorT));


   for(int i=0;i<Width;i++)
    (pout+Length-Width*pixels+i)->c=color.c;
   for(int i=1;i<pixels;i++)
    memcpy(pout+Length-Width*(pixels-i),pout+Length-Width*pixels,Width*sizeof(UColorT));
  break;

  case ubmDown:
   if(pixels > Height)
    {
     if(!target)
      Fill(color);
     else
      {
       target->Fill(color);

//       if(AutoCModelConvert)
//        target->SetColorModel(cmodel);
      }

     return;
    }

   if(!target)
    memmove(pout+Width*pixels,Data,(Length-Width*pixels)*sizeof(UColorT));
   else
    memcpy(pout+Width*pixels,Data,(Length-Width*pixels)*sizeof(UColorT));

   for(int i=0;i<Width;i++)
    (pout+i)->c=color.c;
   for(int i=1;i<pixels;i++)
    memcpy(pout+i*Width,pout,Width*sizeof(UColorT));
  break;
  /*
  case ubmDown:
   if(pixels > Height)
    {
     if(!target)
      Fill(color);
     else
      {
       target->Fill(color);

       if(AutoCModelConvert)
        target->SetColorModel(cmodel);
      }

     return;
    }

   if(!target)
    memmove(pout+Width*pixels,Data,(Length-Width*pixels)*sizeof(UColorT));
   else
    memcpy(pout+Width*pixels,Data,(Length-Width*pixels)*sizeof(UColorT));

   for(int i=0;i<Width;i++)
    (pout+i)->c=color.c;
   for(int i=1;i<pixels-1;i++)
    memcpy(pout+i*Width,pout,Width*sizeof(UColorT));
  break;  */

  case ubmLeft:
   if(pixels > Width)
	{
     if(!target)
      Fill(color);
     else
      {
       target->Fill(color);

       if(AutoCModelConvert)
        target->SetColorModel(cmodel,false);
      }

     return;
    }

   for(int i=0;i<Height;i++)
    if(!target)
     memmove(pout+i*Width,Data+i*Width+pixels,(Width-pixels)*sizeof(UColorT));
    else
     memcpy(pout+i*Width,Data+i*Width+pixels,(Width-pixels)*sizeof(UColorT));

   for(int j=0;j<pixels;j++)
    (pout+Width-pixels+j)->c=color.c;
   for(int i=1;i<Height;i++)
    memcpy(pout+i*Width+Width-pixels,pout+Width-pixels,pixels*sizeof(UColorT));
  break;

  case ubmRight:
   if(pixels > Width)
    {
     if(!target)
      Fill(color);
     else
      {
       target->Fill(color);

       if(AutoCModelConvert)
        target->SetColorModel(cmodel);
      }
     return;
    }

   for(int i=0;i<Height;i++)
    if(!target)
     memmove(pout+i*Width+pixels,Data+i*Width,(Width-pixels)*sizeof(UColorT));
    else
     memcpy(pout+i*Width+pixels,Data+i*Width,(Width-pixels)*sizeof(UColorT));

   for(int j=0;j<pixels;j++)
    (pout+j)->c=color.c;
   for(int i=1;i<Height;i++)
    memcpy(pout+i*Width,pout,pixels*sizeof(UColorT));
  break;
  }

 if(target && AutoCModelConvert)
  target->SetColorModel(cmodel);
}

// �������� ����������� �� 'x' �������� �� ��� ������� � �� 'y'
// �������� �� ��� �������
// ������������� �������� �������� ����� ������ � ����
// ������������� - ����� � �����
// ������ ����� ����������� ������ 'color'
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
void UBitmap::MoveXY(int x, int y, UColorT color, UBitmap *target)
{
 if(x > 0)
  Move(x,ubmRight,color,target);
 else
  Move(-x,ubmLeft,color,target);

 if(y > 0)
  Move(y,ubmDown,color,target);
 else
  Move(-y,ubmUp,color,target);
}

// �������� ������ �����, �������� ���������� �����������
// ���� ����������� �� ���������� ������� � ����� �����,
// �� ��� ���������
// ��������� ����� ����������� ������ 'color'
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
void UBitmap::ResizeCanvas(int top, int left, int right, int bottom,
                            UColorT color, UBitmap *target)
{
 UColorT *out=0,*pout;
 UColorT *line;
 int i,j;
 UBMColorModel cmodel=(target)?target->ColorModel:ColorModel;

 // ���������� ���������� ����� ��������� �����������
 int live_left, live_top, live_width, live_height;

 // ���������� ������ ��������� ����������� � ����� �����
 int start_left, start_top;

 // ����� ���������� �����������
 int nWidth,nHeight;

 if(!top && !left && !right && !bottom)
  {
   if(target)
   {
    *target=*this;
    if(AutoCModelConvert)
     target->SetColorModel(cmodel);
   }
   else
    return;
  }

 nWidth=Width+left+right;
 nHeight=Height+top+bottom;

 if(nHeight <= 0)
  nHeight=0;

 if(nWidth <= 0)
  nWidth=0;

 if(!target)
  {
   if(!nWidth || !nHeight)
    {
     SetRes(nWidth,nHeight);
     return;
    }
  }
 else
  {
   target->SetColorModel(ColorModel,false);
   target->SetRes(nWidth,nHeight);

   if(!nWidth || !nHeight)
    {
     if(AutoCModelConvert)
      target->SetColorModel(cmodel,false);

     return;
    }
  }

  // ��������� ���������� ������� ��������� �����������
 live_left=(left>0)?0:-left;
 live_top=(top>0)?0:-top;
 live_width=Width-live_left-((right>0)?0:-right);
 live_height=Height-live_top-((bottom>0)?0:-bottom);

 // ��������� ���������� ������ ��������� ����������� � ����� �����
 start_left=(left>0)?left:0;
 start_top=(top>0)?top:0;


 // ���������� �������� �����
 if(target)
  {
   target->SetRes(nWidth,nHeight);
   out=target->Data;
  }
 else
  out=new UColorT[nWidth*nHeight];
 pout=out;

 // �������� ���������� ������
 line=new UColorT[nWidth];
 for(i=0;i<nWidth;i++)
  line[i]=color;

 // ���������� ������� �������
 for(j=0;j<start_top;j++)
  {
   memcpy(pout,line,nWidth*sizeof(UColorT));
   pout+=nWidth;
  }

 // ������� ������� ��������� ����������� � ����� �����
 j=start_top;
 for(i=live_top;i<live_top+live_height;i++,j++)
 {
  memcpy(pout,line,start_left*sizeof(UColorT));// ���������� ������
  memcpy(pout+start_left,Data+i*Width+live_left,live_width*sizeof(UColorT));
  memcpy(pout+start_left+live_width, // ���������� ������
                line,(nWidth-live_width-start_left)*sizeof(UColorT));
  pout+=nWidth;
 }

 for(j=start_top+live_height;j<nHeight;j++)
  {
   memcpy(pout,line,nWidth*sizeof(UColorT));
   pout+=nWidth;
  }

 delete []line;
 if(!target)
  {
   delete []Data;
   Data=out;
   Width=nWidth;
   Height=nHeight;
   Length=Width*Height;
  }
 else
  {
   if(AutoCModelConvert)
    target->SetColorModel(cmodel);
  }
}

// �������� ������ ����������� � �������� �������������
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
void UBitmap::Resize(int width, int height, UBMResizeMethod resizemethod,
                    UBitmap *target)
{
 UColorT *out=0;
 UBMColorModel cmodel=(target)?target->ColorModel:ColorModel;

 if(width < 0 || height < 0)
  return;

 if(target)
  {
   if(Width == width && Height == height)
    {
     (*target)=*this;
     if(AutoCModelConvert)
      target->SetColorModel(cmodel);
     return;
    }

   target->SetColorModel(ColorModel,false);

   if(Width == 0 || Height == 0 || width == 0 || height == 0)
    {
     target->SetRes(width,height);
     return;
	}

   target->SetRes(width,height);

   switch(resizemethod)
   {
    case ubmConst:
     ResizeConst(target->Data, Data, Width, Height, width, height);
    break;

    case ubmLinear:
     ResizeLinear(target->Data, Data, Width, Height, width, height);
    break;

	case ubmNolinear:
	 ResizeNolinear(target->Data, Data, Width, Height, width, height);
	break;
   }

  if(AutoCModelConvert)
   target->SetColorModel(cmodel);
  }
 else
  {
   if(Width == width && Height == height)
	return;

   if(Width == 0 || Height == 0 || width == 0 || height == 0)
	{
	 SetRes(width,height);
	 return;
	}

   out= new UColorT[width*height];
   switch(resizemethod)
   {
	case ubmConst:
	 ResizeConst(out, Data, Width, Height, width, height);
	break;

	case ubmLinear:
	 ResizeLinear(out, Data, Width, Height, width, height);
	break;

	case ubmNolinear:
	 ResizeNolinear(out, Data, Width, Height, width, height);
	break;
   }

   delete []Data;
   Data=out;
   Width=width;
   Height=height;
   Length=Width*Height;
  }
}

// ��������� �������������� ������ �������� 'thickness'
// ������� � ������� � ������� y-�����������
void UBitmap::InsertHorLine(int y, int thickness, UColorT color, UBitmap *target)
{
// int *pWidth,*pHeight,*pLength;
// UBMColorModel* pColorModel;
// UColorT *out;
 UBMColorModel cmodel;

 if(thickness < 0 || y < 0 || y >= Height)
  return;

 if(target)
  {
   cmodel=target->ColorModel;
   target->SetColorModel(ColorModel,false);
   target->SetRes(Width,Height+thickness);
   memcpy(target->Data,Data,y*Width*sizeof(UColorT));
   memcpy(target->Data+(y+thickness)*Width,Data+y*Width,(Height-y)*Width*sizeof(UColorT));

   if(color == 0 || color == 0xFFFFFFFF)
    memset(target->Data+y*Width, color.c, thickness*Width*sizeof(UColorT));
   else
    {
     UColorT *p=target->Data+y*Width;
     for(int i=0;i<thickness*Width;i++,p++)
      *p=color;
    }

   if(AutoCModelConvert)
    target->SetColorModel(cmodel);
  }
 else
  {
   Data=(UColorT*)realloc(Data,(Width*(Height+thickness))*sizeof(UColorT));

   memmove(Data+(y+thickness)*Width, Data+y*Width, (Height-y)*Width*sizeof(UColorT));
   if(color == 0 || color == 0xFFFFFFFF)
    memset(Data+y*Width, color.c, thickness*Width*sizeof(UColorT));
   else
    {
     UColorT *p=Data+y*Width;
     for(int i=0;i<thickness*Width;i++,p++)
      *p=color;
    }

   Height+=thickness;
   Length=Width*Height;
  } 
}

// ������� �������������� ������ �������� 'thickness'
// ������� � ������� � ������� y-�����������
void UBitmap::RemoveHorLine(int y, int thickness, UBitmap *target)
{
// int *pWidth,*pHeight,*pLength;
// int length;
// UBMColorModel* pColorModel;
// UColorT *out;
 UBMColorModel cmodel;

 if(thickness < 0 || y < 0 || y >= Height || Height-thickness<0)
  return;

 if(y+thickness >= Height)
  thickness=Height-y;

 if(target)
  {
   if(Height-thickness == 0)
    {
     target->SetRes(Width,0);
     return;
    }

   cmodel=target->ColorModel;
   target->SetColorModel(ColorModel,false);
   target->SetRes(Width,Height-thickness);
   memcpy(target->Data,Data,y*Width*sizeof(UColorT));
   memcpy(target->Data+y*Width,Data+(y+thickness)*Width,(Height-y-thickness)*Width*sizeof(UColorT));

   if(AutoCModelConvert)
    target->SetColorModel(cmodel);
  }
 else
  {
   if(Height-thickness == 0)
    {
     SetRes(Width,0);
     return;
    }
    
   memmove(Data+y*Width, Data+(y+thickness)*Width, (Height-y-thickness)*Width*sizeof(UColorT));
   Data=(UColorT*)realloc(Data,(Width*(Height-thickness))*sizeof(UColorT));

   Height-=thickness;
   Length=Width*Height;
  } 
}

// ��������� ������������ ������ �������� 'thickness'
// ������� � ������� � ����� x-�����������
void UBitmap::InsertVertLine(int x, int thickness, UColorT color, UBitmap *target)
{
 int width,height;
// int length;
 UColorT *p, *pend, *p2, *out;
 UBMColorModel cmodel;

 if(thickness < 0 || x < 0 || x >= Width)
  return;

 if(target)
  {
   cmodel=target->ColorModel;
   target->SetColorModel(ColorModel,false);
   target->SetRes(Width+thickness,Height);

   p=Data; pend=Data+Length;
   p2=target->Data;
   for(;p<pend;p+=Width,p2+=Width+thickness)
    {
     memcpy(p2,p,x*sizeof(UColorT));
     memcpy(p2+x+thickness,p+x,(Width-x)*sizeof(UColorT));
    }

   p=p2=target->Data+x;
   width=target->Width;
   height=target->Height;
  }
 else
  {
   out=p2=new UColorT[(Width+thickness)*Height];
   p=Data; pend=Data+Length;
   for(;p<pend;p+=Width,p2+=Width+thickness)
    {
     memcpy(p2,p,x*sizeof(UColorT));
     memcpy(p2+x+thickness,p+x,(Width-x)*sizeof(UColorT));
    }
   delete []Data;
   Data=out;

   Width+=thickness;
   Length=Width*Height;

   width=Width;
   height=Height;
   p=p2=Data+x;
  }

 // ��������� ������ ������
 if(color == 0 || color == 0xFFFFFFFF)
  {
   for(int i=0;i<height;i++,p+=width)
    memset(p, color.c, thickness*sizeof(UColorT));
  }
 else
  {
   for(int j=0;j<thickness;j++,p++)
    *p=color;

   p=p2;
   p2+=width;
   for(int i=1;i<height;i++,p2+=width)
   memcpy(p2, p, thickness*sizeof(UColorT));
  }

 if(target && AutoCModelConvert)
  target->SetColorModel(cmodel);
}

// ������� ������������ ������ �������� 'thickness'
// ������� � ������� � ����� x-�����������
void UBitmap::RemoveVertLine(int x, int thickness, UBitmap *target)
{
// int *pWidth,*pHeight,*pLength;
// int length;
// UBMColorModel* pColorModel;
 UColorT *p, *pend, *p2;
 UBMColorModel cmodel;

 if(thickness < 0 || x < 0 || x >= Width || Width-thickness<0)
  return;

 if(x+thickness >= Width)
  thickness=Width-x;

 if(target)
  {
   cmodel=target->ColorModel;
   target->SetColorModel(ColorModel,false);
   target->SetRes(Width-thickness,Height);

   p=Data; pend=Data+Width*Height;
   p2=target->Data;
   for(;p<pend;p+=Width,p2+=Width-thickness)
    {
     memcpy(p2,p,x*sizeof(UColorT));
     memcpy(p2+x,p+x+thickness,(Width-x-thickness)*sizeof(UColorT));
    }

   if(AutoCModelConvert)
    target->SetColorModel(cmodel);
  }
 else
  {
   p=p2=Data+x; pend=Data+Width*Height; 
   for(;p<pend;p+=Width-thickness,p2+=Width)
    memmove(p,p2,(Width-thickness)*sizeof(UColorT));

   Data=(UColorT*)realloc(Data,((Width-thickness)*Height)*sizeof(UColorT));

   Width-=thickness;
   Length=Width*Height;
  }
}

// ����������������. ���������� �������� �������� ������� � ������� 0 - 255.
// ������ ���������� ������������ � target
void UBitmap::Contrasting(UBitmap *target)
{
 switch(ColorModel)
 {
  case ubmColor:
   Contrasting(0,UColorT(255,255,255),target);
  break;

  case ubmGray:
   Contrasting(0,UColorT(255,255,255),target);
  break;

  case ubmMath:
   Contrasting(0,255,target);
  break;
 }
}

// ����������������. ���������� �������� �������� ������� � ������� minb - maxb.
// ������ ���������� ������������ � target
void UBitmap::Contrasting(UColorT minb, UColorT maxb, UBitmap *target)
{
 int i;
 UColorT minf, maxf; // ������� � �������� �����������
 UColorT *out=0;
 unsigned int dif_r,dif_g,dif_b,dif_c;
 UBMColorModel cmodel=(target)?target->ColorModel:ColorModel;

 if(target)
  {
   target->SetRes(Width,Height);
   target->SetColorModel(ColorModel,false);
   out=target->Data;
  }
 else
  out=Data;

 FindColorRange(minf,maxf);
 switch(ColorModel)
 {
  case ubmColor:

  dif_r=maxf.r-minf.r;
  dif_g=maxf.g-minf.g;
  dif_b=maxf.b-minf.b;

  if(minf.r!=maxf.r)
  {
   for(i=0;i<Length;i++)
	out[i].r=(((Data+i)->r-minf.r)*maxb.r)/dif_r+minb.r;
  }
  if(minf.g!=maxf.g)
  {
   for(i=0;i<Length;i++)
    out[i].g=(((Data+i)->g-minf.g)*maxb.g)/dif_g+minb.g;
  }
  if(minf.b!=maxf.b)
  {
   for(i=0;i<Length;i++)
    out[i].b=(((Data+i)->b-minf.b)*maxb.b)/dif_b+minb.b;
  }
  break;

  case ubmGray:
  dif_r=maxf.r-minf.r;
  if(minf.r==maxf.r)
   break;
  for(i=0;i<Length;i++)
   out[i].r=out[i].b=out[i].g=(unsigned int)((int((Data+i)->r)-int(minf.r))*int(maxb.b))/dif_r+int(minb.b);
  break;

  case ubmMath:
  dif_c=maxf.c-minf.c;
  if(minf.c==maxf.c)
   break;
  for(i=0;i<Length;i++)
   out[i].c=(unsigned int)(((Data+i)->c-minf.c)*maxb.c)/dif_c+minb.c;
  break;
 }

 if(target && AutoCModelConvert)
  target->SetColorModel(cmodel);
}

// ��������� ��������.
void UBitmap::Looping(UBitmap *target, UBMLoopingMethod method)
{
 switch(method)
 {
 case ubmNative:
  NativeLooping(target);
 break;

 case ubmSobel:
  SobelLooping(target);
 break;
 }
}

// ���������� ����������� ����������� � ������� threshold
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
// ������� � ��������� ���� ������ ��������������� ������� 'minval'
// ������� � ��������� ���� ������ ��������������� ������� 'maxval'
void UBitmap::Binarization(UColorT threshold, UColorT minval, UColorT maxval,
                          UBitmap *target)
{
 UColorT *out;
 UBMColorModel cmodel=(target)?target->ColorModel:ColorModel;

 if(target)
  {
   target->SetRes(Width,Height);
   target->SetColorModel(ColorModel,false);
   out=target->Data;
  }
 else
  {
   out=Data;
  }

 switch(ColorModel)
  {
   case ubmColor:
	for(int i=0;i<Length;i++)
     {
      (out+i)->r=((Data+i)->r >= threshold.r)?maxval.r:minval.r;
      (out+i)->g=((Data+i)->g >= threshold.g)?maxval.r:minval.g;
      (out+i)->b=((Data+i)->b >= threshold.b)?maxval.r:minval.b;
     }
   break;

   case ubmGray:
    for(int i=0;i<Length;i++)
       (out+i)->r=(out+i)->g=(out+i)->b=
                ((Data+i)->b >= threshold.b)?maxval.b:minval.b;
   break;
   
   case ubmMath:
    for(int i=0;i<Length;i++)
     (out+i)->c=((Data+i)->c >= threshold.c)?maxval.c:minval.c;
   break;
  }

 if(target && AutoCModelConvert)
  target->SetColorModel(cmodel);
}


// ���������� �������������� ����������� ����������� ��
// ������, ��������������� ����� ���������������� ������� �����������
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
// ������� � ��������� ���� ������ ��������������� ������� 'minval'
// ������� � ��������� ���� ������ ��������������� ������� 'maxval'
void UBitmap::Binarization(UColorT minval, UColorT maxval,
                            UBitmap *target)
{
 Binarization(FindAverageColor(), minval, maxval, target);
}

// ������������ ���������� ����������� ������� ����������
// �� ����� �������� 'masksize'
// ���� ������ ����� ����� ������, �� �� �����������
// �� ���������� �������� ���������
void UBitmap::MaskFiltering(int mask, UBitmap *target) const
{
 UColorT *out,*pout,*pin,*ppout,*ppin;
 unsigned int r,g,b;
 int i,j, n,m;
 int halfmask,quadmask;
 UBMColorModel cmodel=(target)?target->ColorModel:ColorModel;

 if(!target)
  return;

 if(mask < 0)
  mask=1;
 if(mask %2 == 0)
  ++mask;

 if(mask >= ((Width<Height)?Width:Height))
  return;

 if(mask == 1)
  {
   *target=*this;
   if(target && AutoCModelConvert)
      target->SetColorModel(cmodel);

   return;
  }

 halfmask=mask>>1;
 quadmask=mask*mask;

 target->SetRes(Width,Height);
 target->ColorModel=ColorModel;
 out=target->Data;

 switch(ColorModel)
 {
  case ubmColor:
   pout=out;
   pin=Data;

   for(j=halfmask;j<Height-halfmask;j++)
    {
     r=g=b=0;
     for(n=-halfmask;n<=halfmask;n++)
      for(m=-halfmask;m<=halfmask;m++)
       {
        ppin=pin+(j+n)*Width+m+halfmask;
        r+=ppin->r;
        g+=ppin->g;
        b+=ppin->b;
       }

     ppout=pout+j*Width+halfmask;
     ppout->r=r/quadmask;
     ppout->g=g/quadmask;
     ppout->b=b/quadmask;

     for(i=halfmask+1;i<Width-halfmask;i++)
     {
      for(n=-halfmask;n<=halfmask;n++)
      {
       ppin=pin+(j+n)*Width+i+halfmask;
       r+=ppin->r;
       g+=ppin->g;
       b+=ppin->b;
      }

      for(n=-halfmask;n<=halfmask;n++)
      {
       ppin=pin+(j+n)*Width+i-halfmask-1;
       r-=ppin->r;
       g-=ppin->g;
       b-=ppin->b;
      }

      ppout=pout+j*Width+i;
      ppout->r=r/quadmask;
      ppout->g=g/quadmask;
      ppout->b=b/quadmask;
	 }
    }

   // ���������� ������ �����������

   // ������� �������
   for(j=0;j<halfmask;j++)
   {
    for(i=0;i<Width;i++)
    {
     if(i<halfmask)
      quadmask=(halfmask+i+1)*(halfmask+j+1);
	 else
     if(i>Width-halfmask)
      quadmask=(halfmask+Width-i)*(halfmask+j+1);
     else
      quadmask=mask*(halfmask+j+1);

     r=g=b=0;
     for(n=-j;n<=halfmask;n++)
      for(m=(i<halfmask)?-i:-halfmask;m<=((i>Width-halfmask)?Width-i-1:halfmask);m++)
      {
       ppin=pin+(j+n)*Width+i+m;
       r+=ppin->r;
       g+=ppin->g;
       b+=ppin->b;
      }

     ppout=pout+j*Width+i;
     ppout->r=r/quadmask;
     ppout->g=g/quadmask;
     ppout->b=b/quadmask;
    }
   }

   // ������ �������
   for(j=Height-1;j>=Height-halfmask;j--)
   {
    for(i=0;i<Width;i++)
    {
	 if(i<halfmask)
      quadmask=(halfmask+i+1)*(halfmask+Height-j);
     else
     if(i>Width-halfmask)
      quadmask=(halfmask+Width-i)*(halfmask+Height-j);
     else
      quadmask=mask*(halfmask+Height-j);

     r=g=b=0;
     for(n=-halfmask;n<=Height-j;n++)
      for(m=(i<halfmask)?-i:-halfmask;m<=((i>Width-halfmask)?Width-i-1:halfmask);m++)
      {
	   ppin=pin+(j+n)*Width+i+m;
       r+=ppin->r;
       g+=ppin->g;
       b+=ppin->b;
      }

     ppout=pout+j*Width+i;
     ppout->r=r/quadmask;
     ppout->g=g/quadmask;
     ppout->b=b/quadmask;
    }
   }

   // ����� � ������ �������
   for(j=halfmask;j<Height-halfmask;j++)
   {
    for(i=0;i<halfmask;i++)
    {
     quadmask=mask*(halfmask+i+1);

     r=g=b=0;
     for(n=-halfmask;n<=halfmask;n++)
      for(m=-i;m<=halfmask;m++)
      {
       ppin=pin+(j+n)*Width+i+m;
       r+=ppin->r;
       g+=ppin->g;
       b+=ppin->b;
	  }

     ppout=pout+j*Width+i;
     ppout->r=r/quadmask;
     ppout->g=g/quadmask;
     ppout->b=b/quadmask;
    }

    for(i=Width-1;i>=Width-halfmask;i--)
    {
     quadmask=mask*(halfmask+Width-i);

	 r=g=b=0;
     for(n=-halfmask;n<=halfmask;n++)
      for(m=-halfmask;m<=Width-i-1;m++)
      {
       ppin=pin+(j+n)*Width+i+m;
       r+=ppin->r;
       g+=ppin->g;
       b+=ppin->b;
      }

     ppout=pout+j*Width+i;
     ppout->r=r/quadmask;
     ppout->g=g/quadmask;
     ppout->b=b/quadmask;
    }
   }
  break;

  case ubmGray:
   pout=out;
   pin=Data;

   for(j=halfmask;j<Height-halfmask;j++)
    {
     b=0;
     for(n=-halfmask;n<=halfmask;n++)
      for(m=-halfmask;m<=halfmask;m++)
       b+=(pin+(j+n)*Width+m+halfmask)->b;

     ppout=pout+j*Width+halfmask;
     ppout->b=ppout->g=ppout->r=b/quadmask;

     for(i=halfmask+1;i<Width-halfmask;i++)
     {
      for(n=-halfmask;n<=halfmask;n++)
       b+=(pin+(j+n)*Width+i+halfmask)->b;

      for(n=-halfmask;n<=halfmask;n++)
       b-=(pin+(j+n)*Width+i-halfmask-1)->b;

	  ppout=pout+j*Width+i;
      ppout->b=ppout->g=ppout->r=b/quadmask;
     }
    }

   // ���������� ������ �����������

   // ������� �������
   for(j=0;j<halfmask;j++)
   {
    for(i=0;i<Width;i++)
    {
     if(i<halfmask)
      quadmask=(halfmask+i+1)*(halfmask+j+1);
     else
     if(i>Width-halfmask)
      quadmask=(halfmask+Width-i)*(halfmask+j+1);
     else
      quadmask=mask*(halfmask+j+1);

     b=0;
     for(n=-j;n<=halfmask;n++)
      for(m=(i<halfmask)?-i:-halfmask;m<=((i>Width-halfmask)?Width-i-1:halfmask);m++)
       b+=(pin+(j+n)*Width+i+m)->b;

      ppout=pout+j*Width+i;
      ppout->b=ppout->g=ppout->r=b/quadmask;
    }
   }

   // ������ �������
   for(j=Height-1;j>=Height-halfmask;j--)
   {
    for(i=0;i<Width;i++)
    {
     if(i<halfmask)
      quadmask=(halfmask+i+1)*(halfmask+Height-j);
     else
     if(i>Width-halfmask)
      quadmask=(halfmask+Width-i)*(halfmask+Height-j);
	 else
      quadmask=mask*(halfmask+Height-j);

     b=0;
     for(n=-halfmask;n<=Height-j;n++)
      for(m=(i<halfmask)?-i:-halfmask;m<=((i>Width-halfmask)?Width-i-1:halfmask);m++)
       b+=(pin+(j+n)*Width+i+m)->b;

      ppout=pout+j*Width+i;
      ppout->b=ppout->g=ppout->r=b/quadmask;
    }
   }

   // ����� � ������ �������
   for(j=halfmask;j<Height-halfmask;j++)
   {
    for(i=0;i<halfmask;i++)
    {
     quadmask=mask*(halfmask+i+1);

     b=0;
     for(n=-halfmask;n<=halfmask;n++)
      for(m=-i;m<=halfmask;m++)
       b+=(pin+(j+n)*Width+i+m)->b;

      ppout=pout+j*Width+i;
      ppout->b=ppout->g=ppout->r=b/quadmask;
    }

    for(i=Width-1;i>=Width-halfmask;i--)
    {
     quadmask=mask*(halfmask+Width-i);

     b=0;
     for(n=-halfmask;n<=halfmask;n++)
      for(m=-halfmask;m<=Width-i-1;m++)
       b+=(pin+(j+n)*Width+i+m)->b;

     ppout=pout+j*Width+i;
     ppout->b=ppout->g=ppout->r=b/quadmask;
	}
   }
  break;

  case ubmMath:
   pout=out;
   pin=Data;

   for(j=halfmask;j<Height-halfmask;j++)
    {
     b=0;
     for(n=-halfmask;n<=halfmask;n++)
      for(m=-halfmask;m<=halfmask;m++)
       b+=(pin+(j+n)*Width+m+halfmask)->c;

     (pout+j*Width+halfmask)->c=b/quadmask;

     for(i=halfmask+1;i<Width-halfmask;i++)
     {
      for(n=-halfmask;n<=halfmask;n++)
       b+=(pin+(j+n)*Width+i+halfmask)->c;

      for(n=-halfmask;n<=halfmask;n++)
       b-=(pin+(j+n)*Width+i-halfmask-1)->c;

      (pout+j*Width+i)->c=b/quadmask;
     }
    }

   // ���������� ������ �����������

   // ������� �������
   for(j=0;j<halfmask;j++)
   {
    for(i=0;i<Width;i++)
    {
     if(i<halfmask)
      quadmask=(halfmask+i+1)*(halfmask+j+1);
     else
     if(i>Width-halfmask)
	  quadmask=(halfmask+Width-i)*(halfmask+j+1);
     else
      quadmask=mask*(halfmask+j+1);

     b=0;
     for(n=-j;n<=halfmask;n++)
      for(m=(i<halfmask)?-i:-halfmask;m<=((i>Width-halfmask)?Width-i-1:halfmask);m++)
       b+=(pin+(j+n)*Width+i+m)->c;

     (pout+j*Width+i)->c=b/quadmask;
    }
   }

   // ������ �������
   for(j=Height-1;j>=Height-halfmask;j--)
   {
    for(i=0;i<Width;i++)
    {
     if(i<halfmask)
      quadmask=(halfmask+i+1)*(halfmask+Height-j);
     else
     if(i>Width-halfmask)
      quadmask=(halfmask+Width-i)*(halfmask+Height-j);
     else
      quadmask=mask*(halfmask+Height-j);

     b=0;
     for(n=-halfmask;n<=Height-j;n++)
	  for(m=(i<halfmask)?-i:-halfmask;m<=((i>Width-halfmask)?Width-i-1:halfmask);m++)
       b+=(pin+(j+n)*Width+i+m)->c;

     (pout+j*Width+i)->c=b/quadmask;
    }
   }

   // ����� � ������ �������
   for(j=halfmask;j<Height-halfmask;j++)
   {
    for(i=0;i<halfmask;i++)
    {
	   quadmask=mask*(halfmask+i+1);

     b=0;
     for(n=-halfmask;n<=halfmask;n++)
      for(m=-i;m<=halfmask;m++)
       b+=(pin+(j+n)*Width+i+m)->c;

     (pout+j*Width+i)->c=b/quadmask;
    }

    for(i=Width-1;i>=Width-halfmask;i--)
    {
       quadmask=mask*(halfmask+Width-i);

     b=0;
     for(n=-halfmask;n<=halfmask;n++)
      for(m=-halfmask;m<=Width-i-1;m++)
       b+=(pin+(j+n)*Width+i+m)->c;

     (pout+j*Width+i)->c=b/quadmask;
    }
   }
  break;
 }

 if(target && AutoCModelConvert)
  target->SetColorModel(cmodel);       
}

// ����������� �����������
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
// ��� ���� �������� ������� ���� ��������������� == 255
// �.�. ������ ubmMath ��������� ����������� � [0:255] ����� ���������
void UBitmap::Inverse(UBitmap *target)
{
 UColorT *out;
 UBMColorModel cmodel=(target)?target->ColorModel:ColorModel;

 if(target)
  {
   target->SetRes(Width,Height);
   target->SetColorModel(ColorModel,false);
   out=target->Data;
  }
 else
  {
   out=Data;
  }

 switch(ColorModel)
  {
   case ubmColor:
    for(int i=0;i<Length;i++)
     {
      (out+i)->r=255-(Data+i)->r;
      (out+i)->g=255-(Data+i)->g;
      (out+i)->b=255-(Data+i)->b;
     }
   break;

   case ubmGray:
    for(int i=0;i<Length;i++)
       (out+i)->r=(out+i)->g=(out+i)->b=255-(Data+i)->b;
   break;

   case ubmMath:
    for(int i=0;i<Length;i++)
     (out+i)->c=255-(Data+i)->c;
   break;
  }

 if(target && AutoCModelConvert)
  target->SetColorModel(cmodel);
}

// ������������ ���������� ����������� �����
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
bool UBitmap::DifferenceFrame(const UBitmap *deduction, UBitmap *target)
{
 int i, j;
 int rdif, gdif, bdif;
 UColorT *buf, *bufdata, *bufded;

 if(!deduction || Width != deduction->Width || Height != deduction->Height ||
    ColorModel != deduction->ColorModel)
  return false;

 bufdata = Data;
 bufded = deduction->GetData();
 if(target)
 {
  target->SetRes(Width,Height);
  target->SetColorModel(ColorModel,false);
  buf = target->GetData();
 }
 else
  buf=Data;

 switch(ColorModel)
 {
  case ubmColor:
    for(i=0; i<Height; i++)
     for(j=0; j<Width; j++)
     {
      bdif = (int)(bufdata->b)
                    - (int)(bufded->b);
      gdif = (int)(bufdata->g)
                    - (int)(bufded->g);
	  rdif = (int)(bufdata->r)
                    - (int)(bufded->r);
      buf->r = (rdif<0)?-rdif:rdif;
      buf->g = (gdif<0)?-gdif:gdif;
      buf->b = (bdif<0)?-bdif:bdif;
      ++buf; ++bufdata; ++bufded;
     }
  break;

  case ubmGray:
    for(i=0; i<Height; i++)
     for(j=0; j<Width; j++)
	 {
      bdif = (int)(bufdata->b)
                    - (int)(bufded->b);
      buf->r = buf->g = buf->b = (bdif<0)?-bdif:bdif;
      ++buf; ++bufdata; ++bufded;
     }
  break;

  case ubmMath:
    for(i=0; i<Height; i++)
     for(j=0; j<Width; j++)
     {
      bdif = (int)(bufdata->c)
                    - (int)(bufded->c);
      buf->c = (bdif<0)?-bdif:bdif;
      ++buf; ++bufdata; ++bufded;
     }
  break;
 }

 return true;
}
// -------------------------


// -----------------------
// ������������� ���������
// -----------------------
// �������� ������������
// �������� ������ ��������� ������ ���������� ������� ���������
UBitmap& UBitmap::operator = (const UBitmap &bitmap)
{
 if(Width != bitmap.Width || Height != bitmap.Height)
  {
   delete[] Data;
   Width=bitmap.Width;
   Height=bitmap.Height;
   Length=bitmap.Length;
   Data=new UColorT[Width*Height];
  }
 memcpy(Data,bitmap.Data,Length*sizeof(UColorT));
 ColorModel=bitmap.ColorModel;

 return *this;
}
// -----------------------


// ������� ������
// -----------------------
// ������ ��������� ������� �����������
// -----------------------
// ��������� ������� ����������� � ����������� �������������
bool UBitmap::ResizeConst(UColorT *output, UColorT* input,
                                int oWidth, int oHeight,
                                int nWidth, int nHeight)
{
 int i,j,n,m;

 for(j=0;j<nHeight;j++)
  for(i=0;i<nWidth;i++)
   {
	n=i*oWidth/nWidth;
	m=j*oHeight/nHeight;
	output[j*nWidth+i]=input[m*oWidth+n];
   }

 return true;
}

// ��������� ������� ����������� � �������� �������������
bool UBitmap::ResizeLinear(UColorT *output, UColorT* input,
                                int oWidth, int oHeight,
                                int nWidth, int nHeight)
{
/*
    float    fxScale    = float(oWidth) / float(nWidth);
    float    fyScale    = float(oHeight) / float(nHeight);

    float    fxOppositeScale = float(nWidth) / float(oWidth);
	float    fyOppositeScale = float(nHeight) / float(oHeight);

    float    fxIn , fyIn;

    int        *ipInputCompres = 0;

    int        *ipInputRealBitmap = input;
    int        ixInputRealSize = oWidth;
    int        iyInputRealSize = oHeight;

    int        ixPartDeriv , iyPartDeriv , ixyPartDeriv;
    int        iNewColor;
    int        x,y;
    int        l,m;
    int        iSumm;
    int        iCount;

    
    //    ���� ������ �� -x- � �� -y-
    if(fxScale > 1.0 && fyScale > 1.0)
    {
        for(x = 0 , fxIn = 0.0; x < nWidth; ++x , fxIn += fxScale)
        {
            for(y = 0 , fyIn = 0.0; y < nHeight; ++y , fyIn += fyScale)
            {
                iCount = iSumm = 0;
                for(l = (int)fxIn; l < int(fxIn+fxScale); ++l)
                {
					for(m = (int)fyIn; m < int(fyIn+fyScale); ++m)
                    {
                        if(l < oWidth && m < oHeight)
                        {
                            iSumm += input[ l*oHeight + m ];
                            ++iCount;
                        }
                    }
                }
                output[x*nHeight + y] = iSumm / iCount;
            }
        }
		return true;
    }

    if(fxScale > 1.0) // ���� ������ �� -x- , � �� -y- ���������
    {
        ipInputCompres = new int[ oHeight * nWidth ];
        ixInputRealSize = nWidth;
        iyInputRealSize = oHeight;

        fxOppositeScale = 1.0;

        for(x = 0 , fxIn = 0.0; x < ixInputRealSize; ++x , fxIn += fxScale)
        {
            for(y = 0; y < iyInputRealSize; ++y)
            {
                iCount = iSumm = 0;
                for(l = (int)fxIn; l < int(fxIn+fxScale); ++l)
                {
                    if(l < oWidth)
                    {
                        iSumm += input[ l*oHeight + y ];
                        ++iCount;
                    }
                }
                ipInputCompres[x*iyInputRealSize + y] = iSumm / iCount;
            }
        }
        ipInputRealBitmap = ipInputCompres;
	}
    else    if(fyScale > 1.0) // ���� ������ �� -y- , � �� -x- ���������
    {        
        ipInputCompres = new int[ nHeight * oWidth ];
        ixInputRealSize = oWidth;
        iyInputRealSize = nHeight;

        fyOppositeScale = 1.0;

        for(x = 0 ; x < ixInputRealSize; ++x )
        {
            for(y = 0 , fyIn = 0.0; y < iyInputRealSize; ++y , fyIn += fyScale)
			{
                iCount = iSumm = 0;
                for(m = (int)fyIn; m < int(fyIn+fyScale); ++m)
                {
                    if(m < oHeight)
                    {
                        iSumm += input[ x*oHeight + m ];
                        ++iCount;
                    }
                }
                ipInputCompres[x*iyInputRealSize + y] = iSumm / iCount;
            }
        }
        ipInputRealBitmap = ipInputCompres;        
    }

    for(x = 0; x < ixInputRealSize; ++x)
    {
        for(y = 0; y < iyInputRealSize; ++y)
        {
            ixPartDeriv = int(float(ipInputRealBitmap[(x+1)*iyInputRealSize + y] - ipInputRealBitmap[x*iyInputRealSize + y]) / fxOppositeScale);
            iyPartDeriv = int(float(ipInputRealBitmap[x*iyInputRealSize + y+1] - ipInputRealBitmap[x*iyInputRealSize + y]) / fyOppositeScale);

            ixyPartDeriv = int(float(ipInputRealBitmap[(x+1)*iyInputRealSize + y+1] - ipInputRealBitmap[x*iyInputRealSize + y]) /
                                (fxOppositeScale*fyOppositeScale) - float(ixPartDeriv)/fxOppositeScale - float(iyPartDeriv)/fyOppositeScale);

            for(l = 0; l < 1.0/fxScale; ++l)
            {
				for(m = 0; m < 1.0/fyScale; ++m)
                {
                    iNewColor = (int)( ipInputRealBitmap[x*iyInputRealSize + y] + ixPartDeriv*l + iyPartDeriv*m + ixyPartDeriv*l*m );

                    if(iNewColor > 255)
                        iNewColor = 255;
                    else    if(iNewColor < 0)
                        iNewColor = 0;
                    
                    output[ (int(float(x)*fxOppositeScale) + l)*nHeight +
                        int(float(y)*fyOppositeScale) + m ] = iNewColor;
                }
			}
        }
    }
    
    
    delete[]    ipInputCompres;
    return true;
    */
 return false;
}

// ��������� ������� ����������� � ���������� �������������
bool UBitmap::ResizeNolinear(UColorT *output, UColorT* input,
							int oWidth, int oHeight,
							int nWidth, int nHeight)
{
 // ��������� ���������� ��������� �������
 double StepX, StepY;

	int x0coord, y0coord, x1coord, y1coord;
	UColorT *Dest, *Src0, *Src1;
	unsigned int p1, p2, p3, p4;
	unsigned int Res;
	double corrX, corrY;
	double di=0;
	double dj=0;
	int pDestLine= oWidth;

	StepX= (double)oWidth / (double)nWidth;
	StepY= (double)oHeight / (double)nHeight;


 switch(ColorModel)
 {
 case ubmColor:
  corrX= (StepX>1)? StepX-1. : 0;
  corrY= (StepY>1)? StepY-1. : 0;

  // ������������ �� ������ ������
  Dest= output;
  di=0;
  for(int i=0; i<nHeight; i++, di+=StepY)
  {
	y0coord= (int)di;
	y1coord= (int)(di + corrY);
	Src0= input + y0coord * oWidth;
	Src1= input + y1coord * oWidth;
	dj=0;
	for(int j=0; j<nWidth; j++, dj+=StepX, Dest++)
	{
	 x0coord= (int)dj;
	 x1coord= (int)(dj + corrX);
	 p1= (Src0 + x0coord)->b;
	 p2= (Src0 + x1coord)->b;
	 p3= (Src1 + x0coord)->b;
	 p4= (Src1 + x1coord)->b;
	 Res= p1 + p2 + p3 + p4;
	 Dest->b= Res>>2;

	 p1= (Src0 + x0coord)->g;
	 p2= (Src0 + x1coord)->g;
	 p3= (Src1 + x0coord)->g;
	 p4= (Src1 + x1coord)->g;
	 Res= p1 + p2 + p3 + p4;
	 Dest->g= Res>>2;

	 p1= (Src0 + x0coord)->r;
	 p2= (Src0 + x1coord)->r;
	 p3= (Src1 + x0coord)->r;
	 p4= (Src1 + x1coord)->r;
	 Res= p1 + p2 + p3 + p4;
	 Dest->r= Res>>2;
	}
   }
 break;

 case ubmGray:
  corrX= (StepX>1)? StepX-1. : 0;
  corrY= (StepY>1)? StepY-1. : 0;

  // ������������ �� ������ ������
  Dest= output;
  di=0;
  for(int i=0; i<nHeight; i++, di+=StepY)
  {
	y0coord= (int)di;
	y1coord= (int)(di + corrY);
	Src0= input + y0coord * oWidth;
	Src1= input + y1coord * oWidth;
	dj=0;
	for(int j=0; j<nWidth; j++, dj+=StepX, Dest++)
	{
	 x0coord= (int)dj;
	 x1coord= (int)(dj + corrX);
	 p1= (Src0 + x0coord)->b;
	 p2= (Src0 + x1coord)->b;
	 p3= (Src1 + x0coord)->b;
	 p4= (Src1 + x1coord)->b;
	 Res= p1 + p2 + p3 + p4;
	 Dest->r=Dest->g=Dest->b= Res>>2;
	}
   }
 break;

 case ubmMath:
  corrX= (StepX>1)? StepX-1. : 0;
  corrY= (StepY>1)? StepY-1. : 0;

  // ������������ �� ������ ������
  Dest= output;
  di=0;
  for(int i=0; i<nHeight; i++, di+=StepY)
  {
	y0coord= (int)di;
	y1coord= (int)(di + corrY);
	Src0= input + y0coord * oWidth;
	Src1= input + y1coord * oWidth;
	dj=0;
	for(int j=0; j<nWidth; j++, dj+=StepX, Dest++)
	{
	 x0coord= (int)dj;
	 x1coord= (int)(dj + corrX);
	 p1= (Src0 + x0coord)->c;
	 p2= (Src0 + x1coord)->c;
	 p3= (Src1 + x0coord)->c;
	 p4= (Src1 + x1coord)->c;
	 Res= p1 + p2 + p3 + p4;
	 Dest->c= Res>>2;
	}
   }
 break;
 }

 return true;
}
// -----------------------


// -----------------------
// ������ ��������� ��������
// -----------------------
// ������������ ��������
void UBitmap::NativeLooping(UBitmap *target)
{
 int i; // �������
 UColorT *pData, *ptData;
 int r,g,b;
 int tr,tg,tb;
 UBMColorModel cmodel=(target)?target->ColorModel:ColorModel;


 if(!target)
  return;
 else
 {
  target->SetRes(Width,Height);
  target->SetColorModel(ColorModel,false);
 }

 UColorT cmin,cmax;
 cmin.c=0;
 memset(&cmax,0xFF,sizeof(cmax));

 pData=Data;
 ptData=target->Data;

 switch(ColorModel)
 {
  case ubmColor:
   for(i=0;i<Length;i++,pData++,ptData++)
   {
	tr=tg=tb=0;

	r=pData->r;
	g=pData->g;
	b=pData->b;
	if(i>Width-1)
	{
	 if(i%Width!=0)
	 {
	  tr+=abs(r-(pData-Width-1)->r);
	  tg+=abs(g-(pData-Width-1)->g);
	  tb+=abs(b-(pData-Width-1)->b);
	 }
	 tr+=abs(r-(pData-Width)->r);
	 tg+=abs(g-(pData-Width)->g);
	 tb+=abs(b-(pData-Width)->b);
	 if((i+1)%Width!=0)
	 {
	  tr+=abs(r-(pData-Width+1)->r);
	  tg+=abs(g-(pData-Width+1)->g);
	  tb+=abs(b-(pData-Width+1)->b);
	 }
	}
	if(i%Width!=0)
	{
	 tr+=abs(r-(pData-1)->r);
	 tg+=abs(g-(pData-1)->g);
	 tb+=abs(b-(pData-1)->b);
	}
	if((i+1)%Width!=0)
	{
	 tr+=abs(r-(pData+1)->r);
	 tg+=abs(g-(pData+1)->g);
	 tb+=abs(b-(pData+1)->b);
	}
	if(i<Length-Width)
	{
	 if(i%Width!=0)
	 {
	  tr+=abs(r-(pData+Width-1)->r);
	  tg+=abs(g-(pData+Width-1)->g);
	  tb+=abs(b-(pData+Width-1)->b);
	 }
	 tr+=abs(r-(int)(pData+Width)->r);
	 tg+=abs(g-(int)(pData+Width)->g);
	 tb+=abs(b-(int)(pData+Width)->b);
	 if((i+1)%Width!=0)
	 {
	  tr+=abs(r-(pData+Width+1)->r);
	  tg+=abs(g-(pData+Width+1)->g);
	  tb+=abs(b-(pData+Width+1)->b);
	 }
	}
	ptData->r=tr>>3;
	ptData->g=tg>>3;
	ptData->b=tb>>3;
   }
   target->Contrasting(cmin,cmax);
  break;

  case ubmGray:
   for(i=0;i<Length;i++,pData++,ptData++)
   {
	tr=tg=tb=0;

	b=pData->b;

	if(i>Width-1)
	{
	 if(i%Width!=0)
	  tr=tg=tb+= abs(b-(pData-Width-1)->b);
	 tr=tg=tb+= abs(b-(pData-Width)->b);
	 if((i+1)%Width!=0)
	  tr=tg=tb+= abs(b-(pData-Width+1)->b);
	}
	if(i%Width!=0)
	 tr=tg=tb+= abs(b-(pData-1)->b);
	if((i+1)%Width!=0)
	 tr=tg=tb+= abs(b-(pData+1)->b);
	if(i<Length-Width)
	{
	 if(i%Width!=0)
	  tr=tg=tb+= abs(b-(pData+Width-1)->b);
	 tr=tg=tb+= abs(b-(pData+Width)->b);
	 if((i+1)%Width!=0)
	  tr=tg=tb+= abs(b-(pData+Width+1)->b);
	}

	ptData->r=ptData->g=ptData->b=tb>>3;
   }

   target->Contrasting();
  break;

  case ubmMath:
   for(i=0;i<Length;i++,pData++,ptData++)
   {
	unsigned int &tc=ptData->c;
	tc=0;

	b=pData->c;

	tc=0;
	if(i>Width-1)
	{
	 if(i%Width!=0)
	  tc+=abs(b-(pData-Width-1)->c);
	 tc+=abs(b-(pData-Width)->c);
	 if((i+1)%Width!=0)
	  tc+=abs(b-(pData-Width+1)->c);
	}
	if(i%Width!=0)
	 tc+=abs(b-(pData-1)->c);
	if((i+1)%Width!=0)
	 tc+=abs(b-(pData+1)->c);
	if(i<Length-Width)
	{
	 if(i%Width!=0)
	  tc+=abs(b-(pData+Width-1)->c);
	 tc+=abs(b-(pData+Width)->c);
	 if((i+1)%Width!=0)
	  tc+=abs(b-(pData+Width+1)->c);
	}
   }
   target->Contrasting();
  break;
 }

 if(AutoCModelConvert)
  target->SetColorModel(cmodel);
}

// ������ ������
void UBitmap::SobelLooping(UBitmap *target)
{
 int i; // �������
 UColorT *pData, *ptData;
 int r,g,b;
 int tr,tg,tb;
 UColorT *pNBLine;
 unsigned int Gx,Gy;
 UBMColorModel cmodel=(target)?target->ColorModel:ColorModel;

		int x = 0, y = 0;
		int G00, G01, G02, G10, G12, G20, G21, G22;


 if(!target)
  return;
 else
 {
  target->SetRes(Width,Height);
  target->SetColorModel(ColorModel,false);
 }

 UColorT cmin,cmax;
 cmin.c=0;
 memset(&cmax,0xFF,sizeof(cmax));

 pData=Data;
 ptData=target->Data;
 switch(ColorModel)
 {
  case ubmColor:
		pData+=Width;

		memset(ptData, 0, Width*sizeof(UColorT));	// 1 ������
		ptData += Width;
		for(y = 1; y < Height-1; y++)
		{
			*ptData++=0;
			pData++;// 1 pixel
			for(x = 1; x < Width-1; x++, pData++)
			{
				pNBLine = pData-Width;

				G00 = (pNBLine-1)->b;
				G01 = pNBLine->b;
				G02 = (pNBLine+1)->b;
				pNBLine += Width<<1;
				G10 = (pData-1)->b;
				G12 = (pData+1)->b;
				G20 = (pNBLine-1)->b;
				G21 = pNBLine->b;
				G22 = (pNBLine+1)->b;

				Gx= (abs(-G00+G02-(G10<<1)+(G12<<1)-G20+G22))>>3;
				Gy= (abs(-G00-(G01<<1)-G02+G20+(G21<<1)+G22))>>3;

				ptData->b = (Gx + Gy);

				pNBLine -= Width<<1;
				G00 = (pNBLine-1)->g;
				G01 = pNBLine->g;
				G02 = (pNBLine+1)->g;
				pNBLine += Width<<1;
				G10 = (pData-1)->g;
				G12 = (pData+1)->g;
				G20 = (pNBLine-1)->g;
				G21 = pNBLine->g;
				G22 = (pNBLine+1)->g;

				Gx= (abs(-G00+G02-(G10<<1)+(G12<<1)-G20+G22))>>3;
				Gy= (abs(-G00-(G01<<1)-G02+G20+(G21<<1)+G22))>>3;

				ptData->g= (Gx + Gy);

				pNBLine -= Width<<1;
				G00 = (pNBLine-1)->r;
				G01 = pNBLine->r;
				G02 = (pNBLine+1)->r;
				pNBLine += Width<<1;
				G10 = (pData-1)->r;
				G12 = (pData+1)->r;
				G20 = (pNBLine-1)->r;
				G21 = pNBLine->r;
				G22 = (pNBLine+1)->r;

				Gx= (abs(-G00+G02-(G10<<1)+(G12<<1)-G20+G22))>>3;
				Gy= (abs(-G00-(G01<<1)-G02+G20+(G21<<1)+G22))>>3;

				ptData->r= (Gx + Gy);

				++ptData;
			}
			*ptData++=0;
			pData++;// 1 pixel
		}
		memset(ptData, 0, Width*sizeof(UColorT));	// 1 ������
   target->Contrasting(cmin,cmax);
  break;

  case ubmGray:
		pData+=Width;

		memset(ptData, 0, Width*sizeof(UColorT));	// 1 ������
		ptData += Width;
		for(y = 1; y < Height-1; y++)
		{
			*ptData++=0;
			pData++;// 1 pixel
			for(x = 1; x < Width-1; x++, pData++)
			{
				pNBLine = pData-Width;

				G00 = (pNBLine-1)->b;
				G01 = pNBLine->b;
				G02 = (pNBLine+1)->b;
				pNBLine += Width<<1;
				G10 = (pData-1)->b;
				G12 = (pData+1)->b;
				G20 = (pNBLine-1)->b;
				G21 = pNBLine->b;
				G22 = (pNBLine+1)->b;

				Gx= (abs(-G00+G02-(G10<<1)+(G12<<1)-G20+G22))>>3;
				Gy= (abs(-G00-(G01<<1)-G02+G20+(G21<<1)+G22))>>3;

				ptData->b=ptData->g=ptData->r = (Gx + Gy);
				++ptData;
			}
			*ptData++=0;
			pData++;// 1 pixel
		}
		memset(ptData, 0, Width*sizeof(UColorT));	// 1 ������

   target->Contrasting();
  break;

  case ubmMath:
		pData+=Width;

		memset(ptData, 0, Width*sizeof(UColorT));	// 1 ������
		ptData += Width;
		for(y = 1; y < Height-1; y++)
		{
			*ptData++=0;
			pData++;// 1 pixel
			for(x = 1; x < Width-1; x++, pData++)
			{
				pNBLine = pData-Width;

				G00 = (pNBLine-1)->c;
				G01 = pNBLine->c;
				G02 = (pNBLine+1)->c;
				pNBLine += Width<<1;
				G10 = (pData-1)->c;
				G12 = (pData+1)->c;
				G20 = (pNBLine-1)->c;
				G21 = pNBLine->c;
				G22 = (pNBLine+1)->c;

				Gx= (abs(-G00+G02-(G10<<1)+(G12<<1)-G20+G22))>>3;
				Gy= (abs(-G00-(G01<<1)-G02+G20+(G21<<1)+G22))>>3;

				ptData->c=(Gx + Gy);
				++ptData;
			}
			*ptData++=0;
			pData++;// 1 pixel
		}
		memset(ptData, 0, Width*sizeof(UColorT));	// 1 ������

   target->Contrasting();
  break;
 }

 if(AutoCModelConvert)
  target->SetColorModel(cmodel);
}
// -----------------------

// -----------------------
// ������ �����-������
// -----------------------
// ��������� ����������� � �����
/*template <typename CharT>
ostream& operator << (basic_ostream<CharT> &stream, const UBitmap &bmp)
{
 unsigned char header[54];
 int filesize=54+Length;
 int value;

 // �������� ��������� �����
 memcpy(header,"BM",2);
 memcpy(header+2,&filesize,4);
 memset(header+6,0,4);
 value=54; memcpy(header+10,&value,4);

 // �������� ��������� bitmap
 value=40; memcpy(header+14,&value,4);
 memcpy(header+18,&Width,4);
 memcpy(header+22,&Height,4);
 value=1; memcpy(header+26,&value,2);
 value=32; memcpy(header+28,&value,2);
 value=0; memcpy(header+30,&value,4);
 memset(header+34,0,4);
 value=2835; memcpy(header+38,&value,4);
 value=2835; memcpy(header+42,&value,4);
 value=0; memcpy(header+46,&value,4);
 value=0; memcpy(header+50,&value,4);

 stream.write((char*)header,54);
 if(Data)
  stream.write((char*)Data,Length*sizeof(UColorT));

 return stream;
}*/

// ��������� ����������� �� ������
/*template <typename CharT>
istream& operator >> (basic_istream<CharT> &stream, UBitmap &bmp)
{
 unsigned char header[54];
 int width,height,filesize;
 int offset;

 stream.read((char*)header,54);

 memcpy(&filesize,header+2,4);
 memcpy(&offset,header+10,4);
 memcpy(&width,header+18,4);
 memcpy(&height,header+22,4);

 SetRes(width,height);
 stream.read((char*)Data,filesize-offset);

 return stream;
}*/

// -----------------------

}

#endif

