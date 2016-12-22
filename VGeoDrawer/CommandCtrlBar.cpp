#include "StdAfx.h"
#include "CommandCtrlBar.h"

BEGIN_MESSAGE_MAP(CCommandCtrlBar, CSizingControlBar)
	//{{AFX_MSG_MAP(CCommandCtrlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
//	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CCommandCtrlBar::CCommandCtrlBar(void)
{
}

CCommandCtrlBar::~CCommandCtrlBar(void)
{
}

int CCommandCtrlBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_List.Create(CRect(0,0,0,0),this,ID_COMMAND_LIST);
	//m_Edit.ModifyStyleEx(0,WS_EX_CLIENTEDGE);

	return 0;
}

void CCommandCtrlBar::OnSize(UINT nType, int cx, int cy)
{
	CSizingControlBar::OnSize(nType, cx, cy);
	m_List.MoveWindow(CRect(0,0,cx,cy));
}

void CCommandCtrlBar::DoDataExchange(CDataExchange* pDX)
{
	CSizingControlBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommandWnd)
	//DDX_Control(pDX,ID_COMMAND_LIST,m_List);
	//}}AFX_DATA_MAP}
}

void CCommandCtrlBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHandler)
{
	CSizingControlBar::OnUpdateCmdUI(pTarget, bDisableIfNoHandler);
	UpdateDialogControls(pTarget, bDisableIfNoHandler);
}

CSize CCommandCtrlBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
	CSize size=CSizingControlBar::CalcDynamicLayout(nLength,dwMode);
	//size.cy=30;
	return size;
}