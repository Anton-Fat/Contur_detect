//---------------------------------------------------------------------------


#ifndef GraphFrameUnitH
#define GraphFrameUnitH
#include <Classes.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <series.hpp>

#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>

#include <IniFiles.hpp>
//#include <Filectrl.hpp>
#include <jpeg.hpp>
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>


#include <string>
#include <map>
#include <vector>

using namespace std;

//typedef float real;
//---------------------------------------------------------------------------
/*
   Вспомогательный класс - контейнер данных, характеризующих наблюдаемую точку
съёма.
*/
//---------------------------------------------------------------------------
class OutGateWatchData
{
public: // Связи
// Индекс графика в массиве серий
int SeriesIndex;

// Указатель на источник данных
void* DataSource;

public: // Данные графика
const float *X;
const float *Y;
int XYSize;

// Тип наблюдения
// true - в массивах X,Y хранится набор всех значений графика
// и вся серия обновляется целиком на каждом шаге
// false -
// на каждом шаге новый элемент добавляется в конец
bool FullUpdate;

// Интервал наблюдения, старые данные автоматически удаляются
// игнорируется если <0, или если FullUpdate == true
double WatchInterval;

// Флаг видимости
// Если true - серия отображается, иначе - нет
bool Visible;

public: // Оформление графика
// Смещение графиков серий друг относительно друга по Y
double YShift;

// Цвет графика
TColor Color;

// Подпись графика
string Legend;

public: // Методы
OutGateWatchData(void);
~OutGateWatchData(void);
OutGateWatchData(const OutGateWatchData &wd);
OutGateWatchData& operator = (const OutGateWatchData& wd);
};
        
//---------------------------------------------------------------------------
class TWatchFrame : public TFrame
{
__published:	// IDE-managed Components
        TChart *Chart1;
	TSavePictureDialog *SavePictureDialog;
private:	// User declarations
public:		// User declarations
        __fastcall TWatchFrame(TComponent* Owner);
        virtual __fastcall ~TWatchFrame(void);

protected:	// Данные
        // -----------------------------------------
        // Данные об наблюдаемых точках съёма данных
        // -----------------------------------------
        // Список имён наблюдаемых точек съёма, и смещений
        // графиков серий друг относительно друга по оси Y.
		vector<OutGateWatchData> NameList;
        // -----------------------------------------

        // -----------------------------------------
		// Данные о состоянии
        // -----------------------------------------
        // Содержит 'true' если данные серий были изменены
        // или были добавлены/удалены новые серии
        bool ModifyState;
        // -----------------------------------------

public:	// Методы
		// ------------------------------
		// Методы настройки отображения
		// ------------------------------
		// Включает/отключает автомасштабирование по оси X
		void __fastcall SetXAutoScale(bool value);

		// Возвращает состояние автомасштабирования по оси X
		bool __fastcall GetXAutoScale(void);

		// Включает/отключает автомасштабирование по оси Y
		void __fastcall SetYAutoScale(bool value);

		// Возвращает состояние автомасштабирования по оси Y
		bool __fastcall GetYAutoScale(void);

		// Устанавливает границы изменения по оси X
		void __fastcall SetXMin(float value);
		void __fastcall SetXMax(float value);

		// Устанавливает границы изменения по оси Y
		void __fastcall SetYMin(float value);
		void __fastcall SetYMax(float value);

		// Возвращает границы изменения по оси X
		float __fastcall GetXMin(void);
		float __fastcall GetXMax(void);

		// Возвращает границы изменения по оси Y
		float __fastcall GetYMin(void);
		float __fastcall GetYMax(void);

		// Устанавливает заголовок графика
		void __fastcall SetGraphTitle(AnsiString title);

		// Устанавливает видимость подписей по осям
		void __fastcall SetXLabelVisible(bool value);
		void __fastcall SetYLabelVisible(bool value);

		// Возвращает видимость подписей по осям
		bool __fastcall GetXLabelVisible(void);
		bool __fastcall GetYLabelVisible(void);

		// Устанавливает подписи по осям
		void __fastcall SetXLabelTitle(AnsiString value);
		void __fastcall SetYLabelTitle(AnsiString value);

