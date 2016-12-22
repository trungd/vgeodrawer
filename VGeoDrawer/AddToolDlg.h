#pragma once
#include "afxwin.h"


// CAddToolDlg dialog

class CAddToolDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddToolDlg)

public:
	CAddToolDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddToolDlg();
	HBITMAP hBmp;

// Dialog Data
	enum { IDD = IDD_ADDTOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedEditIcon();
	afx_msg void OnBnClickedAdd1();
	afx_msg void OnBnClickedAdd2();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheck2();
public:
	CString m_ToolName;
public:
	CString m_Command;
public:
	CString m_CommandInput;
public:
	CString m_CommandOutput;
public:
	CString m_ConstructionInput;
public:
	CEdit m_ConstructionOutput;
public:
	CString m_CommandName;
public:
	BOOL m_bAddByCommand;
public:
	BOOL m_bAddByConstruction;
public:
	CString m_Description;
public:
	afx_msg void OnBnClickedOk();
public:
	BOOL m_bAddTBItem;
protected:
	virtual void OnOK();
};
