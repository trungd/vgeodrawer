#include "CmdEdit\CmdEdit.h"
#include "VGObjContainer.h"
#pragma once


// CCommandPromptListBox

class CCommandPromptListBox : public CListBox
{
	DECLARE_DYNAMIC(CCommandPromptListBox)

public:
	CCommandPromptListBox();
	virtual ~CCommandPromptListBox();

	CCmdEdit m_Edit;
	int m_currentEditLine;

	bool m_bIBeam;
	
	CVGObjContainer* m_objContainer;

	virtual void Create(const RECT& rect, CWnd* pParentWnd, UINT nID);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
public:
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
public:
	afx_msg void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
public:
	afx_msg int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg void OnLbnSelchange();
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	LRESULT OnEditEnter(WPARAM wParam, LPARAM lParam);
	void SetCurrentEdit(int nIndex);
	int GetOutputHeight(CString strOutput);
	void Reset();
public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};


