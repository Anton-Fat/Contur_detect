//---------------------------------------------------------------------------

#ifndef VCLmainH
#define VCLmainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <ImgList.hpp>
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
#include <vector>
#include "UBitmap.h"
#include "TUBitmap.h"
#include "UGraphics.h"
#include "UAGraphics.h"

using namespace std;
using namespace Utilities;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TOpenPictureDialog *OpenDialog;
	TSaveDialog *SaveDialog;
	TPanel *Panel1;
	TButton *Button1;
	TButton *Button3;
	TImage *ImageGround;
	TPanel *Panel2;
	TImage *Image1;
	TPanel *Panel3;
	TImage *Image2;
	TPanel *Panel4;
	TEdit *Edit1;
	TButton *Button2;
	TButton *Button4;
	TLabel *Label1;
	TComboBox *ComboBox1;
	TButton *Button6;
	TButton *Button7;
	TEdit *Edit2;
	TLabel *Label2;
	TEdit *Edit3;
	TLabel *Label3;
	TComboBox *ComboBox2;
	TButton *Button8;
	TChart *Chart1;
	TBarSeries *Series1;
	TLineSeries *Series3;
	TButton *Button9;
	TButton *Button10;
	TComboBox *ComboBox3;
	TComboBox *ComboBox4;
	TCheckBox *CheckBox1;
	TButton *Button11;
	TButton *Button12;
	TButton *Button13;
	TPointSeries *Series2;
	TComboBox *ComboBox5;
	TButton *Button14;
	TButton *Button15;
	TButton *Button16;
	TButton *Button17;
	TButton *Button18;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Image2DblClick(TObject *Sender);
	void __fastcall ComboBox2Change(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);
	void __fastcall Button16Click(TObject *Sender);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

   //	vector<vector<char> > ArrImage;

	 //int Per[10][6];
    //int Npoint;

	struct spkont
	{
	vector<int> Xp1;
	vector<int> Yp1;
	vector<int> Type1;
    vector<int> Napr1;
	unsigned char colk;
	};
	spkont KPoint1;
	UBitmap Bmp1,Bmp2,Kont;
	bool B1trig[2];
	bool Im2trig[2];
    bool AP;
	unsigned short int numIt;
	 
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
