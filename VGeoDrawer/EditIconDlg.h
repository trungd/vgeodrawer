#pragma once
#include "VGeoDrawerDoc.h"
#include "afxwin.h"
#include "IconEditor.h"
#include "ColorPicker.h"

// CEditIconDlg dialog

class CEditIconDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditIconDlg)

public:
	CEditIconDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditIconDlg();
	CToolBar m_ToolBar;
	Bitmap* bmp;

// Dialog Data
	enum { IDD = IDD_EDIT_ICON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedIconBtn();
	afx_msg void OnIconPen();
	afx_msg void OnIconLine();
	afx_msg void OnIconRect();
	afx_msg void OnIconEllipse();
	afx_msg void OnIconPoint();
	afx_msg void OnIconClrSel();
	virtual BOOL OnInitDialog();
public:
	CIconEditor m_IconEditor;
protected:
	virtual void OnOK();
public:
	CColorPicker m_ColorPicker;
public:
	CStatic m_staticTBar;
public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButtonClear();
public:
//	afx_msg void OnBnClickedCheck1();
public:
	CButton m_chkAntiAlias;
public:
	afx_msg void OnBnClickedCheckAntialias();
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnIconFill();
public:
//	afx_msg void OnStnClickedStaticPreview();
public:
	CStatic m_staticPreview;
};
