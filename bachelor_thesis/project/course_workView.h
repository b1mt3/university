
// course_workView.h : интерфейс класса Ccourse_workView
//

#pragma once


class Ccourse_workView : public CView
{
protected: // создать только из сериализации
	Ccourse_workView();
	DECLARE_DYNCREATE(Ccourse_workView)

// Атрибуты
public:
	Ccourse_workDoc* GetDocument() const;

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
	virtual ~Ccourse_workView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // отладочная версия в course_workView.cpp
inline Ccourse_workDoc* Ccourse_workView::GetDocument() const
   { return reinterpret_cast<Ccourse_workDoc*>(m_pDocument); }
#endif

