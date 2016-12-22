// ObjBtnDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "ObjBtnDlg.h"


// CObjBtnDlg dialog

IMPLEMENT_DYNAMIC(CObjBtnDlg, CDialog)

CObjBtnDlg::CObjBtnDlg(CWnd* pParent /*=NULL*/)
{
	CDialog::Create(CObjBtnDlg::IDD,pParent);
}

CObjBtnDlg::~CObjBtnDlg()
{
	DeleteAllButtons();
}

void CObjBtnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX,1,btn);
}


BEGIN_MESSAGE_MAP(CObjBtnDlg, CDialog)
	ON_WM_CREATE()
//	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	ON_WM_KILLFOCUS()
	ON_WM_PAINT()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CObjBtnDlg message handlers

void CObjBtnDlg::OnOK()
{
	
}

BOOL CObjBtnDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetCapture();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CObjBtnDlg::AddButton(CString str,HICON hIcon)
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

void CObjBtnDlg::DeleteAllButtons()
{
	for (int i=0;i<m_btnArray.GetSize();i++)
	{
		delete m_btnArray[i];
	}
	m_btnArray.RemoveAll();
}

void CObjBtnDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
}

void CObjBtnDlg::Popup(CPoint pt)
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

	MoveWindow(CRect(pt,size));

// 	CWnd* pTopParent = GetParent()->GetParentOwner();
// 
// 	if ( pTopParent != NULL )
// 		pTopParent->SetRedraw( FALSE );

	ShowWindow(SW_SHOW);

// 	if ( pTopParent != NULL )
// 	{
// 		pTopParent->SendMessage( WM_NCACTIVATE, TRUE );
// 		pTopParent->SetRedraw( TRUE );
// 	}
}

void CObjBtnDlg::OnKillFocus(CWnd* pNewWnd)
{
	CDialog::OnKillFocus(pNewWnd);

	ReleaseCapture();
}

void CObjBtnDlg::OnPaint()
{
	CWnd::OnPaint();
	Graphics gr(this->m_hWnd);
	CRect rc; GetClientRect(&rc);
	//Pen pen(Color(192,192,192));
	//gr.DrawRectangle(&pen,rc.top,rc.left,rc.Width()-1,rc.Height()-1);
}

LRESULT CObjBtnDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message==WM_BTNCLICK)
	{
		ShowWindow(SW_HIDE);
		tbWnd->SendMessage(WM_MENUCLICK,wParam,0);
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CObjBtnDlg::PreTranslateMessage(MSG* pMsg)
{
	if (GetCapture()->GetSafeHwnd() != m_hWnd)
		SetCapture(); 

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CObjBtnDlg::Create(CWnd* pParentWnd)
{
// 	CWnd* pTopParent = pParentWnd;
// 
// 	if ( pTopParent != NULL )
// 		pTopParent->SetRedraw( FALSE );

	CDialog::Create(CObjBtnDlg::IDD, pParentWnd);

// 	if ( pTopParent != NULL )
// 		pTopParent->SetRedraw( TRUE );

	return TRUE;
}

void CObjBtnDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	// TODO: Add your message handler code here
}
