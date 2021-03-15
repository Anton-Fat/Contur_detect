/* ************************************************************************** */
// Copyright Alexander Bakhshiev, 2005-2008.
// E-mail: alexab@ailabe.ru
/* ************************************************************************** */
#ifndef UBITMAP_H
#define UBITMAP_H

namespace Utilities {

typedef enum {ubmColor=1, ubmGray=2, ubmMath=3} UBMColorModel;

typedef enum {ubmUp=1, ubmDown=2, ubmLeft=3, ubmRight=4} UBMShiftDirection;

typedef enum {ubmConst=1, ubmLinear=2, ubmNolinear=3} UBMResizeMethod;

typedef enum {ubmNative=1, ubmSobel=2} UBMLoopingMethod;

union UColorT
{
unsigned int c; // �����, �/� ��� ���������� ������� 000C
struct { unsigned char b,g,r,d; }; // 32,24 ��� RGB 

UColorT(void) 
{ };

UColorT(unsigned color)
{ c=color; };

UColorT(unsigned char rr, unsigned char gg,    unsigned char bb, unsigned char dd=0)
{ r=rr; b=bb; g=gg; d=dd; };

UColorT operator = (const UColorT &color)
{ c=color.c; return *this; };

UColorT operator = (const unsigned color)
{ c=color; return *this; };

bool operator == (const UColorT color)
{ return (c==color.c)?true:false; };

bool operator != (const UColorT color)
{ return (c!=color.c)?true:false; };
};


// �����, ����������� �����������
class UBitmap
{
protected: // ������
UColorT *Data;
int Width, Height; // ������� ����������� �� ����
int Length; // ����� ��������� �����������

UBMColorModel ColorModel; // ������� �����

// ���� ��������������� �������������� ���������� �� ���������
// � �������� ������ ���������
// �� ��������� true
// ��������� �� ��������� ��������� �������������� �����
// �� ��������������
bool AutoCModelConvert;

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
UBitmap(void);
UBitmap(const UBitmap &bitmap);
UBitmap(UBMColorModel cmodel);
UBitmap(int width, int height, UColorT color=0,    UBMColorModel cmodel=ubmColor);
UBitmap(int width, int height, const unsigned* data, UBMColorModel cmodel=ubmColor);
~UBitmap(void);
// --------------------------

// -------------------------
// ������ ���������� �������
// -------------------------
// ���������� ��������� �� ���������� �����
inline UColorT* GetData(void) const
{ return Data; };

// ���������� ������ ����������� �� ��� X
inline int GetWidth(void) const
{ return Width; };

// ���������� ������ ����������� �� ��� Y
inline int GetHeight(void) const
{ return Height; };

inline int GetLength(void) const
{ return Length; };

inline UBMColorModel GetColorModel(void) const
{ return ColorModel; };

inline bool GetAutoCModelConvert(void) const
{ return AutoCModelConvert; };

// ������ ������� ����� �����������
// ���� isupdate == true �� ������������ ����������� �������������
void SetColorModel(UBMColorModel cmodel, bool isupdate=true);

// ������ ����� �������������� �������� ������
// ��������� ����������� ��������� 'target' �� ���� �������
// ���� true - �� target ��������� ���� �������� ������
// ���� false - target ��������� �������� ������ ���������
void SetAutoCModelConvert(bool acmodel);

// ������� ���������� �����
void SetRes(int width, int height);

// �������� ����� ����������� �� ������ data
// � �������� ���������
void SetImage(const UColorT* data);

// �������� ����� ����������� �� ������ data
// � ������ ���������
void SetImage(int width, int height, const UColorT* data);

// ������������� ���������� ��������� �� ����� data
// �������� ������� ���������� � ��������
void SetPImage(UColorT* data);

// ������������� ���������� ��������� �� ����� data
// �������� ���������� � ��������
void SetPImage(int width, int height, UColorT* data);

// ��������� ����������� ������ color
void Fill(UColorT color);
        
// �������� ����������� � 'target' � �������,
// ������������ ��� x,y
// ���� ����������� �� ��������� �������, �� ��� ���������
// ����������� ������ ������������� � �������� ������ ���� 'target'
void CopyTo(int x, int y, UBitmap &target);

// �������� ����������� � 'target' � �������,
// ������������ ��� x,y
// ���� ����������� �� ��������� �������, �� ��� ���������
// ����������� ������ ������������� � �������� ������ ���� 'target'
// �������� ����������� ��������� � ������ 'transp' �� �����������
// (������ ������������)
void CopyTo(int x, int y, UBitmap &target, UColorT transp);

// ���������� ������� ����������� � ������������
// ������ �������� ���� x,y � ������� � ������
// ��������������� �������� 'target'
bool GetRect(int x, int y, UBitmap &target);

// ��������� ������� ����������� �� RGB �������� ������
// ������ ����������� � ������������ � �������� ������� 'cmodel'
// �������� ������ ����������� �������������� ubmColor 
void Separate(UBitmap &red, UBitmap &green, UBitmap &blue, UBMColorModel cmodel=ubmMath);
// -------------------------

// -------------------------
// ������ ����� ����������
// -------------------------
// ���������� ����������� � ������������ �������� ��������
void FindColorRange(UColorT &minval, UColorT &maxval);

// ��������� ���������������� ����� �������� ���� ������� ������� �����������
// ���� 'width' ��� 'height' < 0 ��� ��������� ��������
// �� ������� ������� ����������� �� ����� �����������
UColorT FindAverageColor(int x=0, int y=0, int width=-1,int height=-1);

// ��������� ��������� ������� �� ������ ����������� � ������� y
unsigned int CalcBrightnessByRow(int y);

// ��������� ��������� ������� �� ������� ����������� � ������� x
unsigned int CalcBrightnessByCol(int x);
                                   
// ��������� ��������� ������� ��������� �� �������� � �������� ����������� �� 
// ������� x1 �� x2, � �� ������ y1 �� y2. 
// � x_result �������� ��������, � y_result - �����, ������ ������ ���� ��������
void UBitmap::Histogram(unsigned *x_result, unsigned *y_result, 
                                   int x1=-1, int x2=-1, int y1=-1, int y2=-1);

// ��������� ������������� ��������� ������������� ��������� �� �������� � 
// �������� ����������� �� ������� x1 �� x2, � �� ������ y1 �� y2. 
// ������������� ��������� ��������� �� ������� � ����������� �� �������� ������
// � x_result �������� ��������, � y_result - �����, ������ ������ ���� ��������
void UBitmap::Histogram(UColorT *x_result, UColorT *y_result, 
                                   int x1=-1, int x2=-1, int y1=-1, int y2=-1);
// -------------------------

// -------------------------
// ������ ��������� �����������
// -------------------------      
// ��������� �� ���������
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
// � �������� ������ 'target' ���������� ������� ���������
void UBitmap::ReflectionX(UBitmap *target=0);

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
// � �������� ������ 'target' ���������� ������� ���������
void Move(int pixels, int direction, UColorT color=0, UBitmap *target=0);

// �������� ����������� �� 'x' �������� �� ��� ������� � �� 'y'
// �������� �� ��� �������
// ������������� �������� �������� ����� ������ � ����
// ������������� - ����� � �����
// ������ ����� ����������� ������ 'color'
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
// � �������� ������ 'target' ���������� ������� ���������
void MoveXY(int x, int y, UColorT color=0, UBitmap *target=0);

// �������� ������ �����, �������� ���������� �����������
// ���� ����������� �� ���������� ������� � ����� �����,
// �� ��� ���������
// ��������� ����� ����������� ������ 'color'
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
// � �������� ������ 'target' ���������� ������� ���������
void ResizeCanvas(int top, int left, int right, int bottom, UColorT color=0, UBitmap *target=0);

// �������� ������ ����������� � �������� �������������
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
void Resize(int width, int height, UBMResizeMethod resizemethod=ubmNolinear, UBitmap *target=0);

// ��������� �������������� ������ �������� 'thickness'
// ������� � ������� � ������� y-�����������
// ������ ����������� ������ 'color'
void InsertHorLine(int y, int thickness, UColorT color=0, UBitmap *target=0);

// ������� �������������� ������ �������� 'thickness'
// ������� � ������� � ������� y-�����������
void RemoveHorLine(int y, int thickness, UBitmap *target=0);

// ��������� ������������ ������ �������� 'thickness'
// ������� � ������� � ����� x-�����������
// ������ ����������� ������ 'color'
void InsertVertLine(int x, int thickness, UColorT color=0, UBitmap *target=0);

// ������� ������������ ������ �������� 'thickness'
// ������� � ������� � ����� x-�����������
void RemoveVertLine(int x, int thickness, UBitmap *target=0);

// ����������������. ���������� �������� �������� ������� � ������� 0 - 255.
// ������ ���������� ������������ � target
void Contrasting(UBitmap *target=0);

// ����������������. ���������� �������� �������� ������� � ������� minb - maxb.
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
void Contrasting(UColorT minb, UColorT maxb, UBitmap *target=0);

// ��������� ��������.
// ������ ���������� ������������ � target
void Looping(UBitmap *target, UBMLoopingMethod method=ubmSobel);

// ���������� ����������� ����������� � ������� threshold
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
// ������� � ��������� ���� ������ ��������������� ������� 'minval'
// ������� � ��������� ���� ������ ��������������� ������� 'maxval'
void Binarization(UColorT threshold, UColorT minval, UColorT maxval, UBitmap *target=0);

// ���������� �������������� ����������� ����������� ��
// ������, ��������������� ����� ���������������� ������� �����������
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
// ������� � ��������� ���� ������ ��������������� ������� 'minval'
// ������� � ��������� ���� ������ ��������������� ������� 'maxval'
void Binarization(UColorT minval, UColorT maxval, UBitmap *target=0);

// ������������ ���������� ����������� ������� ����������
// �� ����� �������� 'masksize'
// ���� ������ ����� ����� ������, �� �� �����������
// �� ���������� �������� ���������
// ������������� ����������� ����������� � target
// ���� 'target' == 0 �� �� ������ ������
void MaskFiltering(int mask, UBitmap *target) const;

// ����������� �����������
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
// ��� ���� �������� ������� ���� ��������������� == 255
// �.�. ������ ubmMath ��������� ����������� � [0:255] ����� ���������
void Inverse(UBitmap *target=0);

// ������������ ���������� ����������� �����
// ���� 'target' != 0 �� ��������� �������� ����������� � ����
bool DifferenceFrame(const UBitmap *deduction, UBitmap *target=0);
// -------------------------

// -----------------------
// ������������� ���������
// -----------------------
// �������� ������������
// �������� ������ ��������� ������ ���������� ������� ���������
UBitmap& operator = (const UBitmap &bitmap);

inline unsigned& operator [] (int index) const
{ return (Data+index)->c; };

inline UColorT& operator () (int index) const
{ return *(Data+index); };

inline UColorT& operator () (int ix, int iy) const
{ return *(Data+iy*Width+ix); };
// -----------------------

protected: // ������� ������
// -----------------------
// ������ ��������� ������� �����������
// -----------------------
// ��������� ������� ����������� � ����������� �������������
bool ResizeConst(UColorT *output, UColorT* input,
                            int oWidth, int oHeight,
                            int nWidth, int nHeight);

// ��������� ������� ����������� � �������� �������������
bool ResizeLinear(UColorT *output, UColorT* input,
                            int oWidth, int oHeight,
                            int nWidth, int nHeight);

// ��������� ������� ����������� � ���������� �������������
bool ResizeNolinear(UColorT *output, UColorT* input,
							int oWidth, int oHeight,
							int nWidth, int nHeight);
// -----------------------

// -----------------------
// ������ ��������� ��������
// -----------------------
// ������������ ��������
void NativeLooping(UBitmap *target);

// ������ ������
void SobelLooping(UBitmap *target);
// -----------------------
};

}
#endif

