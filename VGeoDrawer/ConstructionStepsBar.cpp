#include "StdAfx.h"
#include "ConstructionStepsBar.h"

BEGIN_MESSAGE_MAP(CConstructionStepsBar, CSizingControlBar)
	//{{AFX_MSG_MAP(CConstructionStepsBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CConstructionStepsBar::CConstructionStepsBar(void)
{
	m_objArray=NULL;
}

CConstructionStepsBar::~CConstructionStepsBar(void)
{
}

int CConstructionStepsBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_List.Create(WS_VISIBLE | WS_CHILD | LBS_NOINTEGRALHEIGHT | LBS_HASSTRINGS | LBS_OWNERDRAWFIXED | WS_VSCROLL,CRect(0,0,0,0),this,0);
	m_List.ModifyStyleEx(0,WS_EX_CLIENTEDGE);

	return 0;
}

void CConstructionStepsBar::OnSize(UINT nType, int cx, int cy)
{
	CSizingControlBar::OnSize(nType, cx, cy);
	m_List.MoveWindow(CRect(0,0,cx,cy));
}

void CConstructionStepsBar::DoDataExchange(CDataExchange* pDX)
{
	CSizingControlBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommandWnd)
	//}}AFX_DATA_MAP}
}

void CConstructionStepsBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHandler)
{
	CSizingControlBar::OnUpdateCmdUI(pTarget, bDisableIfNoHandler);
	UpdateDialogControls(pTarget, bDisableIfNoHandler);
}

void CConstructionStepsBar::AddCommand(CString str)
{
	CString s=str;
	s.Remove('~');
	m_List.AddString(s);
	m_List.SetCurSel(m_List.GetCount()-1);
	m_List.GetMaxStringSize();
}

void CConstructionStepsBar::Reload()
{
	return;
	if (m_objArray==NULL) return;
	m_List.SetRedraw(FALSE);
	m_List.ResetContent();
	int cmdIndex=0;
	for (int i=0;i<m_objArray->GetSize();i++)
	{
		if (m_objArray->GetAt(i)->m_bTemp) continue;
		if (m_objArray->GetAt(i)->m_cmdIndex>cmdIndex)
		{
			cmdIndex=m_objArray->GetAt(i)->m_cmdIndex;
			AddCommand((m_objArray->GetAt(i))->m_Definition);
		}
	}
	m_List.SetRedraw(TRUE);
}