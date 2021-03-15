/* ************************************************************************** */
// Copyright Anton Fateev, 2009.
// E-mail: antonfat@gmail.com
/* ************************************************************************** */

#include <vcl.h>
   #include <dos.h>
   #include <math.h>
   #include <stdio.h>    //  ������� � �������

#pragma hdrstop

#include "VCLmain.h"
#include "Filter.h"
#include "Canny.h"
#include "Histrogr.h"
#include "Morf.h"
#include "Kontyr.h"
#include "Prosl.h"
 // #include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

 int intMatrix [2] [3] = {{1, 2, 3}, {4, 5, 6}};
 char errorE[] = "Error";
  // intMatrix [1][1] = 8;
 //---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
ComboBox1->Items->Add("�����");
ComboBox1->Items->Add("��������");
ComboBox1->Items->Add("�����-3");
ComboBox1->Items->Add("�����-5");
ComboBox1->Items->Add("�����-7");
ComboBox1->Items->Add("������ Y");
ComboBox1->Items->Add("������ X");
ComboBox1->Items->Add("��� ������");
ComboBox1->Items->Add("�������");

ComboBox2->Items->Add("����������");
ComboBox2->Items->Add("�������");
ComboBox2->Items->Add("��������");
ComboBox2->Items->Add("����������");
ComboBox2->Items->Add("�����");

ComboBox3->Items->Add("�����������");
ComboBox3->Items->Add("������");
ComboBox3->Items->Add("���������");
ComboBox3->Items->Add("����������");
ComboBox3->Items->Add("��������");

ComboBox4->Items->Add("�������");
ComboBox4->Items->Add("����-3");
ComboBox4->Items->Add("����-5");
ComboBox4->Items->Add("����-7");
ComboBox4->Items->Add("�����");
ComboBox4->Items->Add("������-3");
ComboBox4->Items->Add("������-5");
ComboBox4->Items->Add("������-7");

