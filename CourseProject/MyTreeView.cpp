// MyTreeView.cpp: файл реализации
//

#include "pch.h"
#include "CourseProject.h"
#include "MyTreeView.h"
#include "CourseProjectDoc.h"
#include "CourseProjectView.h"

// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

CMyTreeView::~CMyTreeView()
{
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Диагностика CMyTreeView

#ifdef _DEBUG
void CMyTreeView::FillTree()
{
	CTreeCtrl& tree = GetTreeCtrl();

	tree.DeleteAllItems();

	m_hCoupling = tree.InsertItem(L"Втулочная муфта", -1, -1, NULL, TVI_FIRST);

	m_hBushing = tree.InsertItem(L"Втулка", -1, -1, m_hCoupling, TVI_FIRST);
	m_hPin = tree.InsertItem(L"Штифт", -1, -1, m_hCoupling, TVI_FIRST);

	tree.SetCheck(m_hBushing, m_pDoc->m_bBushing);
	tree.SetCheck(m_hPin, m_pDoc->m_bPin);

	tree.Expand(m_hCoupling, TVE_EXPAND);
}
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений CMyTreeView


int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS;
	
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}


void CMyTreeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CTreeCtrl& tree = GetTreeCtrl();

	CRect rc;

	tree.GetItemRect(m_hCoupling, &rc, false);
	if (rc.PtInRect(point))
		tree.SelectItem(m_hCoupling);

	tree.GetItemRect(m_hBushing, &rc, false);
	if (rc.PtInRect(point))
		tree.SelectItem(m_hBushing);

	tree.GetItemRect(m_hPin, &rc, false);
	if (rc.PtInRect(point))
		tree.SelectItem(m_hPin);

	if (tree.GetSelectedItem() == m_hCoupling)
	{
		m_pDoc->m_bCoupling = TRUE;
		m_pDoc->m_bBushing = FALSE;
		m_pDoc->m_bPin = FALSE;
	}

	if (tree.GetSelectedItem() == m_hBushing)
	{
		m_pDoc->m_bBushing = TRUE;
		m_pDoc->m_bCoupling = FALSE;
		m_pDoc->m_bPin = FALSE;
	}

	if (tree.GetSelectedItem() == m_hPin)
	{
		m_pDoc->m_bPin = TRUE;
		m_pDoc->m_bCoupling = FALSE;
		m_pDoc->m_bBushing = FALSE;
	}

	m_pDoc->m_pView->Invalidate();
	CTreeView::OnLButtonDown(nFlags, point);
}