		// Возвращает подписи по осям
		AnsiString __fastcall GetXLabelTitle(void);
		AnsiString __fastcall GetYLabelTitle(void);

		// Устанавливает видимость легенды
		void __fastcall SetLegendVisible(bool value);

		// Возвращает видимость легенды
		bool __fastcall GetLegendVisible(void);
		// ------------------------------

		// ------------------------------
        // Методы управления состоянием
        // ------------------------------
        // Возвращает 'true', если данные в сериях были изменены,
        // или если серии были добавлены/удалены
        bool __fastcall GetModifyState(void);

        // Собирает информацию об открытых сериях в файл 'watchname'
        // Если 'collectstate' == 'true', то сохраняет также накопленную информацию
        bool __fastcall CollectInfo(string watchname, bool collectstate);

        // Восстанавливает серии по информации из файла 'watchname'
        // Если 'collectstate' == 'true', то восстанавливает также накопленную
        // информацию
        // (Все открытые наблюдения будут предварительно закрыты)
        bool __fastcall RestoreInfo(string watchname, bool collectstate);
        // ------------------------------

        // ------------------------------
        // Методы управления наблюдениями
		// ------------------------------
		// Возвращает данные наблюдения
		OutGateWatchData* __fastcall Get(int seriesindex);
		OutGateWatchData* __fastcall Get(void *datasource);

		// Возвращает общее число данных наблюдения
		int __fastcall GetNumWatches(void);

		// Добавление нового наблюдения
		void __fastcall Add(OutGateWatchData& wd);

        // Удаление наблюдения
        void __fastcall Del(int seriesindex);

        // Удаляет все наблюдения
		void __fastcall Clear(void);

		// Отключает отображение серии
		// используется при обновлении данных
		// если seriesindex < 0 то отключает все серии
		void __fastcall SeriesDisable(int seriesindex=-1);

		// Включает отображение серии
		// используется при обновлении данных
		// если seriesindex < 0 то включает все серии
		void __fastcall SeriesEnable(int seriesindex=-1);

		// Обновление данных серии
		// Добавление одной точки в серию
		void __fastcall SeriesUpdate(int seriesindex, float x, float y);
		void __fastcall SeriesUpdate(void* datasource, float x, float y);

		// Обновление данных серии
		// Добавление массива точек в серию
		void __fastcall SeriesUpdate(int seriesindex, float* x, float* y, int size);
		void __fastcall SeriesUpdate(void* datasource, float* x, float* y, int size);

		// Обновление информации за 'stepcount' прошедших шагов интегрирования
		void __fastcall StepUpdate(void);

        // Удаляет данные всех наблюдений
        void __fastcall Reset(void);

        // Возвращает копию списка всех наблюдаемых серий
		void __fastcall GetWatchList(map<int, OutGateWatchData> &buffer);

		// Возвращает копию списка всех видимых серий
		void __fastcall GetVisibleList(map<int, OutGateWatchData> &buffer);

		// Возвращает копию списка всех невидимых серий
		void __fastcall GetInvisibleList(map<int, OutGateWatchData> &buffer);

		// Заменяет подпись под выбранной серией
		void __fastcall ChangeLegend(int seriesindex, string legend);

        // Заменяет цвет выбранной серии
		void __fastcall ChangeColor(int seriesindex, TColor color);

		// Изменяет информацио о видимости серии
		void __fastcall ChangeVisible(int seriesindex, bool visible);
		// ------------------------------

		// -----------------------------
		// Методы визуального управления
		// -----------------------------
		// Изменение данных серий
		void __fastcall TBSeriesModify(TObject *Sender);

		// Сохранение графика в файл
		// Сохраняет изображение графика в bmp
		bool SaveToBitmap(const AnsiString &filename);

		// Сохраняет изображение в метафайл
		bool SaveToMetafile(const AnsiString &filename);

		// Сохраняет изображение графика в jpeg
		bool SaveToJpeg(const AnsiString &filename);

		// Сохраняет изображение с выбором типа из диалога
		bool Save(void);
		// -----------------------------
};
//---------------------------------------------------------------------------
extern PACKAGE TWatchFrame *WatchFrame;
//---------------------------------------------------------------------------
#endif
