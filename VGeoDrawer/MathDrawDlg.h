#pragma once
#include "afxwin.h"


// CMathDrawDlg dialog

class CMathDrawDlg : public CDialog
{
	DECLARE_DYNAMIC(CMathDrawDlg)

public:
	CMathDrawDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMathDrawDlg();
	CToolBar m_ToolBar;

// Dialog Data
	enum { IDD = IDD_MATHDRAWWND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit();
	Bitmap* bmp;
public:
	afx_msg void OnPaint();
public:
	virtual BOOL OnInitDialog();
	void OnExponent();
	void OnSubText();
	void OnFraction();
	void OnSquareRoot();
	void OnRoot();
public:
	CStatic m_staticTBar;
public:
	BOOL m_bLaTex;
public:
	CEdit m_Edit;
};
