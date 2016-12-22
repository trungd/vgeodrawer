#pragma once
#include "afxwin.h"


// CPresSetting dialog

class CPresSetting : public CDialog
{
	DECLARE_DYNAMIC(CPresSetting)

public:
	CPresSetting(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPresSetting();

// Dialog Data
	enum { IDD = IDD_PRES_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_chkPresWhenStart;
public:
	BOOL m_chkAskWhenClose;
public:
	afx_msg void OnBnClickedOk();
};
