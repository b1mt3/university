
// course_work.h : ������� ���� ��������� ��� ���������� course_work
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������


// Ccourse_workApp:
// � ���������� ������� ������ ��. course_work.cpp
//

class Ccourse_workApp : public CWinAppEx
{
public:
	Ccourse_workApp();


// ���������������
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����������
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ccourse_workApp theApp;
