
// course_work.h : главный файл заголовка для приложения course_work
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// Ccourse_workApp:
// О реализации данного класса см. course_work.cpp
//

class Ccourse_workApp : public CWinAppEx
{
public:
	Ccourse_workApp();


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ccourse_workApp theApp;
