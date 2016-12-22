#include "BtnItem.h"
#pragma once

#define WM_MENUCLICK WM_USER+2
#define BTN_DISTANCE 3
#define BTN_HEIGHT 40

// CButtonPopup

class CButtonPopup : public CWnd
{
	DECLARE_DYNAMIC(CButtonPopup)

public:
	CButtonPopup();
	virtual ~CButtonPopup();
	CArray<CBtnItem*,CBtnItem*> m_btnArray;
	void AddButton(CString str,HICON hIcon);
	void DeleteAllButtons();

	void Popup(CPoint pt);

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(CWnd* pParentWnd);
	void ClosePopup();
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	CWnd* m_pParentWnd;
public:
	afx_msg void OnActivateApp(BOOL bActive, DWORD dwThreadID);
public:
	afx_msg BOOL OnNcActivate(BOOL bActive);
	LRESULT OnBtnClk(WPARAM wParam, LPARAM lParam);
};


