// ButtonPopup.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "ButtonPopup.h"


// CButtonPopup

IMPLEMENT_DYNAMIC(CButtonPopup, CWnd)

CButtonPopup::CButtonPopup()
{

}

CButtonPopup::~CButtonPopup()
{
	for (int i=0;i<m_btnArray.GetSize();i++)
	{
		delete m_btnArray[i];
	}
	m_btnArray.RemoveAll();
	//ReleaseCapture();
}


BEGIN_MESSAGE_MAP(CButtonPopup, CWnd)
	ON_WM_KILLFOCUS()
	ON_WM_PALETTECHANGED()
	ON_WM_ACTIVATEAPP()
	ON_WM_NCACTIVATE()
	ON_MESSAGE(WM_BTNCLICK,CButtonPopup::OnBtnClk)
END_MESSAGE_MAP()



// CButtonPopup message handlers

void CButtonPopup::AddButton(CString str,HICON hIcon)
{
	CBtnItem* btn=new CBtnItem();
	m_btnArray.Add(btn);
	CRect rc;
	GetClientRect(&rc);
	btn->Create(str,WS_VISIBLE | BS_OWNERDRAW,
		CRect(BTN_DISTANCE,BTN_DISTANCE+(BTN_DISTANCE+BTN_HEIGHT)*(m_btnArray.GetSize()-1),BTN_DISTANCE,(BTN_DISTANCE+BTN_HEIGHT)*m_btnArray.GetSize()),
		this,m_btnArray.GetSize()-1);

	btn->SetIcon(hIcon);
}

void CButtonPopup::DeleteAllButtons()
{
	for (int i=0;i<m_btnArray.GetSize();i++)
	{
		delete m_btnArray[i];
	}
	m_btnArray.RemoveAll();
}

BOOL CButtonPopup::Create(CWnd* pParentWnd)
{
	CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|CS_HREDRAW|CS_VREDRAW,
		0,
		(HBRUSH) (COLOR_BTNFACE+1), 
		0);

// 	CWnd* pTopParent = pParentWnd->GetParentOwner();

// 	if ( pTopParent != NULL )
// 		pTopParent->SetRedraw( FALSE );

	if (!CWnd::CreateEx(0, szClassName, _T(""), WS_POPUP, 
		CRect(0,0,0,0), // size updated soon
		pParentWnd, 0, NULL))
		return FALSE;

	//this->ModifyStyleEx(0,WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,0);

	m_pParentWnd=pParentWnd;
// 	if ( pTopParent != NULL )
// 		pTopParent->SetRedraw( TRUE );

// 	for (int i=0;i<m_strArray.GetSize();i++)
// 	{
// 		CBtnItem* btn=new CBtnItem();
// 		m_btnArray.Add(btn);
// 		CRect rc;
// 		GetClientRect(&rc);
// 		btn->Create(m_strArray[i],WS_VISIBLE | BS_OWNERDRAW,
// 			CRect(BTN_DISTANCE,BTN_DISTANCE+(BTN_DISTANCE+BTN_HEIGHT)*(m_btnArray.GetSize()-1),BTN_DISTANCE,(BTN_DISTANCE+BTN_HEIGHT)*m_btnArray.GetSize()),
// 			this,m_btnArray.GetSize()-1);
// 
// 		//btn->SetIcon(hIcon);
// 	}

	return TRUE;//CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CButtonPopup::Popup(CPoint pt)
{
	CSize size;
	int w=0;
	for (int i=0;i<m_btnArray.GetSize();i++)
		if (m_btnArray[i]->GetIdealWidth()>w) w=m_btnArray[i]->GetIdealWidth();

	for (int i=0;i<m_btnArray.GetSize();i++)
	{
		m_btnArray[i]->MoveWindow(CRect(BTN_DISTANCE,
			BTN_DISTANCE+(BTN_DISTANCE+BTN_HEIGHT)*(i),
			w-BTN_DISTANCE,
			(BTN_DISTANCE+BTN_HEIGHT)*(i+1)));
	}

	size.cx=w;
	size.cy=BTN_DISTANCE+(BTN_HEIGHT+BTN_DISTANCE)*m_btnArray.GetCount();

// 	CWnd* pTopParent = AfxGetApp()->GetMainWnd();//m_pParentWnd;//->GetParentOwner();
// 
// 	if ( pTopParent != NULL )
// 		pTopParent->SetRedraw( FALSE );

	MoveWindow(CRect(pt,size));
	ShowWindow(SW_SHOWNA);
	//if (GetCapture()!=this) SetCapture();
	//SetFocus();

// 	if ( pTopParent != NULL )
// 	{
// 		//pTopParent->SendMessage( WM_NCACTIVATE, TRUE );
// 		pTopParent->SendMessage(WM_ACTIVATE,TRUE);
// 		pTopParent->SetRedraw( TRUE );
// 	}

//  	if ( pTopParent != NULL )
//  		pTopParent->SetRedraw( TRUE );
 
//  	pTopParent->RedrawWindow();
//  	m_pParentWnd->RedrawWindow();

// 	SetFocus();
// 	SetCapture();
}

void CButtonPopup::ClosePopup()
{
	//ReleaseCapture();
// 	CWnd* pTopParent = AfxGetApp()->GetMainWnd();//m_pParentWnd;//->GetParentOwner();
// 
// 	if ( pTopParent != NULL )
// 		pTopParent->SetRedraw( FALSE );
	
	//if (GetCapture()==this) ReleaseCapture();
	ShowWindow(SW_HIDE);

// 	if ( pTopParent != NULL )
// 	{
// 		pTopParent->SendMessage( WM_ACTIVATE, TRUE );
// 		pTopParent->SetRedraw( TRUE );
// 	}
// 
// 	pTopParent->RedrawWindow();
// 	m_pParentWnd->RedrawWindow();
}

void CButtonPopup::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	//ShowWindow(SW_HIDE);
}

LRESULT CButtonPopup::OnBtnClk(WPARAM wParam, LPARAM lParam)
{
	ClosePopup();
	m_pParentWnd->SendMessage(WM_MENUCLICK,wParam,0);
	return TRUE;
}

void CButtonPopup::OnActivateApp(BOOL bActive, DWORD dwThreadID)
{
	CWnd::OnActivateApp(bActive, dwThreadID);

	// TODO: Add your message handler code here
}

BOOL CButtonPopup::OnNcActivate(BOOL bActive)
{
	
	//return TRUE;
	return CWnd::OnNcActivate(bActive);
}
