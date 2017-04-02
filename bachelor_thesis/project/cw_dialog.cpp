// cw_dialog.cpp : implementation file
//

#include "stdafx.h"
#include "course_work.h"
#include "cw_dialog.h"
#include "afxdialogex.h"


// cw_dialog dialog

IMPLEMENT_DYNAMIC(cw_dialog, CDialogEx)

cw_dialog::cw_dialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(cw_dialog::IDD, pParent)
{

}

cw_dialog::~cw_dialog()
{
}

void cw_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(cw_dialog, CDialogEx)
END_MESSAGE_MAP()


// cw_dialog message handlers
