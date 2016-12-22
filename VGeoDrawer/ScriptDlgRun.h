#pragma once
#include "afxwin.h"
#include "Script\ScriptObject.h"


// CScriptDlgRun dialog

class CScriptDlgRun : public CDialog
{
	DECLARE_DYNAMIC(CScriptDlgRun)

public:
	CScriptDlgRun(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScriptDlgRun();

// Dialog Data
	enum { IDD = IDD_SCRIPTDLGRUN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_FuncList;
public:
	CString m_strParam;
public:
	CString m_strResult;
public:
	CScriptObject* m_ScriptObj;
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedRun();
};
