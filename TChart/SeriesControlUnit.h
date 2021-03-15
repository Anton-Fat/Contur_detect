//---------------------------------------------------------------------------

#ifndef SeriesControlUnitH
#define SeriesControlUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include "GraphFrameUnit.h"
//---------------------------------------------------------------------------
class TSeriesControlForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel2;
        TPanel *Panel4;
        TPanel *Panel5;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TColorDialog *ColorDialog1;
        TPanel *Panel3;
        TPanel *Panel6;
        TBitBtn *BitBtn1;
        TPanel *Panel1;
        TLabel *Label1;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TCheckBox *CheckBox2;
        TEdit *Edit2;
        TCheckBox *CheckBox4;
        TEdit *Edit1;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox3;
        TLabel *Label2;
        TEdit *Edit3;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Edit4;
        TBitBtn *BitBtn2;
        TPanel *OutterCPanel;
        TPanel *InnerCPanel;
        TCheckBox *CheckBox5;
	TGroupBox *GroupBox3;
	TStringGrid *StringGrid1;
	TGroupBox *GroupBox4;
	TStringGrid *StringGrid2;
        void __fastcall OutterCPanelDblClick(TObject *Sender);
        void __fastcall InnerCPanelDblClick(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall StringGrid2Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall StringGrid2DblClick(TObject *Sender);
        void __fastcall Edit3DblClick(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall CheckBox3Click(TObject *Sender);
        void __fastcall CheckBox4Click(TObject *Sender);
        void __fastcall StringGrid1DblClick(TObject *Sender);
        void __fastcall Edit4KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Edit4Exit(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall Edit2Change(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall CheckBox5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TSeriesControlForm(TComponent* Owner);

protected: // ������
        // ������������� ���� ����������
        TWatchFrame* GrSender;

        // -----------------------------------------
        // ������ �� ����������� ������ ����� ������
        // -----------------------------------------
        // ������ ��� ����������� ����� �����, � ��������
        // �������� ����� ���� ������������ ����� �� ��� Y.
		map<int,OutGateWatchData> WatchList;

		// ������ ��� ��������� ��� ���������� ����� �����
		map<int,OutGateWatchData> PossibleWatchList;
        // -----------------------------------------

        // -----------------------------------------
        // ��������, ����������� ��������� ����������� �����
        // -----------------------------------------
        // ��������� ��������� ����������� ���� � ������� � ���
        bool GraphChanged;

        // ��������� ��������� �������� ����� �����
        bool ColorsChanged;

        // ��������� ��������� ������� �����
        bool LegendsChanged;

        // ��������� ���������� ����� �/��� �� ��������
        bool SeriesChanged;
        // -----------------------------------------

protected: // ��������������� ������
        // ------------------------
        // ������ ���������� ���������� ����������/�������� ����� ����������
        // ------------------------
        // ���������� ������� ������
        void __fastcall UpdateDataLists(void);

        // ��������� ���������� � ����� � ��������� ���� ��������� ����������
        void __fastcall UpdateInfo(void);

        // ��������� ���������� �� ��������� ����������� ����� �����
        void __fastcall UpdateSelectedWatch(void);
        // ------------------------

public: // ������
        // ------------------------
        // ������ ���������� ������
        // ------------------------
        // �����, ������� ������ ���� ������ ��� �������� �������
        void __fastcall Execute(TWatchFrame* grsender);

        // ------------------------
};
//---------------------------------------------------------------------------
extern PACKAGE TSeriesControlForm *SeriesControlForm;
//---------------------------------------------------------------------------
#endif