ComboBox5->Items->Add("�������");
ComboBox5->Items->Add("������");
ComboBox5->Items->Add("���������");



}
 void __fastcall TForm1::Button1Click(TObject *Sender)
{  //������ - ��������� ������
 if (B1trig[0]&&B1trig[1]) {   //��������� ��������
  B1trig[1] = false;  B1trig[0] = false;     }
 if (1-B1trig[0]&&B1trig[1]) {
  B1trig[0] = true;

  Edit1->Text = intMatrix [1][2] ;
  Bmp1.SetColorModel(ubmGray);
 Bmp1>>Image1->Picture->Bitmap;
   Image1->Repaint();
   Bmp2=Bmp1;
   Button1 -> Caption = AnsiString("Load Image");
 }
 //-----------------------------------------------------------------------
  if (1-B1trig[0]&&1-B1trig[1]) {
  B1trig[1] = true;

  //Image1->Picture->LoadFromFile("D:\\University\\���\\kater.bmp");
  if(OpenDialog->Execute())  {
 try
	{
	  String ext=ExtractFileExt(OpenDialog->FileName);
		if ((ext == ".jpg")||(ext == ".JPG")) {
		TJPEGImage *jpg=new TJPEGImage;
		jpg->LoadFromFile(OpenDialog->FileName);
	   //
						//
		Image1->Picture->Bitmap->Assign(jpg);
        delete jpg;

	  } else {        //*/
	  Image1->Picture->LoadFromFile(OpenDialog->FileName);
			 }
	  Form1->Caption = "Searh Area - " + OpenDialog->FileName;
	  numIt = 0;
	}
	catch (EInvalidGraphic &Ex)
	{    /// ��������� �� �������
	  MessageBeep(-1);
	  ShowMessage("������ �������� �����������");
	}

 Bmp1<<Image1->Picture->Bitmap;
 UColorT c=Bmp1(5,7);
 char r=Bmp1(5,7).r;
 Edit1->Text = IntToStr(int(r));  

  Button1 -> Caption = AnsiString("Image Load");
   /*
		TMemoryStream *stream1 = new TMemoryStream;
		jpg->SaveToStream(stream1);
		stream1->Seek(0,soFromBeginning);
		Image1->Picture->Bitmap->LoadFromStream(stream1);
		delete stream1;                         //*/
   }
  }
 //-----------------------------------------------------------
  //Image2->Picture->Bitmap;
 //a= Edit1->Text;
 //Image1->Visible = false;
 //intMatrix [1][1] += 10;

	  /*
 ArrImage.assign(Image1->Picture->Bitmap->Height,0);
 for(size_t i=0;i<ArrImage.size();i++)
  ArrImage[i].assign(Image1->Picture->Bitmap->Width*3,0);

 for(size_t i=0;i<ArrImage.size();i++)
  for(size_t j=0;j<ArrImage[i].size();j++)
  {
   ArrImage[i][j*3]=(Image1->Picture->Bitmap->Pixels[i][j] & 0x000000FF);
   ArrImage[i][j*3+1]=(Image1->Picture->Bitmap->Pixels[i][j] & 0x0000FF00)>>8;
   ArrImage[i][j*3+2]=(Image1->Picture->Bitmap->Pixels[i][j] & 0x00FF0000)>>16;
  }

//*/
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{  // ����� ������� ����������
  if (SaveDialog->Execute())
  {
	Image1->Picture->SaveToFile(SaveDialog->FileName + ".bmp");
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{   // ������ ����������
 Button4 -> Caption = "Ok";
 Bmp1=Bmp2;
 Bmp1>>Image1->Picture->Bitmap;
 if (Image2->Picture->Bitmap->Width > 3) {
  numIt++;
 }
 Image1->Repaint();
 Image2->Picture->Bitmap->Width=0;
 Image2->Picture->Bitmap->Height=0;
 Edit1->Text = numIt;
 }
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{ //������ ��������� �������� �������������
  if (Bmp1.GetLength() > 9) {

  Bmp2.SetRes(Bmp1.GetWidth(),Bmp1.GetHeight());

  if (ComboBox2->Text == "����������") {
   //ShowMessage ("gsfsf");
	 Bmp1.Contrasting ();
     UColorT min1, max1;
	 Bmp1.FindColorRange (min1, max1);
	 Edit1->Text = "min- " + IntToStr(int(min1.r))+"  max- "+IntToStr(int(max1.r));
  }  else {
		if (ComboBox2->Text == "�����") {
	double c = StrToFloat(Edit1->Text);
	Tone (Bmp1, Bmp2, (ComboBox2->Text).c_str(), c);
								  } else {
	Tone (Bmp1, Bmp2, (ComboBox2->Text).c_str());
										 }
									  }
   if (Chart1->Visible)
  {
	Button8 -> Caption = AnsiString("������������");
	Chart1->Visible = false;
   }

  Bmp2>>Image2->Picture->Bitmap;
 Image2->Repaint();
  Button4 -> Enabled = true;
} else
	{
	Edit1->Text = AnsiString("-< ����������� �� ��������� >-");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{  //������ ��������� ����������
  if (Bmp1.GetLength() > 9) {
  void gettime(struct time *timep);
  struct time time1,time2;
  gettime(&time1);

 // pTempImage->Assign(Image1->Picture->Bitmap);

  Bmp2.SetRes(Bmp1.GetWidth(),Bmp1.GetHeight());
  if ((ComboBox1->Text == "�����")||(ComboBox1->Text == "��������")||(ComboBox1->Text == ""))
  {
  int a= Edit1->Text.ToInt();
  Edit1->Text = IntToStr(a+2);

  Filter(Bmp1,Bmp2,(ComboBox1->Text).c_str(),a);
  } else {
 Filter(Bmp1,Bmp2,(ComboBox1->Text).c_str());

   byte red1=Bmp2(50,50).r; byte gren1=Bmp2(50,50).g; byte blue1=Bmp2(50,50).b;
  Edit1->Text = "r-" + IntToStr(int(red1)) + "; g-" + AnsiString(int(gren1)) + "; b-" + AnsiString(int(blue1));
 }
 gettime(&time2);
 unsigned int Dtime;
 Dtime = time2.ti_hund-time1.ti_hund + (((time2.ti_hour-time1.ti_hour)*60+time2.ti_min-time1.ti_min)*60+time2.ti_sec-time1.ti_sec)*100;
 Button4 -> Caption = "Ok - " + IntToStr(Dtime)+".";//+IntToStr(time2.ti_hund-time1.ti_hund);

 Bmp2>>Image2->Picture->Bitmap;
 Image2->Repaint();

  Label1->Caption = "������ ������� - " + AnsiString(Bmp2.GetLength());

 Bmp2>>Image2->Picture->Bitmap;
  // ����� else
  Button4 -> Enabled = true;
  Button4 -> SetFocus();
  } else
	{
	Edit1->Text = AnsiString("-< ����������� �� ��������� >-");
	}
 }
//----------------------
void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
// �����
  if (ComboBox1->Text == "�����")
  {
  Edit1->Text = "������� ������ �����������";
  } else {
  Edit1->Text = ComboBox1->Text;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ComboBox2Change(TObject *Sender)
{ //�����
if (ComboBox2->Text != "����������")
  {
  //Edit1->Text = "��������� �������� �����";
  if (!Chart1->Visible)  {
  char ton[256];
  //Chart1->Title->Text-> = "srgtrtr";
  Chart1->Visible = true;

   Chart1->Title->Text->Clear();
   Chart1->Title->Text->Add("��������������");
   Chart1->Legend->Visible = false;
   Chart1->LeftAxis->Automatic = true ;
   Chart1->BottomAxis->Automatic = true;

   Series1->Clear();
   Series2->Clear();
   Series3->Clear();
   unsigned char b = 0;
  for (int a = 0; a <= 255; a++) {
	if (ComboBox2->Text == "�������") {
	b = 255 - a;
	}
	if (ComboBox2->Text == "��������") {
	b = 256*log(a/256.0+1)/log(2);
	}
	if (ComboBox2->Text == "����������") {
	b = 256*(exp(a/256.0)-1)/(M_E - 1);
	}
	if (ComboBox2->Text == "�����") {
	double c = StrToFloat(Edit1->Text);
	b = 256*pow(a/256.0, c);
	}
   Series2->AddXY(a, b, "", clBlack );
		 }



  Button8 -> Caption = AnsiString("������");
  }
  } else {
  Edit1->Text = ComboBox2->Text;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{ //������ ��������� ����������
if (Bmp1.GetLength() > 9) {
  void gettime(struct time *timep);
  struct time time1,time2;
  gettime(&time1);

  //Button1Click(Sender);   //sfewsfwe

  Bmp2.SetRes(Bmp1.GetWidth(),Bmp1.GetHeight());
  int a= StrToInt(Edit1->Text);    //StrToInt
  // if (true) {
	  Filter(Bmp1,Bmp2,"�������",a);
   //}

  gettime(&time2);
 unsigned int Dtime;
 Dtime = time2.ti_hund-time1.ti_hund + (((time2.ti_hour-time1.ti_hour)*60+time2.ti_min-time1.ti_min)*60+time2.ti_sec-time1.ti_sec)*100;
 Button4 -> Caption = "Ok - " + IntToStr(Dtime)+".";//+IntToStr(time2.ti_hund-time1.ti_hund);

 Bmp2>>Image2->Picture->Bitmap;
 Image2->Repaint();

  Button4 -> Enabled = true;
  } else
	{
	Edit1->Text = AnsiString("-< ����������� �� ��������� >-");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{  //������ ��������� �����
 if (Bmp1.GetLength() > 9) {
  void gettime(struct time *timep);
  struct time time1,time2;
  gettime(&time1);

  int sig = StrToInt(Edit2->Text);
  int Th = StrToInt(Edit3->Text);
  int Tl;
  int a=1;
  if ((Edit1->Text==2)||(Edit1->Text==3)||(Edit1->Text==4)||(Edit1->Text==5)) {
	 a = Edit1->Text.ToInt();
  }
  Bmp2.SetRes(Bmp1.GetWidth(),Bmp1.GetHeight());
  Kont.SetRes(Bmp1.GetWidth(),Bmp1.GetHeight());
 // Canny
  //Bmp1.SetColorModel(ubmGray);
  MakeGrayIm (Bmp1);
  CannyF(Bmp1,Bmp2,Kont,sig, Th,Tl,a);

Bmp2>>Image2->Picture->Bitmap;
 Image2->Repaint();
  Label1->Caption = "������ ������� - " + AnsiString(Bmp2.GetLength());



  gettime(&time2);
 unsigned int Dtime;
 Dtime = time2.ti_hund-time1.ti_hund + (((time2.ti_hour-time1.ti_hour)*60+time2.ti_min-time1.ti_min)*60+time2.ti_sec-time1.ti_sec)*100;
 Button4 -> Caption = "Ok - " + IntToStr(Dtime)+".";//+IntToStr(time2.ti_hund-time1.ti_hund);

 Bmp2>>Image2->Picture->Bitmap;
 Image2->Repaint();

  Button4 -> Enabled = true;
  } else
	{
	Edit1->Text = AnsiString("-< ����������� �� ��������� >-");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image2DblClick(TObject *Sender)
{
//     ��������
if (Im2trig[0]&&Im2trig[1]) {   //��������� ��������
  Im2trig[1] = false;  Im2trig[0] = false;     }
 if (1-Im2trig[0]&&Im2trig[1]) {
  Im2trig[0] = true;

 Bmp2>>Image2->Picture->Bitmap;
   Image2->Repaint();
   Edit1->Text = "�����������" ;
 }
 //-----------------------------------------------------------------------
  if (1-Im2trig[0]&&1-Im2trig[1]) {
  if (Kont.GetLength() > 9) {
  Im2trig[1] = true;

 Kont>>Image2->Picture->Bitmap;
   Image2->Repaint();
 byte red1=Kont(50,50).r; byte gren1=Kont(50,50).g; byte blue1=Kont(50,50).b;
  Edit1->Text = "������  r-" + IntToStr(int(red1)) + "; g-" + IntToStr(int(gren1)) + "; b-" + IntToStr(int(blue1));
   }
   }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button8Click(TObject *Sender)
{ // ����������� ������������
   if (Bmp1.GetLength() > 9) {


	if (!Chart1->Visible)  {
	Chart1->Visible = true;
   Chart1->Legend->Visible = true;
   Chart1->Title->Text->Clear();
   Chart1->Title->Text->Add("������������");
   Chart1->LeftAxis->Automatic = true ;
   Chart1->BottomAxis->Automatic = true;

   Series1->Clear();
   Series2->Clear();
   Series3->Clear();  //�������� ������ ������������
	vector<int> SumG;
	MakeGistr (Bmp1, "Red", SumG);
  for (int b = 0; b <= 255; b++) {
   Series1->AddXY(b, SumG[b], "", clTeeColor );
		 }
	MakeGistr (Bmp1, "Green", SumG);
  for (int b = 0; b <= 255; b++) {
   Series2->AddXY(b, SumG[b], "", clTeeColor );
		 }
	MakeGistr (Bmp1, "Blue", SumG);
  for (int b = 0; b <= 255; b++) {
   Series3->AddXY(b, SumG[b], "", clTeeColor );
		 }

   UColorT min1, max1;
   Bmp1.FindColorRange (min1, max1);
   Edit1->Text = "min- (" + IntToStr(int(min1.r))+";"+IntToStr(int(min1.b))+";"+IntToStr(int(min1.g))+")  max- ("+IntToStr(int(max1.r))+";"+IntToStr(int(max1.b))+";"+IntToStr(int(max1.g))+")";

   Button8 -> Caption = AnsiString("������");

			   } else {
   if (Chart1->Visible)
  {
	Button8 -> Caption = AnsiString("������������");
	Chart1->Visible = false;
   }   }
	 //*/
   } else
	{
	Edit1->Text = AnsiString("-< ����������� �� ��������� >-");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{  //������ �����������
if (Bmp1.GetLength() > 9) {

	Bmp2.SetRes(Bmp1.GetWidth(),Bmp1.GetHeight());
	Bmp2=Bmp1;
	UColorT Black, White, Bin;
	 Black.r=0; Black.g=0; Black.b=0;
	White.r=255; White.g=255; White.b=255;
	if (Edit1->Text == "") {
	   Bmp1.Binarization(White, Black);
	}  else {
	  int h= StrToInt(Edit1->Text);
	  Bin.r=h; Bin.g=h; Bin.b=h;
      Bmp1.Binarization(Bin, White, Black);
	}

	Bmp1>>Image1->Picture->Bitmap;
	Image1->Repaint();

    Button4 -> Enabled = true;
	Button4 -> SetFocus();

  } else
	{
	Edit1->Text = AnsiString("-< ����������� �� ��������� >-");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{ // ������ ��������������� ��������
if (Bmp1.GetLength() > 9) {

  void gettime(struct time *timep);
  struct time time1,time2;
  gettime(&time1);

  Bmp2.SetRes(Bmp1.GetWidth(),Bmp1.GetHeight());
  bool Col = (CheckBox1->Checked);
  UColorT Black;
  Black.r=255*Col; Black.g=0; Black.b=0;
   //Bmp2.Fill(Black);

if (ComboBox3->Text == "�����������")
  {
   FilterMorfP(Bmp1, Bmp2, (ComboBox4->Text).c_str(), Col, 3);
  } else {
if (ComboBox3->Text == "������")
  {
   FilterMorfM(Bmp1, Bmp2, (ComboBox4->Text).c_str(), Col, 3);
  } else {
if (ComboBox3->Text == "���������")
  {
   FilterMorfP(Bmp1, Bmp2, (ComboBox4->Text).c_str(), Col, 3);
   Bmp1=Bmp2;
   Bmp1>>Image1->Picture->Bitmap;
   Image1->Repaint();

   FilterMorfM(Bmp1, Bmp2, (ComboBox4->Text).c_str(), Col, 3);
  } else {
if (ComboBox3->Text == "����������")
  {
   FilterMorfM(Bmp1, Bmp2, (ComboBox4->Text).c_str(), Col, 3);
   Bmp1=Bmp2;
   FilterMorfP(Bmp1, Bmp2, (ComboBox4->Text).c_str(), Col, 3);
  } else {
   if (ComboBox3->Text == "��������")
  {
   FilterMorfP(Bmp1, Bmp2, "�������", Col, 3);
   Bmp1=Bmp2;
   FilterMorfP(Bmp1, Bmp2, "����-3", !Col, 3);
  } else {

  if (Col) {
   FillColor(Bmp1, (ComboBox3->Text).c_str(), 0);
   Bmp1>>Image1->Picture->Bitmap;
   Image1->Repaint();
  } else {
   FillColor(Bmp2, (ComboBox3->Text).c_str(), 0);
	 }  }  }  }  }  }
  gettime(&time2);
 unsigned int Dtime;
 Dtime = time2.ti_hund-time1.ti_hund + (((time2.ti_hour-time1.ti_hour)*60+time2.ti_min-time1.ti_min)*60+time2.ti_sec-time1.ti_sec)*100;
 Button4 -> Caption = "Ok - " + IntToStr(Dtime)+".";

  Bmp2>>Image2->Picture->Bitmap;
 Image2->Repaint();

  } else
	{
	Edit1->Text = AnsiString("-< ����������� �� ��������� >-");
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button11Click(TObject *Sender)
{// ������ ��������� ����������
  if (Bmp1.GetLength() > 9) {

  Bmp2.SetRes(Bmp1.GetWidth(),Bmp1.GetHeight());
  bool Col = (CheckBox1->Checked);
  int nmark = 10;
  Markir (Bmp1, Bmp2, nmark, Col);
   //Bmp2.Looping(,Bmp1);
  Edit1->Text = "������� �������� - " + IntToStr(nmark);


   Bmp2>>Image2->Picture->Bitmap;
 Image2->Repaint();

  } else
	{
	Edit1->Text = AnsiString("-< ����������� �� ��������� >-");
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button12Click(TObject *Sender)
{ // ������ ��������� ���������� �������
  if (Bmp1.GetLength() > 9) {

   void gettime(struct time *timep);
   struct time time1,time2;
   gettime(&time1);

   char Ogib = 1;
   int minY = Bmp1.GetHeight()/10;
   while (Bmp1(Bmp1.GetWidth()/2, minY).r != 0)
   {  minY++;  }  //*/

   if (ComboBox5->Text == "�������")
   {
   while ((Ogib > 0)&&(minY >= 0))
   {
   KontyrP (Bmp1, KPoint1.Xp1, KPoint1.Yp1, KPoint1.Napr1, Ogib, minY);
   minY--;
   }
   //KontyrP (Bmp1, KPoint1.Xp1, KPoint1.Yp1, Ogib, minY);
   GetKontType (KPoint1.Xp1, KPoint1.Yp1, KPoint1.Type1);
   }
   if (ComboBox5->Text == "������")
   {
   KontyrV (Bmp1, KPoint1.Xp1, KPoint1.Yp1, Ogib);
   }
   if (ComboBox5->Text == "���������")
   {
   GetKontType (KPoint1.Xp1, KPoint1.Yp1, KPoint1.Type1);
   }

   gettime(&time2);
  unsigned int Dtime;
  Dtime = time2.ti_hund-time1.ti_hund + (((time2.ti_hour-time1.ti_hour)*60+time2.ti_min-time1.ti_min)*60+time2.ti_sec-time1.ti_sec)*100;
  Button4 -> Caption = "Ok - " + IntToStr(Dtime)+".";


	if (!Chart1->Visible)  {
  Chart1->Visible = true;

   Chart1->Title->Text->Clear();
   Chart1->Title->Text->Add("������");
   Chart1->Legend->Visible = false;
   Chart1->LeftAxis->Automatic = false ;
   Chart1->BottomAxis->Automatic = false;
   Chart1->LeftAxis->Minimum = -10;
   Chart1->LeftAxis->Maximum = Bmp1.GetHeight()+10;
   Chart1->BottomAxis->Minimum = -10;
   Chart1->BottomAxis->Maximum = Bmp1.GetWidth()+10;
					 //*/
   Series1->Clear();
   Series2->Clear();
   Series3->Clear();

   //ShowMessage (KPoint1.Xp1.size());                    //clBlack
 for(int i=0;i<KPoint1.Xp1.size();i++)
	{
	//ShowMessage (IntToStr(i));
   sleep(0.01);
   if ((KPoint1.Type1.size() > 0)&&(KPoint1.Type1[i] != 1)) {
	 if (KPoint1.Type1[i] == 2)
		{  Series2->AddXY(KPoint1.Xp1[i], KPoint1.Yp1[i], "", clYellow ); }
	 if (KPoint1.Type1[i] == 3)
    	{  Series2->AddXY(KPoint1.Xp1[i], KPoint1.Yp1[i], "", clRed ); }

   } else {
   Series2->AddXY(KPoint1.Xp1[i], KPoint1.Yp1[i], "", clGreen );
		  }
   if (i%100 == 0) {
   Chart1->Repaint();  }
	}

	Button8 -> Caption = AnsiString("������");
	}
 //  Kontyr (Bmp1, Xp1, Yp1);

   Bmp1>>Image1->Picture->Bitmap;
 Image1->Repaint();
   if (KPoint1.Xp1.size() > 0) {
   Edit1->Text = IntToStr(KPoint1.Xp1[0]) +";"+ KPoint1.Yp1[0] +", �����: "+IntToStr(KPoint1.Xp1.size())+" ����- "+IntToStr(Ogib)+" min- "+IntToStr(minY);
                       }
  } else
	{
	Edit1->Text = AnsiString("-< ����������� �� ��������� >-");
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button13Click(TObject *Sender)
{  //������ ������ ������� � ��������� ����

   if (KPoint1.Xp1.size() > 0) {

   FILE *out;     /*
   if ((out = fopen("TestFile.txt", "w+"))
	   == NULL)
   {
	  ShowMessage ("Cannot open output file.");
   }     //*/

   AnsiString path = ExtractFileDir(Application->ExeName); //��������� �������� ������� ���������
   AnsiString strf = path + "\\TestFile.txt" ;
	// AnsiString(GetCurrentDir() + "\\TestFile.txt")
   out = fopen( strf.c_str(), "w+"); //"D:\\University\\���\\kater.bmp"
fprintf(out, "������ �������.\n");
fprintf(out, ("������� �����: "+ IntToStr(KPoint1.Xp1.size()) +"\n").c_str());
   for(size_t i2=0;i2<KPoint1.Xp1.size();i2++)
   {
fprintf(out, ( IntToStr(KPoint1.Xp1[i2])+ "; � "+KPoint1.Yp1[i2]+"; "+IntToStr(KPoint1.Napr1[i2])+"\n").c_str() );
   }        //*/
  //    fputc(msg[i], out);
   fclose(out);

   }  else {
	MessageBeep(-1);
	Edit1->Text = AnsiString("-< �� �������� �� ����� ����� >-");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button14Click(TObject *Sender)
{ //������ ������ ���������
if (Bmp1.GetLength() > 9) {

 //MessageBeep(-1);
//------------------------------------------------
//     ������� �������������
 ComboBox2->Text = "����������";
 Button5Click(Sender);   //  ����������  //-------------------

  unsigned char Intens;
  double c;
  PolAreaN (Bmp1, Intens);
c = log(0.5)/log(Intens/256.0);  // �������� ��� ������������ ������������
c = sqrt (c);    // �������� �������� c
Edit1->Text = AnsiString(c);
 ComboBox2->Text = "�����";
 Button5Click(Sender);                        // ������ Tone
 ShowMessage ("������� �������������");
 //sleep(0.2);
 Button4Click(Sender);  // OK

//----------------------------------------
//       �������
  ComboBox1->Text = "�����-3";
  Button2Click(Sender);   // ������ ����������
  ShowMessage ("������ ������");
  //sleep(0.2);
  Button4Click(Sender);  //*/// OK
//-------------------------------------
//      ���������� �����
 short int Pmax = 4; //Pmin = 0;
 int Npoint =0 , hh=0;
 vector<int> SumG2;
 UColorT Black;
  Black.r = Black.g = Black.b = 0;
 int Area[4]= {0,0,1,1};
 Area[2]= Bmp1.GetWidth();
 Area[3]= Bmp1.GetHeight();
 Edit1->Text = AnsiString(2);
 Edit3->Text = AnsiString(Pmax);

 Button7Click(Sender);   // ������ �����
 MakeGistr (Bmp2, "Red", SumG2);
 Npoint = SumG2[128] + SumG2[255];    // ��������� ������

 while ((Npoint >= (Bmp2.GetLength())*0.05)&&(++hh < 30))
 {
  Pmax += 5;
  int sig = StrToInt(Edit2->Text);
  int Tl; bool N;
 Bmp2.Fill(Black);
 Detect(Bmp2, Kont, Pmax, Tl, Area);

 Bmp2>>Image2->Picture->Bitmap;
 Image2->Repaint();
 MakeGistr (Bmp2, "Red", SumG2);
 Npoint = SumG2[128] + SumG2[255];    // ��������� ������
 }   //*/
 //MessageBeep(-1);
 while (( Npoint < (Bmp2.GetLength())*0.05)&&(++hh < 30))
 {
 Pmax-- ;

  int Tl;
	/*
 int sig = StrToInt(Edit2->Text);
  int a=1;
bool N;
Filter(Bmp1, Bmp2, "�����", sig, a);  //  /  Bmp2=Bmp1;
Roberts(Bmp2, Kont, N);
Suppress(Bmp2, Kont, N); // */
Detect(Bmp2, Kont, Pmax, Tl, Area);

Bmp2>>Image2->Picture->Bitmap;
 Image2->Repaint();                // ������ �����

 MakeGistr (Bmp2, "Red", SumG2);
 Npoint = SumG2[128] + SumG2[255];    // ��������� ������
 //ShowMessage ("������ �����");
 }

 Pmax++ ;
 int Tl;
 Bmp2.Fill(Black);
 Detect(Bmp2, Kont, Pmax, Tl, Area);
 Bmp2>>Image2->Picture->Bitmap;
 Image2->Repaint();                // ������ �����
   //*/

 Edit3->Text = AnsiString(Pmax);
 ShowMessage ("������ �����");
 //sleep(0.2);
 Button4Click(Sender);  // OK
		//*/
//--------------------------------------
//      ����������
  ComboBox3->Text = "�����������";
  ComboBox4->Text = "�������";
  Button10Click(Sender);            // ������ ����������
  Button4Click(Sender);  // OK

  ComboBox3->Text = "�����������";
  ComboBox4->Text = "����-3";
  CheckBox1->Checked = true;
  Button10Click(Sender);            // ������ ����������
  CheckBox1->Checked = false;
  ComboBox4->Text = "�������";
  ShowMessage ("���������");
  //sleep(0.2);
  Button4Click(Sender);  // OK
//--------------------------------------
//      �������� ����� ��������

   int nmark = 300;
   while (nmark > 255)
	{
	nmark = 10;
	Markir (Bmp1, Bmp2, nmark, false);

   Bmp2>>Image2->Picture->Bitmap;
   Image2->Repaint();

   //Button11Click(Sender);            // ������ ����������
   Button4Click(Sender);  // OK
   short int NumD = (Bmp1.GetWidth()+Bmp1.GetHeight())/7;
   ShowMessage ("����������");
   //sleep(0.2);
   Edit1->Text = AnsiString(NumD);
   Button15Click(Sender);            // ������ ������� ����� ��������
   Bmp2 = Bmp1;
	   }
//--------------------------------------
//      ���������� ������

   unsigned char ColK;
   //bool AP;
   int ht=0, NumArea = 1;
   int NumPointK1 = 0, NumPointK2 = 200;
   Pmax /= 2;
   //int Tl;
   int pn;

	 //*

   while ((((NumPointK2- NumPointK1) > 50)||((NumPointK1- NumPointK2) > 50))&&(NumArea > 0)&&(ht++ < 10))
	   {      //������� ����
   NumArea = 0;

   ComboBox3->Text = "��������";
  Button10Click(Sender);            // ������ ����������
  Button4Click(Sender);  //* /// OK

	nmark = 10;
	Markir (Bmp1, Bmp2, nmark, false);
   Button4Click(Sender);  // OK


   ComboBox5->Text = "�������";
   NumPointK2 = NumPointK1;
   Button12Click(Sender);   // ������ ����������� �������
   NumPointK1 = KPoint1.Xp1.size();

   ShowMessage ("������");
   //sleep(0.2);
	Button8Click(Sender);   // ������ ������

	if (((NumPointK2- NumPointK1) > 100)||((NumPointK1- NumPointK2) > 100)) {
	 int pn=0;      //������� ����� ��� ������ �������
	 AP = true;
   while (AP) {

	 unsigned char ColK = 0;
   getColorK (Bmp1, KPoint1.Xp1, KPoint1.Yp1, ColK);
   if (ColK == 0) {
   ShowMessage ("������������ ����");
   }
   int Area[4]= {0,0,0,0};
   AP = false;  short int Pmax;
   ProslK (Bmp1, KPoint1.Xp1, KPoint1.Yp1, KPoint1.Type1, Area, ColK, pn, AP);
   if (AP) {
   // ��������� �������������� ���������
  Pmax = StrToInt(Edit3->Text);  Pmax /= 2;
  Detect(Bmp2, Kont, Pmax, Tl, Area);    //���������� ����� ������
  Bmp2>>Image2->Picture->Bitmap;
  Image2->Repaint();   }            //*/

	 //Button17Click(Sender);   // ������ ����������� ������� �������
	 //ShowMessage ("������");
	 NumArea++;
		 }
   NumArea--;
   Button4Click(Sender);  // OK
		 }  }      //������� ����

		 Button12Click(Sender);   // ������ ����������� �������

	ShowMessage ("������ ������");
	//sleep(0.2);
	Button8Click(Sender);   // ������ ������
		 //*/
//------------------------------------
//      ��������� ���������� �����

 //SmalKont (KPoint1.Xp1, KPoint1.Yp1, KPoint1.Napr1, KPoint1.Type1);

 Button18Click(Sender);   // ������ �������������� ������� � ���


//-------------   END
//Button4Click(Sender);  // OK
//ShowMessage ("���������: " + IntToStr(numIt));
//-------------

} else
	{
	MessageBeep(-1);
	Edit1->Text = AnsiString("-< ����������� �� ��������� >-");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button15Click(TObject *Sender)
{ // ������ �������� ����� ��������

  void gettime(struct time *timep);
   struct time time1,time2;
   gettime(&time1);

  vector <smark> konp;
  konp.resize(256);
  short int H = 0;
 H = StrToInt(Edit1->Text);
 KontMark (Bmp1, konp);
 ErSmall (Bmp1, konp, H);

 Bmp1>>Image1->Picture->Bitmap;
 Image1->Repaint();



 gettime(&time2);
  unsigned int Dtime;
  Dtime = time2.ti_hund-time1.ti_hund + (((time2.ti_hour-time1.ti_hour)*60+time2.ti_min-time1.ti_min)*60+time2.ti_sec-time1.ti_sec)*100;
  Button4 -> Caption = "Ok - " + IntToStr(Dtime)+".";


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button16Click(TObject *Sender)
{ // ������ ���������� ������� � ����.
  if (Chart1->Visible) {

// ��������� ����������� ������� � jpeg
/*bool TWatchFrame::SaveToJpeg(const AnsiString &filename)
{  //*/
 //if(filename == "")
  //return false;
 //TJPEGImage *jpg=new TJPEGImage;
 Chart1->SaveToBitmapFile("GrafImeg.bmp");
 //Chart1->CopyToClipboardBitmap();
// jpg->LoadFromClipboardFormat();
 //jpg->Assign(Chart1->BackImage->Bitmap);
 //jpg->SaveToFile("GrafImeg.jpg");
 //jpg->SaveToFile(SaveDialog->FileName);
 /* TMemoryStream *stream=new TMemoryStream;

 stream->SetSize(Chart->Cop

 delete stream;*/
 //delete jpg;
  /*
// ��������� ����������� ������� � bmp
bool TWatchFrame::SaveToBitmap(const AnsiString &filename)
{
 if(filename == "")
  return false;

 Chart1->SaveToBitmapFile(filename);
 return true;
}


 //*/
 } else {
	MessageBeep(-1);
	Edit1->Text = AnsiString("-< ������ �� ������ >-");
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button17Click(TObject *Sender)
{ // ������ ����������� ������� �������

   if (KPoint1.Xp1.size() > 0) {
   if (Kont.GetLength() > 9 ) {


   void gettime(struct time *timep);
   struct time time1,time2;
   gettime(&time1);

   unsigned char ColK = 0;
   getColorK (Bmp1, KPoint1.Xp1, KPoint1.Yp1, ColK);
   if (ColK == 0) {
   ShowMessage ("������������ ����");
   }
   int Area[4]= {0,0,0,0};
   int pn=0;
   AP = false;  short int Pmax;

   ProslK (Bmp1, KPoint1.Xp1, KPoint1.Yp1, KPoint1.Type1, Area, ColK, pn, AP);
   if (AP) {
   // ��������� �������������� ���������

  Pmax = StrToInt(Edit3->Text);  Pmax /= 2;  int Tl;

  Detect(Bmp2, Kont, Pmax, Tl, Area);    //���������� ����� ������

  Bmp2>>Image2->Picture->Bitmap;
  Image2->Repaint();


   Edit1->Text = "������� - (" + IntToStr(Area[0])+","+IntToStr(Area[1])+";"+IntToStr(Area[2])+","+IntToStr(Area[3])+") "+IntToStr(pn);




   } else {  Edit1->Text = "����� ������� �� ����������";  }

   gettime(&time2);
   unsigned int Dtime;
   Dtime = time2.ti_hund-time1.ti_hund + (((time2.ti_hour-time1.ti_hour)*60+time2.ti_min-time1.ti_min)*60+time2.ti_sec-time1.ti_sec)*100;
   Button4 -> Caption = "Ok - " + IntToStr(Dtime)+".";

   } else {
   MessageBeep(-1);
   Edit1->Text = "������� �� �������";  }
   }  else {
	MessageBeep(-1);
	Edit1->Text = AnsiString("-< �� �������� �� ����� ����� >-");
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button18Click(TObject *Sender)
{  //������ �������������� ������� � ���������
  if (KPoint1.Xp1.size() > 0) {
   vector<int> Xd1, Yd1;
   int h = Bmp1.GetHeight(), w = Bmp1.GetWidth();
   PreobrGor (KPoint1.Xp1, KPoint1.Yp1 , Xd1, Yd1, h, w);




   if (!Chart1->Visible)  {
   Chart1->Visible = true;

   Chart1->Title->Text->Clear();
   Chart1->Title->Text->Add("��������");
   Chart1->Legend->Visible = false;
   Chart1->LeftAxis->Automatic = false ;
   Chart1->BottomAxis->Automatic = false;
   Chart1->LeftAxis->Minimum = -10;
   Chart1->LeftAxis->Maximum = h+10;
   Chart1->BottomAxis->Minimum = -10;
   Chart1->BottomAxis->Maximum = w+10;
					 //*/
   Series1->Clear();
   Series2->Clear();
   Series3->Clear();

   //ShowMessage (KPoint1.Xp1.size());                    //clBlack
 for(int i=0;i<Xd1.size();i++)
	{
	//ShowMessage (IntToStr(i));
   if ((KPoint1.Type1.size() > 0)&&(KPoint1.Type1[i] != 1)) {
	 if (KPoint1.Type1[i] == 2)
		{  Series2->AddXY(Xd1[i], Yd1[i], "", clYellow ); }
	 if (KPoint1.Type1[i] == 3)
		{  Series2->AddXY(Xd1[i], Yd1[i], "", clRed ); }
   } else {
   Series2->AddXY(Xd1[i], Yd1[i], "", clGreen );
		  }
	}

	Button8 -> Caption = AnsiString("������");
	}



   }  else {
	MessageBeep(-1);
	Edit1->Text = AnsiString("-< �� �������� �� ����� ����� >-");
	}
}
//---------------------------------------------------------------------------


