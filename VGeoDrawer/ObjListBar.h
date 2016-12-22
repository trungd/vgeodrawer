#pragma once
#include "sizecbar.h"
#include "GeoObjTree.h"

//#define ID_COMMAND_LIST 1000

class CObjListBar :
	public CSizingControlBar
{
public:
	CObjListBar(void);
public:
	~CObjListBar(void);
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
	CGeoObjTree m_tree;
	CStatic m_static;
};