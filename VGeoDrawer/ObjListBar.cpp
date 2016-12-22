#include "StdAfx.h"
#include "ObjListBar.h"

BEGIN_MESSAGE_MAP(CObjListBar, CSizingControlBar)
	//{{AFX_MSG_MAP(CObjListBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	//	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CObjListBar::CObjListBar(void)
{
}

CObjListBar::~CObjListBar(void)
{

}

int CObjListBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	//m_objListWnd=new CObjListWnd(this);
	//m_objListWnd->ShowWindow(SW_SHOW);
	m_tree.Create(WS_VISIBLE | WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_BORDER | TVS_EDITLABELS | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_FULLROWSELECT, CRect(0,0,0,0),this,1);
	//m_tree.SetItemHeight(1,20);

	return 0;
}

void CObjListBar::OnSize(UINT nType, int cx, int cy)
{
	CSizingControlBar::OnSize(nType, cx, cy);
	//m_objListWnd->MoveWindow(CRect(0,0,cx,cy));
	m_tree.MoveWindow(CRect(0,0,cx,cy));
}

void CObjListBar::DoDataExchange(CDataExchange* pDX)
{
	CSizingControlBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommandWnd)
	//DDX_Control(pDX,ID_COMMAND_EDIT,m_Edit);
	DDX_Control(pDX,1,m_tree);
	//}}AFX_DATA_MAP}
}

void CObjListBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHandler)
{
	CSizingControlBar::OnUpdateCmdUI(pTarget, bDisableIfNoHandler);
	UpdateDialogControls(pTarget, bDisableIfNoHandler);
}