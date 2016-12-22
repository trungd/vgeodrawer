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
	CString m_Cmd;
	CString m_FileName;
	CToolBar m_ToolBar;

// Dialog Data
	enum { IDD = IDD_ADD_TOOLBOX_ITEM };

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
public:
	virtual BOOL OnInitDialog();
public:
	CComboBox m_cmdNameCombo;
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
};
