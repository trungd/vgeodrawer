#pragma once
#include "sizecbar.h"
#include "CommandEdit.h"
#include "CmdEdit\CmdEdit.h"
#include "CommandPromptListBox.h"
#include "VGeoDrawerView.h"

#define ID_WATCH_LIST 1

class CWatchBar :
	public CSizingControlBar
{
public:
	CWatchBar(void);
public:
	~CWatchBar(void);
public:
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHandler);
	CListCtrl m_List;
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
	void Reload();
	void OnListViewRClick(NMHDR *pNMHDR, LRESULT *pResult);
	CVGObjContainer* m_objCont;
	CVGeoDrawerView* pView;
public:
	void OnListGetDispInfo(NMHDR *pNMHDR, LRESULT *pResult);
	void OnListEndLabelEdit(NMHDR *pNMHDR, LRESULT *pResult);
	void AddWatch();
	void OnListKeyDown(NMHDR *pNMHDR, LRESULT *pResult);
	void OnListLDbClick(NMHDR *pNMHDR, LRESULT *pResult);
};