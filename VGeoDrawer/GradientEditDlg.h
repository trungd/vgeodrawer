#include "VGObject.h"
#pragma once#include "colorbutton.h"
#include "afxwin.h"



// CGradientEditDlg dialog

class CGradientEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CGradientEditDlg)

public:
	CGradientEditDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGradientEditDlg();

// Dialog Data
	enum { IDD = IDD_EDIT_GRADIENT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CVGGradientStyle m_grStyle;
	CVGGradientStyle m_grTitleStyle;
public:
	afx_msg void OnPaint();
	LRESULT OnColorChanged(WPARAM wParam, LPARAM lParam);
public:
	CColorButton m_btnColor1;
public:
	CColorButton m_btnColor2;
public:
	afx_msg void OnCbnSelchangeComboGrMode();
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedOk();
public:
	CColorButton m_btnTitleColor1;
public:
	CColorButton m_btnTitleColor2;
public:
	CColorButton m_btnBorderClr;
public:
	afx_msg void OnBnClickedBtnSelectFont();
public:
	BOOL m_bTitle;
public:
	int m_nTitleHeight;
	LOGFONT m_Font;
	CString m_strTitle;
	Color m_TextColor;
public:
	void SetStyle(int nID);
public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedBtnChooseStyle();
};
