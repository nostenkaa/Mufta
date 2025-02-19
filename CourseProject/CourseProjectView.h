
// CourseProjectView.h: интерфейс класса CCourseProjectView
//

#pragma once
#include "CourseProjectDoc.h"
#include <vector>
//Измените на Ваши пути
#include "C:\Program Files\ASCON\KOMPAS-3D v22 Study\SDK\Include\ksConstants.h"
#include "C:\Program Files\ASCON\KOMPAS-3D v22 Study\SDK\Include\ksConstants3D.h"
#import "C:\Program Files\ASCON\KOMPAS-3D v22 Study\SDK\lib\kAPI5.tlb"

using namespace Kompas6API5;
class CCourseProjectView : public CView
{
protected: // создать только из сериализации
	CCourseProjectView() noexcept;
	DECLARE_DYNCREATE(CCourseProjectView)

// Атрибуты
public:
	CCourseProjectDoc* GetDocument() const;

	KompasObjectPtr kompas;
	
	//Структура для штифта
	struct Pin
	{
		double d, d1, l, c;
		CString name[5];
		CString filePath;
	};
	//Структура для вала
	struct Shaft
	{
		double D, d, l, c, L;
		CString filePath;
	};
	//Структура для втулки
	struct Bushing
	{
		double d, d1, D, L, l, c;
		CString name[8];
		CString filePath;
	};
	//Структура для муфты
	struct Coupling
	{
		CString name[3];
	};

	//Векторы (массивы) структур по деталям 
	std::vector<Pin> vecPin;			//вектор для штифта
	std::vector<Bushing> vecBushing;	//вектор для втулки 
	std::vector<Shaft> vecShaft;		//вектор для вала
	std::vector<Coupling> vecCoupling;	//вектор для муфты 

	CButton m_Buttons[7];	//массив кнопок	
	CString m_sfilePath;	//файловый путь 
	
	//Методы для построения деталей
	void CreatePin(Pin& st);
	void CreateShaft(Shaft& st);
	void CreateBushing(Bushing& st);
	//Метод для построения сборки
	void CreateCoupling(Pin ring, Shaft shaft, Bushing bushing);

	//Mетод для создания изображения 
	int CreateImage(CDC* pDC, int Width, CString name_file);
	//Cлужебный метод, который переводит из double в CString и отбрасывает незначащие нули
	CString Сonversion(double number);

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CCourseProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnButtonClick(UINT nID);
};

#ifndef _DEBUG  // версия отладки в CourseProjectView.cpp
inline CCourseProjectDoc* CCourseProjectView::GetDocument() const
   { return reinterpret_cast<CCourseProjectDoc*>(m_pDocument); }
#endif

