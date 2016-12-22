#include "StdAfx.h"
#include "PageViewBar.h"

BEGIN_MESSAGE_MAP(CPageViewBar, CSizingControlBar)
	//{{AFX_MSG_MAP(CObjListBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

CPageViewBar::CPageViewBar(void)
{
}

CPageViewBar::~CPageViewBar(void)
{

}

int CPageViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	//m_objListWnd=new CObjListWnd(this);
	//m_objListWnd->ShowWindow(SW_SHOW);
	m_PageListBox.Create(WS_VISIBLE | WS_CHILD | WS_VSCROLL | LBS_OWNERDRAWFIXED | LBS_NOINTEGRALHEIGHT, CRect(0,0,0,0),this,1);
	m_PageListBox.ModifyStyleEx(0,WS_EX_CLIENTEDGE);

	return 0;
}

void CPageViewBar::OnSize(UINT nType, int cx, int cy)
{
	CSizingControlBar::OnSize(nType, cx, cy);

	m_PageListBox.MoveWindow(CRect(0,0,cx,cy));
}

void CPageViewBar::DoDataExchange(CDataExchange* pDX)
{
	CSizingControlBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommandWnd)
	//DDX_Control(pDX,ID_COMMAND_EDIT,m_Edit);
	//DDX_Control(pDX,1,m_PageListBox);
	//}}AFX_DATA_MAP}
}

void CPageViewBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHandler)
{
	CSizingControlBar::OnUpdateCmdUI(pTarget, bDisableIfNoHandler);
	UpdateDialogControls(pTarget, bDisableIfNoHandler);
}