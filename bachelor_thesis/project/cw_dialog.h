#pragma once


// cw_dialog dialog

class cw_dialog : public CDialogEx
{
	DECLARE_DYNAMIC(cw_dialog)

public:
	cw_dialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~cw_dialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
