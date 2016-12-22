#include "Script/ScriptObject.h"
#pragma once#include "scriptedit.h"



// CScriptDlg dialog

class CScriptDlg : public CDialog
{
	DECLARE_DYNAMIC(CScriptDlg)

public:
	CScriptDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScriptDlg();

// Dialog Data
	enum { IDD = IDD_SCRIPTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSelectFile();

	CScriptObject* m_DocScriptObj;
	CScriptObject m_ScriptObj;
public:
	afx_msg void OnBnClickedCheckError();
public:
	CScriptEdit m_Edit;
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedRun();
	BOOL UpdateScript();
public:
	afx_msg void OnBnClickedSetDefault();
public:
	afx_msg void OnBnClickedAddFunction();
public:
	CString m_strCode;
};
