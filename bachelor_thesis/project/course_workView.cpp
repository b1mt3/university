
// course_workView.cpp : реализаци€ класса Ccourse_workView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позвол€ет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "course_work.h"
#endif

#define _USE_MATH_DEFINES

#include "course_workDoc.h"
#include "course_workView.h"
#include <math.h>
#include "controller.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Ccourse_workView

IMPLEMENT_DYNCREATE(Ccourse_workView, CView)

BEGIN_MESSAGE_MAP(Ccourse_workView, CView)
	// —тандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Ccourse_workView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// создание/уничтожение Ccourse_workView

Ccourse_workView::Ccourse_workView()
{
	// TODO: добавьте код создани€

}

Ccourse_workView::~Ccourse_workView()
{
}

BOOL Ccourse_workView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменени€
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// рисование Ccourse_workView

void Ccourse_workView::OnDraw(CDC* unit/*pDC*/)
{
//variables' announcements & initializations
	char *file = "in.txt";
	double step = M_PI/200, *coords;
	Ccourse_workDoc* pDoc = GetDocument();
	CRect Recto;
	CPen PenBlue(PS_SOLID, 1, RGB(0, 0, 255));
	unit->SelectObject(PenBlue);
	CSize lp_wind, lp_view;
	LPSIZE lp_w, lp_v;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	unit->SetMapMode(MM_ANISOTROPIC);
//drawing classical cartesian CS
	GetClientRect(&Recto);
	unit->MoveTo(Recto.Width() / 2, 0);
	unit->LineTo(Recto.Width() / 2, Recto.Height());
	unit->MoveTo(0, Recto.Height() / 2);
	unit->LineTo(Recto.Width(), Recto.Height() / 2);
//setting new CS origin
	unit->SetViewportOrg(Recto.Width() / 2, Recto.Height() / 2);
//setting visible drawing area's size
	unit->SetWindowExt(800, 600);
//settint new Y-axis orientation, a natural one
	unit->SetViewportExt(Recto.Width(), -Recto.Height());
//converting from logical coordinates to device coordinates
	lp_wind = unit->GetWindowExt();
	lp_view = unit->GetViewportExt();
	lp_w = &lp_wind;
	lp_v = &lp_view;
	unit->LPtoDP(lp_w);
	unit->LPtoDP(lp_v);
//reading input file, start coordinates calculation
	controller m(file, unit);
//drawing
	CPen PenRed(PS_SOLID, 1, RGB(255, 0, 0));
	unit->SelectObject(PenRed);
	for (double rad = 50; rad < 1000; rad += 150)
		for (double f = 0; f < 2*M_PI; f += step)
		{
			coords = m.init_ellips(f, rad);
			if (f == 0)
			{
				unit->MoveTo(coords[0], coords[1]);
			}
			unit->LineTo(coords[0], coords[1]);
		}
	// TODO: добавьте здесь код отрисовки дл€ собственных данных
}


// печать Ccourse_workView


void Ccourse_workView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Ccourse_workView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void Ccourse_workView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void Ccourse_workView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void Ccourse_workView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Ccourse_workView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// диагностика Ccourse_workView

#ifdef _DEBUG
void Ccourse_workView::AssertValid() const
{
	CView::AssertValid();
}

void Ccourse_workView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ccourse_workDoc* Ccourse_workView::GetDocument() const // встроена неотлаженна€ верси€
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ccourse_workDoc)));
	return (Ccourse_workDoc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений Ccourse_workView
