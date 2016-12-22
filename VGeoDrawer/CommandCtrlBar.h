#pragma once
#include "sizecbar.h"
#include "CommandEdit.h"
#include "CmdEdit\CmdEdit.h"
#include "CommandPromptListBox.h"

#define ID_COMMAND_LIST 1

class CCommandCtrlBar :
	public CSizingControlBar
{
public:
	CCommandCtrlBar(void);
public:
	~CCommandCtrlBar(void);
public:
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHandler);
	//CCmdEdit m_Edit;
	CCommandPromptListBox m_List;
	virtual void DoDataExchange(CDataExchange* pDX);
protected:	
	//{{AFX_MSG(CCommandCtrlBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void AddCommand(CString str);
	CSize CalcDynamicLayout(int nLength, DWORD dwMode);
};