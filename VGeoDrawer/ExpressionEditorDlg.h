#pragma once
#include "afxwin.h"


// CExpressionEditorDlg dialog

class CExpressionEditorDlg : public CDialog
{
	DECLARE_DYNAMIC(CExpressionEditorDlg)

public:
	CExpressionEditorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CExpressionEditorDlg();

// Dialog Data
	enum { IDD = IDD_EXPRESSIONEDITORDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString strExp;
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnCbnSelchangeComboFuncNum();
public:
	afx_msg void OnCbnSelchangeComboFuncBool();
public:
	CComboBox m_cbNum;
public:
	CComboBox m_cbBool;
public:
	CEdit m_Edit;
public:
	afx_msg void OnEnChangeEditExp();
private:
	Bitmap* bmp;
	afx_msg void OnPaint();
};
