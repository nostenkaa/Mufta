
// CourseProjectView.cpp: реализация класса CCourseProjectView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "CourseProject.h"
#endif

#include "CourseProjectDoc.h"
#include "CourseProjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCourseProjectView

IMPLEMENT_DYNCREATE(CCourseProjectView, CView)

BEGIN_MESSAGE_MAP(CCourseProjectView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_NEST_1, IDC_BUTTON_NEST_6, &CCourseProjectView::OnButtonClick)
END_MESSAGE_MAP()

// Создание или уничтожение CCourseProjectView

CCourseProjectView::CCourseProjectView() noexcept
{
	// TODO: добавьте код создания

}

CCourseProjectView::~CCourseProjectView()
{
}

BOOL CCourseProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}


// Рисование CCourseProjectView



void CCourseProjectView::OnDraw(CDC* pDC)
{
	CCourseProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных

	CRect clientRect;
	GetClientRect(&clientRect);

	int Height = clientRect.Height();	//Высота окна
	int Width = clientRect.Width();		//Ширина окна
	int headingWidth = 160;				//Ширина колонки под № исполения 	
	int cellHeight = 30;				//Высота одной ячейки
	double cellWidth = (Width - headingWidth) / 9.f;	//Ширина одной ячейки

	//Если в дереве выбрана муфта
	if (pDoc->m_bCoupling)
	{
		CFont font;
		font.CreatePointFont(90, L"Arial");
		CFont* pOldFont = pDC->SelectObject(&font);

		int imageHeight = CreateImage(pDC, Width, L"res\\Coupling.jpg");
		int x = 0;
		int y = imageHeight + 15;

		// Рисование шапки таблицы
		{
			CString CouplingBuff[4] = { L"№ исполнения", L"D", L"d", L"L" };

			CRect HeaderRect(x, y, x + headingWidth, y + cellHeight);
			pDC->Rectangle(HeaderRect);
			pDC->DrawText(CouplingBuff[0], HeaderRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			x += headingWidth;
			
			for (int i = 1; i < 4; i++)
			{
				CRect HeaderRect(x, y, x + cellWidth, y + cellHeight);
				pDC->Rectangle(HeaderRect);
				pDC->DrawText(CouplingBuff[i], HeaderRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				x += cellWidth;
			}
		}

		// Заполнение таблицы
		{
			for (int i = 0; i < vecCoupling.size(); i++)
			{
				y += cellHeight;
				x = 0;

				CRect ButtonRect(x, y, x + headingWidth, y + cellHeight);

				m_Buttons[i].MoveWindow(ButtonRect);
				m_Buttons[i].ShowWindow(SW_SHOW);

				x += headingWidth;

				for (int g = 0; g < 3; g++)
				{
					CRect HeaderRect(x, y, x + cellWidth, y + cellHeight);
					pDC->Rectangle(HeaderRect);
					pDC->DrawText(vecCoupling[i].name[g], HeaderRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					x += cellWidth;
				}
			}
		}

		pDC->SelectObject(pOldFont);
	}
	//Если в дереве выбрана втулка 
	if (pDoc->m_bBushing)
	{
		CFont font;
		font.CreatePointFont(90, L"Arial");
		CFont* pOldFont = pDC->SelectObject(&font);

		int imageHeight = CreateImage(pDC, Width, L"res\\Bushing.jpg");
		int x = 0;
		int y = imageHeight + 15;

		// Рисование шапки таблицы
		{
			CString BushingBuff[9] = { L"№ исполнения", L"Крутящий момент", L"d", L"d1", L"D", L"L", L"l", L"c", L"Масса, кг" };

			CRect HeaderRect(x, y, x + headingWidth, y + cellHeight);
			pDC->Rectangle(HeaderRect);
			pDC->DrawText(BushingBuff[0], HeaderRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			x += headingWidth;
			
			for (int i = 1; i < 9; i++)
			{
				CRect HeaderRect(x, y, x + cellWidth, y + cellHeight);
				pDC->Rectangle(HeaderRect);
				pDC->DrawText(BushingBuff[i], HeaderRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				x += cellWidth;
			}
		}

		// Заполнение таблицы
		{
			for (int i = 0; i < vecBushing.size(); i++)
			{
				y += cellHeight;
				x = 0;

				CRect ButtonRect(x, y, x + headingWidth, y + cellHeight);

				m_Buttons[i].MoveWindow(ButtonRect);
				m_Buttons[i].ShowWindow(SW_SHOW);

				x += headingWidth;

				for (int g = 0; g < 8; g++)
				{
					CRect HeaderRect(x, y, x + cellWidth, y + cellHeight);
					pDC->Rectangle(HeaderRect);
					pDC->DrawText(vecBushing[i].name[g], HeaderRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					x += cellWidth;
				}
			}
		}

		pDC->SelectObject(pOldFont);
	}
	//Если в дереве выбран штифт 
	if (pDoc->m_bPin)
	{
		CFont font;
		font.CreatePointFont(90, L"Arial");
		CFont* pOldFont = pDC->SelectObject(&font);

		int imageHeight = CreateImage(pDC, Width, L"res\\Pin.jpg");
		int x = 0;
		int y = imageHeight + 15;

		// Рисование шапки таблицы
		{
			CString PinBuff[6] = { L"№ исполнения", L"d", L"d1", L"l", L"c", L"Масса 1000 шт, кг" };

			CRect HeaderRect(x, y, x + headingWidth, y + cellHeight);
			pDC->Rectangle(HeaderRect);
			pDC->DrawText(PinBuff[0], HeaderRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			x += headingWidth;
			
			for (int i = 1; i < 6; i++)
			{
				CRect HeaderRect(x, y, x + cellWidth, y + cellHeight);
				pDC->Rectangle(HeaderRect);
				pDC->DrawText(PinBuff[i], HeaderRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				x += cellWidth;
			}
		}

		// Заполнение таблицы
		{
			for (int i = 0; i < vecPin.size(); i++)
			{
				y += cellHeight;
				x = 0;

				CRect ButtonRect(x, y, x + headingWidth, y + cellHeight);

				m_Buttons[i].MoveWindow(ButtonRect);
				m_Buttons[i].ShowWindow(SW_SHOW);

				x += headingWidth;

				for (int g = 0; g < 5; g++)
				{
					CRect HeaderRect(x, y, x + cellWidth, y + cellHeight);
					pDC->Rectangle(HeaderRect);
					pDC->DrawText(vecPin[i].name[g], HeaderRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					x += cellWidth;
				}
			}
		}

		pDC->SelectObject(pOldFont);
	}
}


// Печать CCourseProjectView

BOOL CCourseProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CCourseProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CCourseProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CCourseProjectView

#ifdef _DEBUG
void CCourseProjectView::AssertValid() const
{
	CView::AssertValid();
}

void CCourseProjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCourseProjectDoc* CCourseProjectView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCourseProjectDoc)));
	return (CCourseProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CCourseProjectView


//Обработчик создания окна 
int CCourseProjectView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания
	for (int i = 0; i < 7; i++)
	{
		CString NumberButton;
		NumberButton.Format(L"Исполнение %i", i + 1);
		m_Buttons[i].Create(NumberButton, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, IDC_BUTTON_NEST_1 + i);
	}

	
	//Исполнение 1
	{
		Bushing bushing;
		bushing.d = 18;
		bushing.d1 = 5;
		bushing.D = 32;
		bushing.L = 55; 
		bushing.l = 12;
		bushing.c = 1;
		bushing.name[0] = L"31,5";
		bushing.name[1] = Сonversion(bushing.d);
		bushing.name[2] = Сonversion(bushing.d1);
		bushing.name[3] = Сonversion(bushing.D);
		bushing.name[4] = Сonversion(bushing.L);
		bushing.name[5] = Сonversion(bushing.l);
		bushing.name[6] = Сonversion(bushing.c);
		bushing.name[7] = L"0,20";
		vecBushing.push_back(bushing);

		Shaft shaft;
		shaft.D = bushing.d;
		shaft.c = bushing.c;
		shaft.d = bushing.d1;
		shaft.L = (bushing.L - 2) / 2.f + bushing.L * 0.15;
		shaft.l = bushing.L / 2.f - bushing.l - 1;
		vecShaft.push_back(shaft);

		Pin pin;
		pin.d = bushing.d1;
		pin.c = 0.8;
		pin.l = bushing.D;
		pin.d1 = pin.d + pin.l / 50.f;
		pin.name[0] = Сonversion(pin.d);
		pin.name[1] = Сonversion(pin.d1);
		pin.name[2] = Сonversion(pin.l);
		pin.name[3] = Сonversion(pin.c);
		pin.name[4] = L"2,55";
		vecPin.push_back(pin);

		Coupling coupling;
		coupling.name[0] = Сonversion(bushing.D);
		coupling.name[1] = Сonversion(bushing.d);
		coupling.name[2] = Сonversion(bushing.L);
		vecCoupling.push_back(coupling);
	}

	//Исполнение 2
	{
		Bushing bushing;
		bushing.d = 19;
		bushing.d1 = 5;
		bushing.D = 32;
		bushing.L = 55;
		bushing.l = 12;
		bushing.c = 1;
		bushing.name[0] = L"31,5";
		bushing.name[1] = Сonversion(bushing.d);
		bushing.name[2] = Сonversion(bushing.d1);
		bushing.name[3] = Сonversion(bushing.D);
		bushing.name[4] = Сonversion(bushing.L);
		bushing.name[5] = Сonversion(bushing.l);
		bushing.name[6] = Сonversion(bushing.c);
		bushing.name[7] = L"0,17";
		vecBushing.push_back(bushing);

		Shaft shaft;
		shaft.D = bushing.d;
		shaft.c = bushing.c;
		shaft.d = bushing.d1;
		shaft.L = (bushing.L - 2) / 2.f + bushing.L * 0.15;
		shaft.l = bushing.L / 2.f - bushing.l - 1;
		vecShaft.push_back(shaft);

		Pin pin;
		pin.d = bushing.d1;
		pin.c = 0.8;
		pin.l = bushing.D;
		pin.d1 = pin.d + pin.l / 50.f;
		pin.name[0] = Сonversion(pin.d);
		pin.name[1] = Сonversion(pin.d1);
		pin.name[2] = Сonversion(pin.l);
		pin.name[3] = Сonversion(pin.c);
		pin.name[4] = L"2,55";
		vecPin.push_back(pin);

		Coupling coupling;
		coupling.name[0] = Сonversion(bushing.D);
		coupling.name[1] = Сonversion(bushing.d);
		coupling.name[2] = Сonversion(bushing.L);
		vecCoupling.push_back(coupling);
	}

	//Исполнение 3
	{
		Bushing bushing;
		bushing.d = 20;
		bushing.d1 = 5;
		bushing.D = 32;
		bushing.L = 55;
		bushing.l = 12;
		bushing.c = 1;
		bushing.name[0] = L"31,5";
		bushing.name[1] = Сonversion(bushing.d);
		bushing.name[2] = Сonversion(bushing.d1);
		bushing.name[3] = Сonversion(bushing.D);
		bushing.name[4] = Сonversion(bushing.L);
		bushing.name[5] = Сonversion(bushing.l);
		bushing.name[6] = Сonversion(bushing.c);
		bushing.name[7] = L"0,16";
		vecBushing.push_back(bushing);

		Shaft shaft;
		shaft.D = bushing.d;
		shaft.c = bushing.c;
		shaft.d = bushing.d1;
		shaft.L = (bushing.L - 2) / 2.f + bushing.L * 0.15;
		shaft.l = bushing.L / 2.f - bushing.l - 1;
		vecShaft.push_back(shaft);

		Pin pin;
		pin.d = bushing.d1;
		pin.c = 0.8;
		pin.l = bushing.D;
		pin.d1 = pin.d + pin.l / 50.f;
		pin.name[0] = Сonversion(pin.d);
		pin.name[1] = Сonversion(pin.d1);
		pin.name[2] = Сonversion(pin.l);
		pin.name[3] = Сonversion(pin.c);
		pin.name[4] = L"2,55";
		vecPin.push_back(pin);

		Coupling coupling;
		coupling.name[0] = Сonversion(bushing.D);
		coupling.name[1] = Сonversion(bushing.d);
		coupling.name[2] = Сonversion(bushing.L);
		vecCoupling.push_back(coupling);
	}

	//Исполнение 4
	{
		Bushing bushing;
		bushing.d = 20;
		bushing.d1 = 6;
		bushing.D = 38;
		bushing.L = 65;
		bushing.l = 15;
		bushing.c = 1;
		bushing.name[0] = L"50,0";
		bushing.name[1] = Сonversion(bushing.d);
		bushing.name[2] = Сonversion(bushing.d1);
		bushing.name[3] = Сonversion(bushing.D);
		bushing.name[4] = Сonversion(bushing.L);
		bushing.name[5] = Сonversion(bushing.l);
		bushing.name[6] = Сonversion(bushing.c);
		bushing.name[7] = L"0,34";
		vecBushing.push_back(bushing);

		Shaft shaft;
		shaft.D = bushing.d;
		shaft.c = bushing.c;
		shaft.d = bushing.d1;
		shaft.L = (bushing.L - 2) / 2.f + bushing.L * 0.15;
		shaft.l = bushing.L / 2.f - bushing.l - 1;
		vecShaft.push_back(shaft);

		Pin pin;
		pin.d = bushing.d1;
		pin.c = 1;
		pin.l = bushing.D;
		pin.d1 = pin.d + pin.l / 50.f;
		pin.name[0] = Сonversion(pin.d);
		pin.name[1] = Сonversion(pin.d1);
		pin.name[2] = Сonversion(pin.l);
		pin.name[3] = Сonversion(pin.c);
		pin.name[4] = L"4,60";
		vecPin.push_back(pin);

		Coupling coupling;
		coupling.name[0] = Сonversion(bushing.D);
		coupling.name[1] = Сonversion(bushing.d);
		coupling.name[2] = Сonversion(bushing.L);
		vecCoupling.push_back(coupling);
	}
	
	//Исполнение 5
	{
		Bushing bushing;
		bushing.d = 22;
		bushing.d1 = 6;
		bushing.D = 38;
		bushing.L = 65;
		bushing.l = 15;
		bushing.c = 1;
		bushing.name[0] = L"50,0";
		bushing.name[1] = Сonversion(bushing.d);
		bushing.name[2] = Сonversion(bushing.d1);
		bushing.name[3] = Сonversion(bushing.D);
		bushing.name[4] = Сonversion(bushing.L);
		bushing.name[5] = Сonversion(bushing.l);
		bushing.name[6] = Сonversion(bushing.c);
		bushing.name[7] = L"0,30";
		vecBushing.push_back(bushing);

		Shaft shaft;
		shaft.D = bushing.d;
		shaft.c = bushing.c;
		shaft.d = bushing.d1;
		shaft.L = (bushing.L - 2) / 2.f + bushing.L * 0.15;
		shaft.l = bushing.L / 2.f - bushing.l - 1;
		vecShaft.push_back(shaft);

		Pin pin;
		pin.d = bushing.d1;
		pin.c = 1;
		pin.l = bushing.D;
		pin.d1 = pin.d + pin.l / 50.f;
		pin.name[0] = Сonversion(pin.d);
		pin.name[1] = Сonversion(pin.d1);
		pin.name[2] = Сonversion(pin.l);
		pin.name[3] = Сonversion(pin.c);
		pin.name[4] = L"4,60";
		vecPin.push_back(pin);

		Coupling coupling;
		coupling.name[0] = Сonversion(bushing.D);
		coupling.name[1] = Сonversion(bushing.d);
		coupling.name[2] = Сonversion(bushing.L);
		vecCoupling.push_back(coupling);
	}

	//Исполнение 6
	{
		Bushing bushing;
		bushing.d = 24;
		bushing.d1 = 6;
		bushing.D = 38;
		bushing.L = 65;
		bushing.l = 15;
		bushing.c = 1;
		bushing.name[0] = L"50,0";
		bushing.name[1] = Сonversion(bushing.d);
		bushing.name[2] = Сonversion(bushing.d1);
		bushing.name[3] = Сonversion(bushing.D);
		bushing.name[4] = Сonversion(bushing.L);
		bushing.name[5] = Сonversion(bushing.l);
		bushing.name[6] = Сonversion(bushing.c);
		bushing.name[7] = L"0,27";
		vecBushing.push_back(bushing);

		Shaft shaft;
		shaft.D = bushing.d;
		shaft.c = bushing.c;
		shaft.d = bushing.d1;
		shaft.L = (bushing.L - 2) / 2.f + bushing.L * 0.15;
		shaft.l = bushing.L / 2.f - bushing.l - 1;
		vecShaft.push_back(shaft);

		Pin pin;
		pin.d = bushing.d1;
		pin.c = 1;
		pin.l = bushing.D;
		pin.d1 = pin.d + pin.l / 50.f;
		pin.name[0] = Сonversion(pin.d);
		pin.name[1] = Сonversion(pin.d1);
		pin.name[2] = Сonversion(pin.l);
		pin.name[3] = Сonversion(pin.c);
		pin.name[4] = L"4,60";
		vecPin.push_back(pin);

		Coupling coupling;
		coupling.name[0] = Сonversion(bushing.D);
		coupling.name[1] = Сonversion(bushing.d);
		coupling.name[2] = Сonversion(bushing.L);
		vecCoupling.push_back(coupling);
	}
	


	return 0;
}

//Обработчик нажания на одну из шести кнопок
void CCourseProjectView::OnButtonClick(UINT nID)
{
	//Получаем индекс кнопки в массиве m_Buttons
	int buttonIndex = nID - IDC_BUTTON_NEST_1;

	//Задаем путь куда будут сохранятся файлы:
	m_sfilePath = L"C:\\Users\\minch\\Desktop\\Курсовой проект\\Исполнения";
	CString numberIsp;
	numberIsp.Format(L"Исполнение %i", buttonIndex + 1);
	CString targetPath = m_sfilePath + L"\\" + numberIsp;

	//Создание папки с деталями по исполнениям
	if (!CreateDirectory(targetPath, NULL))
	{
		DWORD error = GetLastError();
		if (error == ERROR_ALREADY_EXISTS)
		{
			int index = 1;
			while (true)
			{
				CString indexStr;
				indexStr.Format(L"%i", index);
				CString newFolderName = numberIsp + L" (" + indexStr + L")";
				CString newPath = m_sfilePath + L"\\" + newFolderName;
				if (CreateDirectory(newPath, NULL))
				{
					m_sfilePath = newPath;
					break;
				}
				index++;
			}
		}
		else
			AfxMessageBox(L"Ошибка при создании папки");
	}
	else
	{
		CreateDirectory(targetPath, NULL);
		m_sfilePath = targetPath;
	}

	//Вызываем методы построения деталей и передаем в качестве параметра экземпляр структуры из массива по индексу buttonIndex
	CreateBushing(vecBushing[buttonIndex]);
	CreateShaft(vecShaft[buttonIndex]);
	CreatePin(vecPin[buttonIndex]);
	CreateCoupling(vecPin[buttonIndex], vecShaft[buttonIndex], vecBushing[buttonIndex]);
}

// Метод для создания штифта
void CCourseProjectView::CreatePin(Pin& st)
{
	CoInitialize(NULL);
	HRESULT hRes;
	hRes = kompas.GetActiveObject(L"Kompas.Application.5");
	if (FAILED(hRes))
		kompas.CreateInstance(L"Kompas.Application.5");
	kompas->Visible = true;

	//создание документа КОМПАС:
	ksDocument3DPtr doc;
	doc = kompas->Document3D();
	doc->Create(false, true);
	doc = kompas->ActiveDocument3D();
	ksPartPtr part;
	part = doc->GetPart(pTop_Part);

	//эскиз под вращение:
	ksEntityPtr sketch = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketchDef = sketch->GetDefinition();
	sketchDef->SetPlane(part->GetDefaultEntity(o3d_planeXOY));
	sketch->Create();
	ksDocument2DPtr doc2D = sketchDef->BeginEdit();
	doc2D->ksLineSeg(0, 0, 0, st.d / 2.f, 1);
	doc2D->ksLineSeg(0, st.d / 2.f, st.l, st.d1 / 2.f, 1);
	doc2D->ksLineSeg(st.l, st.d1 / 2.f, st.l, 0, 1);
	doc2D->ksLineSeg(st.l, 0, 0, 0, 1);
	doc2D->ksLineSeg(0, 0, 10, 0, 3); //осевая
	sketchDef->EndEdit();
	
	//операция вращения:
	ksEntityPtr rotation = part->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr rotationDef = rotation->GetDefinition();
	rotationDef->SetSideParam(TRUE, 360);
	rotationDef->directionType = dtNormal;
	rotationDef->SetSketch(sketch);
	rotation->Create();

	//операция фаска
	ksEntityPtr Chamfers = part->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr ChamfersDef = Chamfers->GetDefinition();
	ChamfersDef->SetChamferParam(true, st.c, st.c);
	ksEntityCollectionPtr Collection = part->EntityCollection(o3d_edge);
	ksEntityCollectionPtr CollectionChamfers = ChamfersDef->array();
	Collection->SelectByPoint(0, st.d / 2.f, 0);
	CollectionChamfers->Add(Collection->First());
	Collection->Clear();
	Collection = part->EntityCollection(o3d_edge);
	Collection->SelectByPoint(st.l, st.d1 / 2.f, 0);
	CollectionChamfers->Add(Collection->First());
	Chamfers->Create();

	//операция сохранения детали
	CString name = L"Штифт";
	st.filePath = m_sfilePath;
	doc->fileName = _bstr_t(name);
	st.filePath += L"\\" + name + L".m3d";
	doc->SaveAs(_bstr_t(st.filePath));
	if (!PathFileExists(m_sfilePath)) {
		AfxMessageBox(L"Папка для сохранения не существует!");
		return;
	}
}
// Метод для создания вала
void CCourseProjectView::CreateShaft(Shaft& st)
{
	CoInitialize(NULL);
	HRESULT hRes;
	hRes = kompas.GetActiveObject(L"Kompas.Application.5");
	if (FAILED(hRes))
		kompas.CreateInstance(L"Kompas.Application.5");
	kompas->Visible = true;

	//создание документа КОМПАС:
	ksDocument3DPtr doc;
	doc = kompas->Document3D();
	doc->Create(false, true);
	doc = kompas->ActiveDocument3D();
	ksPartPtr part;
	part = doc->GetPart(pTop_Part);

	//эскиз под выдавливание
	ksEntityPtr sketch = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketchDef = sketch->GetDefinition();
	sketchDef->SetPlane(part->GetDefaultEntity(o3d_planeXOY));
	sketch->Create();
	ksDocument2DPtr doc2D = sketchDef->BeginEdit();
	doc2D->ksCircle(0, 0, st.D / 2.f, 1);
	sketchDef->EndEdit();

	//операция выдавливания 
	ksEntityPtr baseExtr = part->NewEntity(o3d_baseExtrusion);
	ksBaseExtrusionDefinitionPtr ExtrDef = baseExtr->GetDefinition();
	ExtrDef->SetSideParam(TRUE, etBlind, st.L, 0, TRUE);
	ExtrDef->SetSketch(sketch);
	baseExtr->Create();

	//операция фаска
	ksEntityPtr Chamfers = part->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr ChamfersDef = Chamfers->GetDefinition();
	ChamfersDef->SetChamferParam(true, st.c, st.c);
	ksEntityCollectionPtr Collection = part->EntityCollection(o3d_edge);
	Collection->SelectByPoint(st.D / 2.f, 0, st.L);
	ksEntityCollectionPtr CollectionChamfers = ChamfersDef->array();
	CollectionChamfers->Add(Collection->First());
	Chamfers->Create();

	//операция смещенная плоскость
	ksEntityPtr planeXOZ = part->GetDefaultEntity(o3d_planeXOZ);
	ksEntityPtr plane = part->NewEntity(o3d_planeOffset);
	ksPlaneOffsetDefinitionPtr planeDef = plane->GetDefinition();
	planeDef->direction = TRUE;
	planeDef->offset = st.D / 2.f;
	planeDef->SetPlane(planeXOZ);
	plane->Create();

	//эскиз под отверстия
	ksEntityPtr sketch2 = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketchDef2 = sketch2->GetDefinition();
	sketchDef2->SetPlane(plane);
	sketch2->Create();
	ksDocument2DPtr doc2D2 = sketchDef2->BeginEdit();
	doc2D2->ksCircle(0, -(st.L - st.l), st.d / 2.f, 1);
	sketchDef2->EndEdit();

	//операция вырез выдавливанием
	ksEntityPtr CutExtr = part->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr CutExtrDef = CutExtr->GetDefinition();
	CutExtrDef->directionType = dtNormal;
	CutExtrDef->SetSketch(sketch2);
	CutExtrDef->SetSideParam(TRUE, etBlind, st.D, 0, FALSE);
	CutExtr->Create();
	
	//операция сохранения детали
	CString name = L"Вал";
	st.filePath = m_sfilePath;
	doc->fileName = _bstr_t(name);
	st.filePath += L"\\" + name + L".m3d";
	doc->SaveAs(_bstr_t(st.filePath));
}
// Метод для создания втулки
void CCourseProjectView::CreateBushing(Bushing& st)
{
	CoInitialize(NULL);
	HRESULT hRes;
	hRes = kompas.GetActiveObject(L"Kompas.Application.5");
	if (FAILED(hRes))
		kompas.CreateInstance(L"Kompas.Application.5");
	kompas->Visible = true;
	
	//создание документа КОМПАС:
	ksDocument3DPtr doc;
	doc = kompas->Document3D();
	doc->Create(false, true);
	doc = kompas->ActiveDocument3D();
	ksPartPtr part;
	part = doc->GetPart(pTop_Part);

	//эскиз под выдавливание
	ksEntityPtr sketch = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketchDef = sketch->GetDefinition();
	sketchDef->SetPlane(part->GetDefaultEntity(o3d_planeXOY));
	sketch->Create();
	ksDocument2DPtr doc2D = sketchDef->BeginEdit();
	doc2D->ksCircle(0, 0, st.D / 2.f, 1);
	doc2D->ksCircle(0, 0, st.d / 2.f, 1);
	sketchDef->EndEdit();
	
	//операция выдавливания 
	ksEntityPtr baseExtr = part->NewEntity(o3d_baseExtrusion);
	ksBaseExtrusionDefinitionPtr ExtrDef = baseExtr->GetDefinition();
	ExtrDef->SetSideParam(TRUE, etBlind, st.L, 0, TRUE);
	ExtrDef->SetSketch(sketch);
	baseExtr->Create();

	//операция смещенная плоскость
	ksEntityPtr planeXOZ = part->GetDefaultEntity(o3d_planeXOZ);
	ksEntityPtr plane = part->NewEntity(o3d_planeOffset);
	ksPlaneOffsetDefinitionPtr planeDef = plane->GetDefinition();
	planeDef->direction = TRUE;
	planeDef->offset = st.D / 2.f;
	planeDef->SetPlane(planeXOZ);
	plane->Create();

	//эскиз под отверстия
	ksEntityPtr sketch2 = part->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr sketchDef2 = sketch2->GetDefinition();
	sketchDef2->SetPlane(plane);
	sketch2->Create();
	ksDocument2DPtr doc2D2 = sketchDef2->BeginEdit();
	doc2D2->ksCircle(0, -st.l, st.d1 / 2.f, 1);
	doc2D2->ksCircle(0, -(st.L - st.l), st.d1 / 2.f, 1);
	sketchDef2->EndEdit();
	
	//операция вырез выдавливанием
	ksEntityPtr CutExtr = part->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr CutExtrDef = CutExtr->GetDefinition();
	CutExtrDef->directionType = dtNormal;
	CutExtrDef->SetSketch(sketch2);
	CutExtrDef->SetSideParam(TRUE, etBlind, st.D, 0, FALSE);
	CutExtr->Create();

	//операция фаска
	ksEntityPtr Chamfers = part->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr ChamfersDef = Chamfers->GetDefinition();
	ChamfersDef->SetChamferParam(true, st.c, st.c);
	ksEntityCollectionPtr Collection = part->EntityCollection(o3d_edge);
	ksEntityCollectionPtr CollectionChamfers = ChamfersDef->array();
	Collection->SelectByPoint(0, st.d / 2.f, 0);
	CollectionChamfers->Add(Collection->First());
	Collection->Clear();
	Collection = part->EntityCollection(o3d_edge);
	Collection->SelectByPoint(0, st.D / 2.f, 0);
	CollectionChamfers->Add(Collection->First());
	Collection->Clear();
	Collection = part->EntityCollection(o3d_edge);
	Collection->SelectByPoint(0, st.d / 2.f, st.L);
	CollectionChamfers->Add(Collection->First());
	Collection->Clear();
	Collection = part->EntityCollection(o3d_edge);
	Collection->SelectByPoint(0, st.D / 2.f, st.L);
	CollectionChamfers->Add(Collection->First());
	Chamfers->Create();

	//операция сохранения детали
	CString name = L"Втулка";
	st.filePath = m_sfilePath;
	doc->fileName = _bstr_t(name);
	st.filePath += L"\\" + name + L".m3d";
	doc->SaveAs(_bstr_t(st.filePath));
}
// Метод для создания всей сборки 
void CCourseProjectView::CreateCoupling(Pin pin, Shaft shaft, Bushing bushing)
{
	CoInitialize(NULL);
	HRESULT hRes;
	hRes = kompas.GetActiveObject(L"Kompas.Application.5");
	if (FAILED(hRes))
		kompas.CreateInstance(L"Kompas.Application.5");
	kompas->Visible = true;

	//создание документа КОМПАС :
	ksDocument3DPtr doc;
	doc = kompas->Document3D();
	doc->Create(false, false);
	doc = kompas->ActiveDocument3D();
	ksPartPtr part;
	part = doc->GetPart(pTop_Part);

	//добавление детали "Втулка"
	doc->SetPartFromFile(_bstr_t(bushing.filePath), part, TRUE);
	ksPartPtr partbushing = doc->GetPart(0);
	ksEntityCollectionPtr bushingCollection = partbushing->EntityCollection(o3d_edge);
	//ребро 1
	ksEntityPtr edgebushing;
	bushingCollection->SelectByPoint(0, bushing.d / 2.f + bushing.c, 0);
	edgebushing = bushingCollection->First();
	//грань 1
	ksEntityPtr facebushing;
	bushingCollection->Clear();
	bushingCollection = partbushing->EntityCollection(o3d_face);
	bushingCollection->SelectByPoint(bushing.d1 / 2.f, (bushing.D - bushing.d) / 4.f + bushing.d / 2.f, bushing.l);
	facebushing = bushingCollection->First();
	//грань 2
	ksEntityPtr facebushing2;
	bushingCollection->Clear();
	bushingCollection = partbushing->EntityCollection(o3d_face);
	bushingCollection->SelectByPoint(bushing.d1 / 2.f, (bushing.D - bushing.d) / 4.f + bushing.d / 2.f, bushing.L - bushing.l);
	facebushing2 = bushingCollection->First();
	//грань 3
	ksEntityPtr facebushing3;
	bushingCollection->Clear();
	bushingCollection = partbushing->EntityCollection(o3d_face);
	bushingCollection->SelectByPoint(0, bushing.D / 2.f, bushing.L / 2.f);
	facebushing3 = bushingCollection->First();

	//добавление детали "Вал" x1
 	doc->SetPartFromFile(_bstr_t(shaft.filePath), part, TRUE);
	ksPartPtr partshaft = doc->GetPart(1);
	ksEntityCollectionPtr shaftCollection = partshaft->EntityCollection(o3d_edge);
	//ребро 1
	ksEntityPtr edgeshaft;
	shaftCollection->SelectByPoint(0, shaft.D / 2.f, 0);
	edgeshaft = shaftCollection->First();
	//грань 
	ksEntityPtr faceshaft;
	shaftCollection->Clear();
	shaftCollection = partshaft->EntityCollection(o3d_face);
	shaftCollection->SelectByPoint(shaft.d / 2.f, 0, shaft.L - shaft.l);
	faceshaft = shaftCollection->First();

	//добавление детали "Вал" x2
	doc->SetPartFromFile(_bstr_t(shaft.filePath), part, TRUE);
	ksPartPtr partshaft2 = doc->GetPart(2);
	ksEntityCollectionPtr shaftCollection2 = partshaft2->EntityCollection(o3d_edge);
	//ребро 1
	ksEntityPtr edgeshaft2;
	shaftCollection2->SelectByPoint(0, shaft.D / 2.f, 0);
	edgeshaft2 = shaftCollection2->First();
	//грань 
	ksEntityPtr faceshaft2;
	shaftCollection2->Clear();
	shaftCollection2 = partshaft2->EntityCollection(o3d_face);
	shaftCollection2->SelectByPoint(shaft.d / 2.f, 0, shaft.L - shaft.l);
	faceshaft2 = shaftCollection2->First();

	//добавление детали "Штифт" x1
	doc->SetPartFromFile(_bstr_t(pin.filePath), part, TRUE);
	ksPartPtr partpin = doc->GetPart(3);
	ksEntityCollectionPtr pinCollection = partpin->EntityCollection(o3d_face);
	//грань 
	ksEntityPtr facepin;
	pinCollection->SelectByPoint(pin.l, 0, 0);
	facepin = pinCollection->First();
	//ребро
	ksEntityPtr edgepin;
	pinCollection->Clear();
	pinCollection = partpin->EntityCollection(o3d_edge);
	pinCollection->SelectByPoint(pin.l, pin.d1 / 2.f - pin.c, 0);
	edgepin = pinCollection->First();

	//добавление детали "Штифт" x2
	doc->SetPartFromFile(_bstr_t(pin.filePath), part, TRUE);
	ksPartPtr partpin2 = doc->GetPart(4);
	ksEntityCollectionPtr pinCollection2 = partpin2->EntityCollection(o3d_face);
	//грань 
	ksEntityPtr facepin2;
	pinCollection2->SelectByPoint(pin.l, 0, 0);
	facepin2 = pinCollection2->First();
	//ребро
	ksEntityPtr edgepin2;
	pinCollection2->Clear();
	pinCollection2 = partpin2->EntityCollection(o3d_edge);
	pinCollection2->SelectByPoint(pin.l, pin.d1 / 2.f - pin.c, 0);
	edgepin2 = pinCollection2->First();

	//Установка сопряжений
	doc->AddMateConstraint(mc_Concentric, edgebushing, edgeshaft, 1, 0, NULL);
	doc->AddMateConstraint(mc_Concentric, edgebushing, edgeshaft2, -1, 0, NULL);
	doc->AddMateConstraint(mc_Concentric, facebushing, faceshaft, 1, 0, NULL);
	doc->AddMateConstraint(mc_Concentric, facebushing2, faceshaft2, 1, 0, NULL);
	doc->AddMateConstraint(mc_Concentric, facebushing, edgepin, 1, 0, NULL);
	doc->AddMateConstraint(mc_Tangency, facepin, facebushing3, -1, 0, NULL);
	doc->AddMateConstraint(mc_Concentric, facebushing2, edgepin2, -1, 0, NULL);
	doc->AddMateConstraint(mc_Tangency, facepin2, facebushing3, -1, 0, NULL);

	//операция сохранения детали
	CString name = L"Втулочная муфта";
	CString filePath = m_sfilePath;
	doc->fileName = _bstr_t(name);
	filePath += L"\\" + name + L".a3d";
	doc->SaveAs(_bstr_t(filePath));
}
// Метод для создания изображения
int CCourseProjectView::CreateImage(CDC* pDC, int Width, CString name_file)
{
	CImage image;
	image.Load(name_file);

	if (image.IsNull())
	{
		AfxMessageBox(L"Ошибка загрузки картинки");
		return 10;
	}

	int imageWidth = image.GetWidth();		//Ширина картинки
	int imageHeight = image.GetHeight();	//Высота картинки

	image.StretchBlt
	(
		pDC->GetSafeHdc(), Width / 2.f - imageWidth / 2.f, 0,
		imageWidth, imageHeight, 0, 0,
		imageWidth, imageHeight, SRCCOPY
	);

	return imageHeight;

}
// Служебный метод для преобразования числа в строку
CString CCourseProjectView::Сonversion(double number)
{
	CString buff;
	buff.Format(L"%f", number);

	int dotIndex = buff.Find(L".");

	if (dotIndex != -1)
	{
		int Index = buff.GetLength() - 1;

		while (Index > dotIndex && buff[Index] == _T('0'))
			Index--;

		if (Index > dotIndex)
			buff = buff.Left(Index + 1);
		else
			buff = buff.Left(dotIndex);
	}

	buff.Replace(L".", L",");

	return buff;
}
