#pragma once
#include "sizecbar.h"
#include "ConstructionStepsListBox.h"
#include "VGObjContainer.h"

class CConstructionStepsBar :
	public CSizingControlBar
{
public:
	CConstructionStepsBar(void);
	~CConstructionStepsBar(void);
public:
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHandler);
	CConstructionStepsListBox m_List;
	virtual void DoDataExchange(CDataExchange* pDX);
	void Reload();
	CVGObjContainer* m_objArray;
protected:	
	//{{AFX_MSG(CCommandCtrlBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void AddCommand(CString str);
};
