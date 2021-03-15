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
unsigned int c; // Целое, ч/б для вычислений формата 000C
struct { unsigned char b,g,r,d; }; // 32,24 бит RGB 

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


// Класс, описывающий изображение
class UBitmap
{
protected: // Данные
UColorT *Data;
int Width, Height; // размеры изображения по осям
int Length; // Число элементов изображения

UBMColorModel ColorModel; // Глубина цвета

// Флаг автоматического преобразования информации из источника
// в цветовую модель приемника
// По умолчанию true
// Состояние по умолчанию расходует дополнительное время
// на преобразование
bool AutoCModelConvert;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBitmap(void);
UBitmap(const UBitmap &bitmap);
UBitmap(UBMColorModel cmodel);
UBitmap(int width, int height, UColorT color=0,    UBMColorModel cmodel=ubmColor);
UBitmap(int width, int height, const unsigned* data, UBMColorModel cmodel=ubmColor);
~UBitmap(void);
// --------------------------

// -------------------------
// Методы управления данными
// -------------------------
// Возвращает указатель на внутренний буфер
inline UColorT* GetData(void) const
{ return Data; };

// Возвращает размер изображения по оси X
inline int GetWidth(void) const
{ return Width; };

// Возвращает размер изображения по оси Y
inline int GetHeight(void) const
{ return Height; };

inline int GetLength(void) const
{ return Length; };

inline UBMColorModel GetColorModel(void) const
{ return ColorModel; };

inline bool GetAutoCModelConvert(void) const
{ return AutoCModelConvert; };

// Задает глубину цвета изображения
// Если isupdate == true то существующее изображение преобразуется
void SetColorModel(UBMColorModel cmodel, bool isupdate=true);

// Задает режим преобразования цветовой модели
// приемника результатов обработки 'target' во всех методах
// если true - то target сохраняет свою цветовую модель
// если false - target принимает цветовую модель источника
void SetAutoCModelConvert(bool acmodel);

// Создает внутренний буфер
void SetRes(int width, int height);

// Копирует новое изображение из буфера data
// с прежними размерами
void SetImage(const UColorT* data);

// Копирует новое изображение из буфера data
// с новыми размерами
void SetImage(int width, int height, const UColorT* data);

// Устанавливает внутренний указатель на буфер data
// сохраняя прежнюю информацию о размерах
void SetPImage(UColorT* data);

// Устанавливает внутренний указатель на буфер data
// обновляя информацию о размерах
void SetPImage(int width, int height, UColorT* data);

// Заполняет изображение цветом color
void Fill(UColorT color);
        
// Копирует изображение в 'target' в позицию,
// начинающуюся как x,y
// Если изображение не вмещается целиком, то оно усекается
// Изображение всегда преобразуется в цветовую модель цели 'target'
void CopyTo(int x, int y, UBitmap &target);

// Копирует изображение в 'target' в позицию,
// начинающуюся как x,y
// Если изображение не вмещается целиком, то оно усекается
// Изображение всегда преобразуется в цветовую модель цели 'target'
// Элементы изображения источника с цветом 'transp' не переносятся
// (эффект прозрачности)
void CopyTo(int x, int y, UBitmap &target, UColorT transp);

// Возвращает участок изображения с координатами
// левого верхнего угла x,y и шириной и длиной
// соответствующей размерам 'target'
bool GetRect(int x, int y, UBitmap &target);

// Разделяет текущее изображение на RGB цветовые каналы
// Каналы формируются в соответствии с цветовой моделью 'cmodel'
// Цветовая модель изображения предполагается ubmColor 
void Separate(UBitmap &red, UBitmap &green, UBitmap &blue, UBMColorModel cmodel=ubmMath);
// -------------------------

// -------------------------
// Методы сбора статистики
// -------------------------
// Возвращает минимальное и максимальное значение яркостей
void FindColorRange(UColorT &minval, UColorT &maxval);

// Вычисляет средневзвешенную сумму яркостей всех пикслей участка изображения
// Если 'width' или 'height' < 0 или превышает максимум
// то размеры участка вычисляются до конца изображения
UColorT FindAverageColor(int x=0, int y=0, int width=-1,int height=-1);

// Вычисляет суммарную яркость по строке изображения с номером y
unsigned int CalcBrightnessByRow(int y);

// Вычисляет суммарную яркость по столбцу изображения с номером x
unsigned int CalcBrightnessByCol(int x);
                                   
// Вычисляет суммарную яркость раздельно по столбцам и строками изображения от 
// столбца x1 до x2, и от строки y1 до y2. 
// В x_result значения столбцов, в y_result - строк, память должна быть выделена
void UBitmap::Histogram(unsigned *x_result, unsigned *y_result, 
                                   int x1=-1, int x2=-1, int y1=-1, int y2=-1);

// Вычисляет относительную суммарную интенсивность раздельно по столбцам и 
// строками изображения от столбца x1 до x2, и от строки y1 до y2. 
// Интенсивность считается раздельно по каналам в зависимости от цветовой модели
// В x_result значения столбцов, в y_result - строк, память должна быть выделена
void UBitmap::Histogram(UColorT *x_result, UColorT *y_result, 
                                   int x1=-1, int x2=-1, int y1=-1, int y2=-1);
// -------------------------

// -------------------------
// Методы обработки изображения
// -------------------------      
// Отражение по вертикали
// Если 'target' != 0 то результат операции сохраняется в него
// и цветовая модель 'target' замещается моделью источника
void UBitmap::ReflectionX(UBitmap *target=0);

// Сдвигает изображение в требуемую сторону на 'pixels' пикселей
// Направление определяется 'direction'
// 1 - Up
// 2 - Down
// 3 - Left
// 4 - Right
// При иных значениях 'direction' или отрицательных значениях pixels
// метод не делает ничего
// Пустое место заполняется цветом 'color'
// Если 'target' != 0 то результат операции сохраняется в него
// и цветовая модель 'target' замещается моделью источника
void Move(int pixels, int direction, UColorT color=0, UBitmap *target=0);

// Сдвигает изображение на 'x' пикселей по оси абсцисс и на 'y'
// пикселей по оси ординат
// положительные значения вызывают сдвиг вправо и вниз
// отрицательные - влево и вверх
// Пустое место заполняется цветом 'color'
// Если 'target' != 0 то результат операции сохраняется в него
// и цветовая модель 'target' замещается моделью источника
void MoveXY(int x, int y, UColorT color=0, UBitmap *target=0);

// Изменяет размер канвы, сохраняя нетронутым изображение
// Если изображение не помещается целиком в новую канву,
// то оно усекается
// Свободное место заполняется цветом 'color'
// Если 'target' != 0 то результат операции сохраняется в него
// и цветовая модель 'target' замещается моделью источника
void ResizeCanvas(int top, int left, int right, int bottom, UColorT color=0, UBitmap *target=0);

// Изменяет размер изображения с линейной интерполяцией
// Если 'target' != 0 то результат операции сохраняется в него
void Resize(int width, int height, UBMResizeMethod resizemethod=ubmNolinear, UBitmap *target=0);

// Вставляет горизонтальную полосу толщиной 'thickness'
// начиная с позиции с верхней y-координатой
// Полоса заполняется цветом 'color'
void InsertHorLine(int y, int thickness, UColorT color=0, UBitmap *target=0);

// Удаляет горизонтальную полосу толщиной 'thickness'
// начиная с позиции с верхней y-координатой
void RemoveHorLine(int y, int thickness, UBitmap *target=0);

// Вставляет вертикальную полосу толщиной 'thickness'
// начиная с позиции с левой x-координатой
// Полоса заполняется цветом 'color'
void InsertVertLine(int x, int thickness, UColorT color=0, UBitmap *target=0);

// Удаляет вертикальную полосу толщиной 'thickness'
// начиная с позиции с левой x-координатой
void RemoveVertLine(int x, int thickness, UBitmap *target=0);

// Контрастирование. Производит пересчёт значений яркости в масштаб 0 - 255.
// Запись результата производится в target
void Contrasting(UBitmap *target=0);

// Контрастирование. Производит пересчёт значений яркости в масштаб minb - maxb.
// Если 'target' != 0 то результат операции сохраняется в него
void Contrasting(UColorT minb, UColorT maxb, UBitmap *target=0);

// Выделение контуров.
// Запись результата производится в target
void Looping(UBitmap *target, UBMLoopingMethod method=ubmSobel);

// Производит бинаризацию изображения с порогом threshold
// Если 'target' != 0 то результат операции сохраняется в него
// Пиксели с яркостями ниже порога устанавливаются равными 'minval'
// Пиксели с яркостями выше порога устанавливаются равными 'maxval'
void Binarization(UColorT threshold, UColorT minval, UColorT maxval, UBitmap *target=0);

// Производит автоматическую бинаризацию изображения по
// порогу, представляющему собой средневзвешенную яркость изображения
// Если 'target' != 0 то результат операции сохраняется в него
// Пиксели с яркостями ниже порога устанавливаются равными 'minval'
// Пиксели с яркостями выше порога устанавливаются равными 'maxval'
void Binarization(UColorT minval, UColorT maxval, UBitmap *target=0);

// Осуществляет фильтрацию изображение методом усреднения
// по маске размером 'masksize'
// Если размер маски задан четным, то он округляется
// до ближайшего большего нечетного
// Фильтрованное изображение сохраняется в target
// Если 'target' == 0 то не делает ничего
void MaskFiltering(int mask, UBitmap *target) const;

// Инвертирует изображение
// Если 'target' != 0 то результат операции сохраняется в него
// Для всех цветовых моделей база устанавливается == 255
// т.о. модель ubmMath необходим нормировать в [0:255] перед инверсией
void Inverse(UBitmap *target=0);

// Осуществляет построение разностного кадра
// Если 'target' != 0 то результат операции сохраняется в него
bool DifferenceFrame(const UBitmap *deduction, UBitmap *target=0);
// -------------------------

// -----------------------
// Перегруженные операторы
// -----------------------
// Оператор присваивания
// Цветовая модель приемника всегда замещается моделью источника
UBitmap& operator = (const UBitmap &bitmap);

inline unsigned& operator [] (int index) const
{ return (Data+index)->c; };

inline UColorT& operator () (int index) const
{ return *(Data+index); };

inline UColorT& operator () (int ix, int iy) const
{ return *(Data+iy*Width+ix); };
// -----------------------

protected: // Скрытые методы
// -----------------------
// Методы изменения размера изображения
// -----------------------
// Изменение размера изображения с константной интерполяцией
bool ResizeConst(UColorT *output, UColorT* input,
                            int oWidth, int oHeight,
                            int nWidth, int nHeight);

// Изменение размера изображения с линейной интерполяцией
bool ResizeLinear(UColorT *output, UColorT* input,
                            int oWidth, int oHeight,
                            int nWidth, int nHeight);

// Изменение размера изображения с нелинейной интерполяцией
bool ResizeNolinear(UColorT *output, UColorT* input,
							int oWidth, int oHeight,
							int nWidth, int nHeight);
// -----------------------

// -----------------------
// Методы выделения контуров
// -----------------------
// Оригинальный алгоритм
void NativeLooping(UBitmap *target);

// Фильтр Собеля
void SobelLooping(UBitmap *target);
// -----------------------
};

}
#endif

