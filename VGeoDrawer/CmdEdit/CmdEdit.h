#pragma once

#include "ParamToolTipCtrl.h"
#include "..\CommandArray.h"
#include "..\VGObject.h"

// CCmdEdit

#define WM_EDIT_ENTER WM_USER+5

class CCmdEdit : public CEdit
{
	DECLARE_DYNAMIC(CCmdEdit)

public:
	CCmdEdit();
	virtual ~CCmdEdit();

	CStringArray m_wordArray;

	CCommandArray* m_cmdArray;

	HWND hwndTT;
	TOOLINFO ti;

protected:
	DECLARE_MESSAGE_MAP()

	CParamTooltipCtrl m_wndTT;
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	CString GetLastWord();
	CComboBox m_List;
	afx_msg void OnEnChange();
	CFont fontTahoma;
	CFont fontCourierNew;
	CArray<CVGObject*>* m_objArr;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	void ReplaceLastWord(CString strText);
	void FillList();
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	void ShowDropDown();
	void InitCtrl();
	void ShowParamToolTip();
	afx_msg void OnKillFocus(CWnd*);
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};


