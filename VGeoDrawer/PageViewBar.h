#pragma once
#include "sizecbar.h"
#include "PageListBox.h"

class CPageViewBar :
	public CSizingControlBar
{
public:
	CPageViewBar(void);
public:
	~CPageViewBar(void);
public:
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHandler);
	virtual void DoDataExchange(CDataExchange* pDX);
protected:	
	//{{AFX_MSG(CObjListBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CPageListBox m_PageListBox;
};