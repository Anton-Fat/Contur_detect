//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GraphFrameUnit.h"
#include "ListInputFormUnit.h"
#include "SeriesControlUnit.h"
#include "ShowProgressBarUnit.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWatchFrame *WatchFrame;

//---------------------------------------------------------------------------
/*
   ������ ������ OutGateWatchData
*/
//---------------------------------------------------------------------------
OutGateWatchData::OutGateWatchData(void)
{
 YShift=0;
 FullUpdate=false;
 WatchInterval=-1;

 SeriesIndex=-1;
 DataSource=0;
 Color=TColor(0);

 X=0;
 Y=0;
 XYSize=0;

 Visible=true;
}

OutGateWatchData::~OutGateWatchData(void)
{
}

OutGateWatchData::OutGateWatchData(const OutGateWatchData &wd)
{
 YShift=wd.YShift;
 Color=wd.Color;
 Legend=wd.Legend;
 X=wd.X;
 Y=wd.Y;
 XYSize=wd.XYSize;
 FullUpdate=wd.FullUpdate;
 WatchInterval=wd.WatchInterval;
 SeriesIndex=wd.SeriesIndex;
 DataSource=wd.DataSource;

 Visible=wd.Visible;
}

OutGateWatchData& OutGateWatchData::operator = (const OutGateWatchData& wd)
{
 YShift=wd.YShift;
 Color=wd.Color;
 Legend=wd.Legend;
 X=wd.X;
 Y=wd.Y;
 XYSize=wd.XYSize;
 FullUpdate=wd.FullUpdate;
 WatchInterval=wd.WatchInterval;
 SeriesIndex=wd.SeriesIndex;
 DataSource=wd.DataSource;
 Visible=wd.Visible;
 return *this;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
__fastcall TWatchFrame::TWatchFrame(TComponent* Owner)
        : TFrame(Owner)
{
 ModifyState=false;
 Chart1->BufferedDisplay=true;
}

__fastcall TWatchFrame::~TWatchFrame(void)
{
 Clear();
} 
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// ������
// ------------------------------
// ������ ���������� ����������
// ------------------------------
// ���������� 'true', ���� ������ � ������ ���� ��������,
// ��� ���� ����� ���� ���������/�������
bool __fastcall TWatchFrame::GetModifyState(void)
{
 if(ModifyState)
  {
   ModifyState=false;
   return true;
  }

 return false;
}


// �������� ���������� �� �������� ������ � ���� 'watchname'
// ���� 'collectstate' == 'true', �� ��������� ����� ����������� ����������
bool __fastcall TWatchFrame::CollectInfo(string watchname, bool collectstate)
{
 TMemIniFile *ini;
 char *out=0;
 int len;
 char buffer[32];
 string *sp;

 if(NameList.size() == 0)
  return true;

 ini=new TMemIniFile(watchname.c_str());
 if(!ini)
  return false;

 ini->Clear();

 String s=ShowProgressBarForm->GetBarHeader(1);
 ShowProgressBarForm->ResetBarStatus(1,0,NameList.size());

 // ��������� �� ������ ���� �������� �����
 for(int seriesindex=0;seriesindex<(int)NameList.size();seriesindex++)
  {
   ShowProgressBarForm->SetBarHeader(1,s+" - "+NameList[seriesindex].Legend.c_str()+":");

   ini->WriteString(IntToStr(seriesindex),"Legend",NameList[seriesindex].Legend.c_str());
   ini->WriteString(IntToStr(seriesindex),"YShift",FloatToStr(NameList[seriesindex].YShift));
   ini->WriteString(IntToStr(seriesindex),"Color",IntToStr(NameList[seriesindex].Color));

   if(collectstate)
	{
	 delete[] out;
	 out=new char[31*Chart1->Series[seriesindex]->Count()+1];
	 *out='\0';
	 len=0;
	 for(int k=0;k<Chart1->Series[seriesindex]->Count();k++)
	 {
	  *buffer='\0';
	  sprintf(buffer,"%f|",Chart1->Series[seriesindex]->XValue[k]);
	  memcpy(out+len,buffer,strlen(buffer));
	  len+=strlen(buffer);
	 }
	 out[len]='\0';
	 ini->WriteString(IntToStr(seriesindex),"XDATA",out);

	 *out='\0';
	 len=0;
	 for(int k=0;k<Chart1->Series[seriesindex]->Count();k++)
	 {
	  *buffer='\0';
	  sprintf(buffer,"%f|",Chart1->Series[seriesindex]->YValue[k]);
	  memcpy(out+len,buffer,strlen(buffer));
	  len+=strlen(buffer);
	 }
	 out[len]='\0';
	 ini->WriteString(IntToStr(seriesindex),"YDATA",out);
	}

   ShowProgressBarForm->IncBarStatus(1);
  }

 ini->UpdateFile();
 delete ini;
 ModifyState=false;
 return true;
}

// ��������������� ����� �� ���������� �� ����� 'watchname'
// ���� 'collectstate' == 'true', �� ��������������� ����� �����������
// ����������
// (��� �������� ���������� ����� �������������� �������)
bool __fastcall TWatchFrame::RestoreInfo(string watchname, bool collectstate)
{
 map<string,OutGateWatchData*>::iterator I;
 TMemIniFile *ini;
 TStringList *series;
 OutGateWatchData *wd;
 TFastLineSeries *grseries;
 string xs,ys;
 float x,y;
 string::size_type ix1,ix2,iy1,iy2;

 ini=new TMemIniFile(watchname.c_str());
 if(!ini)
  return false;

 Clear();

 series=new TStringList;
 ini->ReadSections(series);

 String s=ShowProgressBarForm->GetBarHeader(1);
 ShowProgressBarForm->ResetBarStatus(1,0,series->Count);

 for(int i=0;i<series->Count;i++)
  {
   ShowProgressBarForm->SetBarHeader(1,s+" - "+series->Strings[i]+":");

/*   if(!Model->GetOutGate(series->Strings[i].c_str()))
	{
	 ShowProgressBarForm->IncBarStatus(1);
	 continue;
	}*/

   NameList.resize(NameList.size()+1);
   wd=&NameList[NameList.size()-1];
   wd->Legend=ini->ReadString(IntToStr(i),"Legend","").c_str();
   wd->YShift=StrToFloat(ini->ReadString(IntToStr(i),"YShift","0"));
   wd->Color=(TColor)StrToInt(ini->ReadString(IntToStr(i),"Color",IntToStr(clTeeColor)));

   grseries=new TFastLineSeries(Chart1);
   grseries->ParentChart=Chart1;
   grseries->Title=wd->Legend.c_str();
   grseries->ColorSource=wd->Color;
   grseries->SeriesColor=wd->Color;
   if(collectstate)
	{
	 grseries->Clear();
     ix1=0; ix2=0;
     iy1=0; iy2=0;
	 xs=ini->ReadString(IntToStr(i),"XDATA","").c_str();
	 ys=ini->ReadString(IntToStr(i),"YDATA","").c_str();
	 grseries->Active=false;
	 while( ((ix2+1) < xs.size()) && ((ix2=xs.find_first_of('|',ix2+1)) != string::npos) )
	  {
	   if(iy2+1 >= ys.size())
		{
		 grseries->Clear();
		 break;
		}

	   iy2=ys.find_first_of('|',iy2+1);
//       x=StrToFloat(xs.substr(ix1,ix2-ix1).c_str());
//       y=StrToFloat(ys.substr(iy1,iy2-iy1).c_str());
	   x=atof(xs.substr(ix1,ix2-ix1).c_str());
	   y=atof(ys.substr(iy1,iy2-iy1).c_str());
	   grseries->AddXY(x,y,"",wd->Color);
	   ix1=ix2+1;
	   iy1=iy2+1;
	  }
	 grseries->Active=true;
    }

   ShowProgressBarForm->IncBarStatus(1);
  }

 delete series;
 delete ini;
 ModifyState=false;
 return true;
}
// ------------------------------

// ------------------------------
// ������ ��������� �����������
// ------------------------------
// ��������/��������� ������������������� �� ��� X
void __fastcall TWatchFrame::SetXAutoScale(bool value)
{
 if(value)
 {
  Chart1->TopAxis->Automatic=true;
  Chart1->BottomAxis->Automatic=true;
 }
 else
 {
  Chart1->TopAxis->Automatic=false;
  Chart1->BottomAxis->Automatic=false;
 }
}

// ���������� ��������� ������������������� �� ��� X
bool __fastcall TWatchFrame::GetXAutoScale(void)
{
 return Chart1->TopAxis->Automatic;
}

// ��������/��������� ������������������� �� ��� Y
void __fastcall TWatchFrame::SetYAutoScale(bool value)
{
 if(value)
 {
  Chart1->LeftAxis->Automatic=true;
  Chart1->RightAxis->Automatic=true;
 }
 else
 {
  Chart1->LeftAxis->Automatic=false;
  Chart1->RightAxis->Automatic=false;
 }
}

// ���������� ��������� ������������������� �� ��� Y
bool __fastcall TWatchFrame::GetYAutoScale(void)
{
 return Chart1->LeftAxis->Automatic;
}

// ������������� ������� ��������� �� ��� X
void __fastcall TWatchFrame::SetXMin(float value)
{
  Chart1->TopAxis->Minimum=value;
  Chart1->BottomAxis->Minimum=value;
}

void __fastcall TWatchFrame::SetXMax(float value)
{
  Chart1->TopAxis->Maximum=value;
  Chart1->BottomAxis->Maximum=value;
}

// ������������� ������� ��������� �� ��� Y
void __fastcall TWatchFrame::SetYMin(float value)
{
  Chart1->LeftAxis->Minimum=value;
  Chart1->RightAxis->Minimum=value;
}

void __fastcall TWatchFrame::SetYMax(float value)
{
  Chart1->LeftAxis->Maximum=value;
  Chart1->RightAxis->Maximum=value;
}

// ���������� ������� ��������� �� ��� X
float __fastcall TWatchFrame::GetXMin(void)
{
 return Chart1->TopAxis->Minimum;
}

float __fastcall TWatchFrame::GetXMax(void)
{
 return Chart1->TopAxis->Maximum;
}

// ���������� ������� ��������� �� ��� Y
float __fastcall TWatchFrame::GetYMin(void)
{
 return Chart1->LeftAxis->Minimum;
}

float __fastcall TWatchFrame::GetYMax(void)
{
 return Chart1->LeftAxis->Maximum;
}

// ������������� ��������� �������
void __fastcall TWatchFrame::SetGraphTitle(AnsiString title)
{
 Chart1->Title->Text->Clear();
 Chart1->Title->Text->Add(title);

 if(title.Length() == 0)
  Chart1->Title->Visible=false;
 else
  Chart1->Title->Visible=true;
}

// ������������� ��������� �������� �� ����
void __fastcall TWatchFrame::SetXLabelVisible(bool value)
{
 Chart1->BottomAxis->Labels=value;
}

void __fastcall TWatchFrame::SetYLabelVisible(bool value)
{
 Chart1->LeftAxis->Labels=value;
}

// ���������� ��������� �������� �� ����
bool __fastcall TWatchFrame::GetXLabelVisible(void)
{
 return Chart1->BottomAxis->Labels;
}

bool __fastcall TWatchFrame::GetYLabelVisible(void)
{
 return Chart1->LeftAxis->Labels;
}

// ������������� ������� �� ����
void __fastcall TWatchFrame::SetXLabelTitle(AnsiString value)
{
 Chart1->BottomAxis->Title->Caption=value;
}

void __fastcall TWatchFrame::SetYLabelTitle(AnsiString value)
{
 Chart1->LeftAxis->Title->Caption=value;
}

// ���������� ������� �� ����
AnsiString __fastcall TWatchFrame::GetXLabelTitle(void)
{
 return Chart1->BottomAxis->Title->Caption;
}

AnsiString __fastcall TWatchFrame::GetYLabelTitle(void)
{
 return Chart1->LeftAxis->Title->Caption;
}

// ������������� ��������� �������
void __fastcall TWatchFrame::SetLegendVisible(bool value)
{
 Chart1->Legend->Visible=value;
}

// ���������� ��������� �������
bool __fastcall TWatchFrame::GetLegendVisible(void)
{
 return Chart1->Legend->Visible;
}
// ------------------------------

// ------------------------------
// ������ ���������� ������������
// ------------------------------
// ���������� ������ ����������
OutGateWatchData* __fastcall TWatchFrame::Get(int seriesindex)
{
 if(seriesindex < 0 || seriesindex >= (int)NameList.size())
  return 0;

 return &NameList[seriesindex];
}

OutGateWatchData* __fastcall TWatchFrame::Get(void *datasource)
{
 for(size_t i=0;i<NameList.size();i++)
  if(NameList[i].DataSource == datasource)
   return &NameList[i];

 return 0;
}

// ���������� ����� ����� ������ ����������
int __fastcall TWatchFrame::GetNumWatches(void)
{
 return (int)NameList.size();
}


// ���������� ������ ����������
void __fastcall TWatchFrame::Add(OutGateWatchData& wd)
{
 // ...��� ��������, ���� �� ����� � ����� �������� � 'NameList'
/* I=NameList.begin();
 while(I != NameList.end())
  {
   if(wd->Legend == I->second->Legend)
	return;
   I++;
  }*/


 NameList.resize(NameList.size()+1);
 NameList[NameList.size()-1]=wd;

 // ��������� ����� ������
 TFastLineSeries *ser;

 ser=new TFastLineSeries(Chart1);
 ser->ParentChart=Chart1;
 ser->Title=wd.Legend.c_str();
 ser->ColorSource=wd.Color;
 ser->SeriesColor=wd.Color;

 // ...������� ����� � �����
 StepUpdate();

// AddSeries(NameList.size()-1);

 // ... ��������� ���������...

 ModifyState=true;
}

// �������� ����������
void __fastcall TWatchFrame::Del(int seriesindex)
{
 if(seriesindex >= (int)NameList.size())
  return;
// DelSeries(seriesindex);

 TChartSeries *ser;

 ser=Chart1->Series[seriesindex];
 Chart1->RemoveSeries(ser);
 delete ser;
 // ...... ��������� �������

 vector<OutGateWatchData>::iterator I=NameList.begin();

 I+=seriesindex;
 NameList.erase(I);

 ModifyState=true;
}

// ������� ��� ����������
void __fastcall TWatchFrame::Clear(void)
{
 map<string,OutGateWatchData*>::iterator I;

 if(NameList.size() == 0)
  return;

// ClearSeries();
 TChartSeries *ser;

 for(int i=0;i<Chart1->SeriesCount();)
  {
   ser=Chart1->Series[i];
   Chart1->RemoveSeries(ser);
   delete ser;
   ModifyState=true;
  }

 // ...... ��������� �������
 NameList.clear();

 ModifyState=true;
}

// ��������� ����������� �����
// ������������ ��� ���������� ������
// ���� seriesindex < 0 �� ��������� ��� �����
void __fastcall TWatchFrame::SeriesDisable(int seriesindex)
{
 if(seriesindex >= (int)NameList.size())
  return;

 if(seriesindex<0)
 {
  for(int i=0;i<Chart1->SeriesCount();i++)
   Chart1->Series[i]->Active=false;
 }
 else
  Chart1->Series[seriesindex]->Active=false;
}

// �������� ����������� �����
// ������������ ��� ���������� ������
// ���� seriesindex < 0 �� �������� ��� �����
void __fastcall TWatchFrame::SeriesEnable(int seriesindex)
{
 if(seriesindex >= Chart1->SeriesCount())
  return;

 if(seriesindex<0)
 {
  for(int i=0;i<Chart1->SeriesCount();i++)
   Chart1->Series[i]->Active=true;
 }
 else
  Chart1->Series[seriesindex]->Active=true;
}

// ���������� ������ �����
// ���������� ����� ����� � �����
void __fastcall TWatchFrame::SeriesUpdate(int seriesindex, float x, float y)
{
 if(seriesindex < 0 || seriesindex >= (int)NameList.size())
  return;

 OutGateWatchData *wd;


 // ������������ ���������� � ������
 wd=&NameList[seriesindex];

 if(!wd->Visible)
  return;

 // ������� ������ ���������� ������ ����������...
 if(wd->FullUpdate)
 {
  Chart1->Series[seriesindex]->Clear();
  Chart1->Series[seriesindex]->AddXY(x,y+wd->YShift,"",wd->Color);
 }
 else
 {
  if(wd->WatchInterval == 0)
   return;

  Chart1->Series[seriesindex]->AddXY(x,y+wd->YShift,"",wd->Color);
 }
 ModifyState=true;
}

void __fastcall TWatchFrame::SeriesUpdate(void* datasource, float x, float y)
{
 for(int i=0;i<(int)NameList.size();i++)
  if(NameList[i].DataSource == datasource)
  {
   SeriesUpdate(i,x,y);
   return;
  }
}

// ���������� ������ �����
// ���������� ������� ����� � �����
void __fastcall TWatchFrame::SeriesUpdate(int seriesindex, float* x, float* y, int size)
{
 if(seriesindex < 0 || seriesindex >= (int)NameList.size())
  return;

 OutGateWatchData *wd;

 // ������������ ���������� � ������
 wd=&NameList[seriesindex];

 if(!wd->Visible)
  return;

 
 // ������� ������ ���������� ������ ����������...
 if(wd->FullUpdate)
 {
  Chart1->Series[seriesindex]->Clear();

  if(!x || !y || size == 0)
   return;

  for(int i=0;i<size;i++)
   Chart1->Series[seriesindex]->AddXY(x[i],y[i]+wd->YShift,"",wd->Color);
 }
 else
 {
  if(wd->WatchInterval == 0)
   return;

  if(!x || !y || size == 0)
   return;

  for(int i=0;i<size;i++)
   Chart1->Series[seriesindex]->AddXY(x[i],y[i]+wd->YShift,"",wd->Color);
  if(wd->WatchInterval>0)
  {
   float ser_max,ser_min;
   if(Chart1->Series[seriesindex]->Count() > 0)
   {
	ser_max=Chart1->Series[seriesindex]->XValue[Chart1->Series[seriesindex]->Count()-1];
	ser_min=Chart1->Series[seriesindex]->XValue[0];
   }
   else
   {
	ser_max=0;
	ser_min=0;
   }

   if(ser_max-ser_min > wd->WatchInterval)
    Chart1->Series[seriesindex]->Delete(0);
  }
 }
 ModifyState=true;
}

void __fastcall TWatchFrame::SeriesUpdate(void* datasource, float* x, float* y, int size)
{
 for(int i=0;i<(int)NameList.size();i++)
  if(NameList[i].DataSource == datasource)
  {
   SeriesUpdate(i,x,y,size);
   return;
  }
}

// ���������� ���������� �� 'stepcount' ��������� ����� ��������������
void __fastcall TWatchFrame::StepUpdate(void)
{
 for(int seriesindex=0; seriesindex<(int)NameList.size();seriesindex++)
 {
  OutGateWatchData *wd;

  // ������������ ���������� � ������
  wd=&NameList[seriesindex];

  if(!wd->Visible)
   continue;

  // ������� ������ ���������� ������ ����������...
  if(wd->FullUpdate)
  {
   Chart1->Series[seriesindex]->Clear();

   if(!wd->X || !wd->Y || wd->XYSize == 0)
	continue;

   for(int i=0;i<wd->XYSize;i++)
	Chart1->Series[seriesindex]->AddXY(wd->X[i],wd->Y[i]+wd->YShift,"",wd->Color);
  }
  else
  {
   if(wd->WatchInterval == 0)
	continue;

   if(!wd->X || !wd->Y || wd->XYSize == 0)
	continue;

   for(int i=0;i<wd->XYSize;i++)
	Chart1->Series[seriesindex]->AddXY(wd->X[i],wd->Y[i]+wd->YShift,"",wd->Color);

   if(wd->WatchInterval>0)
   {
	float ser_max,ser_min;
	if(Chart1->Series[seriesindex]->Count() > 0)
	{
	 ser_max=Chart1->Series[seriesindex]->XValue[Chart1->Series[seriesindex]->Count()-1];
	 ser_min=Chart1->Series[seriesindex]->XValue[0];
	}
	else
	{
	 ser_max=0;
	 ser_min=0;
	}

	if(ser_max-ser_min > wd->WatchInterval)
	 for(int i=0;i<wd->XYSize;i++)
	  Chart1->Series[seriesindex]->Delete(0);
   }
  }
  ModifyState=true;
 }
}
// ------------------------------

// ������� ������ ���� ����������
void __fastcall TWatchFrame::Reset(void)
{
 // ������������ ���������� � ������
 for(int i=0;i<Chart1->SeriesCount();i++)
  {
   Chart1->Series[i]->Clear();
   ModifyState=true;
  }
}


// ���������� ����� ������ ���� ����������� �����
void __fastcall TWatchFrame::GetWatchList(map<int, OutGateWatchData> &buffer)
{
 buffer.clear();
 for(size_t i=0;i<NameList.size();i++)
  buffer[i]=NameList[i];
}

// ���������� ����� ������ ���� ������� �����
void __fastcall TWatchFrame::GetVisibleList(map<int, OutGateWatchData> &buffer)
{
 buffer.clear();
 for(size_t i=0;i<NameList.size();i++)
  if(NameList[i].Visible)
   buffer[i]=NameList[i];
}

// ���������� ����� ������ ���� ��������� �����
void __fastcall TWatchFrame::GetInvisibleList(map<int, OutGateWatchData> &buffer)
{
 buffer.clear();
 for(size_t i=0;i<NameList.size();i++)
  if(!NameList[i].Visible)
   buffer[i]=NameList[i];
}


// �������� ������� �� ��������� ������
void __fastcall TWatchFrame::ChangeLegend(int seriesindex, string legend)
{
 if(seriesindex >= (int)NameList.size())
  return;

// ChangeSeriesLegend(seriesindex,legend);
 if(seriesindex >=Chart1->SeriesCount())
  return;

 Chart1->Series[seriesindex]->Title=legend.c_str();
 ModifyState=true;
 // ...��� ��������� ����������

 NameList[seriesindex].Legend=legend;
}

// �������� ���� ��������� �����
void __fastcall TWatchFrame::ChangeColor(int seriesindex, TColor color)
{
 if(seriesindex >= (int)NameList.size())
  return;

// ChangeSeriesColor(seriesindex,color);
 if(seriesindex >=Chart1->SeriesCount())
  return;

 Chart1->Series[seriesindex]->ColorSource=color;
 Chart1->Series[seriesindex]->SeriesColor=color;
 ModifyState=true;
 // ...��� ��������� ����������

 NameList[seriesindex].Color=color;
}

// �������� ���������� � ��������� �����
void __fastcall TWatchFrame::ChangeVisible(int seriesindex, bool visible)
{
 if(seriesindex < 0 || seriesindex >= (int)NameList.size())
  return;

 NameList[seriesindex].Visible=visible;
 Chart1->Series[seriesindex]->Active=visible;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

// -----------------------------
// ������ ����������� ����������
// -----------------------------
// ��������� ������ �����
void __fastcall TWatchFrame::TBSeriesModify(TObject *Sender)
{
 SeriesControlForm->Execute(this);
}

// ���������� ������� � ����
/*void __fastcall TWatchFrame::TBGraphSave(TObject *Sender)
{
 if(!SaveDialog1->Execute())
  return;

 Chart1->SaveToBitmapFile(SaveDialog1->FileName);
} */

// ��������� ����������� ������� � bmp
bool TWatchFrame::SaveToBitmap(const AnsiString &filename)
{
 if(filename == "")
  return false;

 Chart1->SaveToBitmapFile(filename);
 return true;
}

// ��������� ����������� � ��������
bool TWatchFrame::SaveToMetafile(const AnsiString &filename)
{
 if(filename == "")
  return false;

 Chart1->SaveToMetafileEnh(filename);
 return true;
}

// ��������� ����������� ������� � jpeg
bool TWatchFrame::SaveToJpeg(const AnsiString &filename)
{
 if(filename == "")
  return false;

 TJPEGImage *jpg=new TJPEGImage;

 //Chart->CopyToClipboardBitmap();
 //jpg->LoadFromClipboardFormat(
 jpg->Assign(Chart1->BackImage->Bitmap);
 jpg->SaveToFile(filename);
/* TMemoryStream *stream=new TMemoryStream;

 stream->SetSize(Chart->Cop

 delete stream;*/
 delete jpg;

 return true;
}

// ��������� ����������� � ������� ���� �� �������
bool TWatchFrame::Save(void)
{
 SavePictureDialog->DefaultExt="";
 SavePictureDialog->FileName="";
 if(!SavePictureDialog->Execute())
  return true;

 AnsiString ext=SavePictureDialog->FileName.SubString(SavePictureDialog->FileName.Length()-2,3);
 switch(SavePictureDialog->FilterIndex)
 {
 case 1:
  if(ext != "bmp")
   SavePictureDialog->FileName=SavePictureDialog->FileName+".bmp";
  SaveToBitmap(SavePictureDialog->FileName);
 break;

 case 2:
  if(ext != "emf")
   SavePictureDialog->FileName=SavePictureDialog->FileName+".emf";
  SaveToMetafile(SavePictureDialog->FileName);

 break;

 case 3:
  if(ext != "jpg")
   SavePictureDialog->FileName=SavePictureDialog->FileName+".jpg";
  SaveToJpeg(SavePictureDialog->FileName);
 break;
 }

 return true;
}
// -------------------------
//---------------------------------------------------------------------------
// -----------------------------



