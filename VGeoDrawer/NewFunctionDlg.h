#pragma once


// CNewFunctionDlg dialog

class CNewFunctionDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewFunctionDlg)

public:
	CNewFunctionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewFunctionDlg();

// Dialog Data
	enum { IDD = IDD_NEWFUNCTIONDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnCbnSelchangeComboFunctype();
public:
	afx_msg void OnBnClickedOk();
};
