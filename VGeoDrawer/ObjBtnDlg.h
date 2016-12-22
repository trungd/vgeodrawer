#include "BtnItem.h"
#pragma once

#define WM_MENUCLICK WM_USER+2
#define BTN_DISTANCE 3
#define BTN_HEIGHT 40
// CObjBtnDlg dialog

class CObjBtnDlg : public CDialog
{
	DECLARE_DYNAMIC(CObjBtnDlg)

public:
	CObjBtnDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CObjBtnDlg();

// Dialog Data
	enum { IDD = IDD_OBJBTNDLG };
	CArray<CBtnItem*,CBtnItem*> m_btnArray;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	void DeleteAllButtons();
	void AddButton(CString str,HICON hIcon);
public:
//	afx_msg void OnClose();
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void Popup(CPoint pt);
	void SetSelection(int nSelection);
	CWnd* tbWnd;
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
public:
	afx_msg void OnPaint();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	virtual BOOL Create(CWnd* pParentWnd);
public:
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};
