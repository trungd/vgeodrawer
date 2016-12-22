// ObjToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "ObjToolBar.h"
#include "resource.h"
#include "appfunc.h"

// CObjToolBar

IMPLEMENT_DYNAMIC(CObjToolBar, CSizingControlBar)

CObjToolBar::CObjToolBar()
{
	m_bSelecting=FALSE;
}

CObjToolBar::~CObjToolBar()
{
	delete popup;
	RemoveAll();
}

BEGIN_MESSAGE_MAP(CObjToolBar, CSizingControlBar)
	ON_WM_CREATE()
	ON_MESSAGE(WM_BTNCLICK,CObjToolBar::OnBtnClk)
	ON_MESSAGE(WM_BTNMOUSEMOVE,CObjToolBar::OnBtnMouseMove)
	ON_MESSAGE(WM_MENUCLICK,CObjToolBar::OnMenuClk)
	ON_WM_CONTEXTMENU(CObjToolBar::OnContextMenu)
	ON_WM_SIZE()

END_MESSAGE_MAP()



// CObjToolBar message handlers



int CObjToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

// 	popup=new CButtonPopup();
// 	popup->Create(this);
	//dlg=new CObjBtnDlg(this);
	//dlg->tbWnd=this;

	popup=NULL;

	//m_Menu.CreateMenu();
	//LoadButtons();

	//LoadButtons();
	
	return 0;
}

void CObjToolBar::OnCommand(UINT nIndex)
{
	CString strText=m_btnTextArray[m_nSelection]->GetAt(nIndex-TOOL_MENU_START);
	m_btnArray[m_nSelection]->SetIcon(pDoc->m_cmdArray.m_ImageList.ExtractIcon(pDoc->m_cmdArray.GetToolImageIndex(strText)));
	m_btnArray[m_nSelection]->SetWindowText(strText);
	pDoc->SetToolMode(strText);
}

void CObjToolBar::OnUpdateCommand(UINT nIndex, CCmdUI* pCmdUI)
{
	CString strText1=m_btnTextArray[m_nSelection]->GetAt(nIndex);
	CString strText2; m_btnArray[m_nSelection]->GetWindowText(strText2);
	pCmdUI->SetCheck(strText1==strText2);
}

LRESULT CObjToolBar::OnBtnClk(WPARAM wParam, LPARAM lParam)
{
	//m_Menu.AddToGlobalImageList();
	//m_Menu.AddToGlobalImageList(&cmdArray->m_ImageList)
	
	CWnd* btn=(CWnd*)wParam;
	int index=btn->GetDlgCtrlID();

	if (m_nSelection!=index)
	{
		SetSelection(index);
		CString str;
		btn->GetWindowText(str);
		pDoc->SetToolMode(str);
	}
	else
	{
		m_bSelecting=TRUE;
		PopupMenu(index);
	}

	//m_Menu.Detach();
	
// 	if (popup!=NULL)
// 	{
// 		popup->DestroyWindow();
// 		delete popup;
// 	}
// 	popup=new CButtonPopup();
// 	popup->Create(this);
// 	CWnd* btn=(CWnd*)wParam;
// 	int index=btn->GetDlgCtrlID();
// 	if (m_nSelection!=index)
// 	{
// 		SetSelection(index);
// 		CString str;
// 		btn->GetWindowText(str);
// 		pDoc->SetToolMode(str);
// 	}
// 	else
// 	{
// 		m_bSelecting=TRUE;
// 		CCommandArray* cmdArray=&pDoc->m_cmdArray;
// 		popup->DeleteAllButtons();
// 		for (int i=0;i<m_btnTextArray[index]->GetSize();i++)
// 		{
// 			popup->AddButton(m_btnTextArray[index]->GetAt(i),
// 				cmdArray->m_ImageList.ExtractIcon(cmdArray->GetToolImageIndex(m_btnTextArray[index]->GetAt(i))));
// 		}
// 		CRect rc;
// 		GetClientRect(&rc);
// 		ClientToScreen(rc);
// 		if (m_bHorz)
// 			popup->Popup(CPoint(rc.left+BUTTON_DISTANCE+index*(BUTTON_SIZE+BUTTON_DISTANCE),rc.bottom));
// 		else
// 			popup->Popup(CPoint(rc.right,rc.top+BUTTON_DISTANCE+index*(BUTTON_SIZE+BUTTON_DISTANCE)));
// 	}
	return TRUE;
}

LRESULT CObjToolBar::OnMenuClk(WPARAM wParam, LPARAM lParam)
{
	//popup->OnKillFocus(AfxGetApp()->GetMainWnd());
	//AfxGetApp()->GetMainWnd()->SetActiveWindow();
	//AfxGetApp()->GetMainWnd()->SetFocus();
	CBtnItem* btnItem=(CBtnItem*)wParam;
	m_bSelecting=FALSE;
	HICON hIcon;
	btnItem->m_Bitmap->GetHICON(&hIcon);
	m_btnArray[m_nSelection]->SetIcon(hIcon);
	CString str;
	btnItem->GetWindowText(str);
	m_btnArray[m_nSelection]->SetWindowText(str);
	pDoc->SetToolMode(str);
	popup->DestroyWindow();
	//delete popup;
	popup=NULL;
	return TRUE;
}

void CObjToolBar::PopupMenu(int index, bool bAnimate)
{
	CCommandArray* cmdArray=&pDoc->m_cmdArray;

	BCMenu bcMenu;
	bcMenu.xp_draw_3D_bitmaps=FALSE;

	bcMenu.CreatePopupMenu();
	bcMenu.SetIconSize(32,32);
	
	cmdArray->m_ImageList.SetBkColor(RGB(254,254,254));
	bcMenu.SetBitmapBackground(RGB(254,254,254));

	for (int i=0;i<m_btnTextArray[index]->GetSize();i++)
	{
		CString s=m_btnTextArray[index]->GetAt(i);
		wchar_t* str=s.GetBuffer(255);
		bcMenu.AppendODMenuW(str,MF_STRING,i+TOOL_MENU_START,&pDoc->m_cmdArray.m_ImageList,cmdArray->GetToolImageIndex(m_btnTextArray[index]->GetAt(i)));
		s.ReleaseBuffer(255);
		//cmdArray->m_ImageList.ExtractIcon(cmdArray->GetToolImageIndex(m_btnTextArray[index]->GetAt(i))));
	}
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(rc);
	UINT flags=bAnimate ? TPM_LEFTALIGN | TPM_RIGHTBUTTON : TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_NOANIMATION;
	switch (m_nDockBarID)
	{
	case AFX_IDW_DOCKBAR_TOP:
		bcMenu.TrackPopupMenu(flags,rc.left+BUTTON_DISTANCE+index*(BUTTON_SIZE+BUTTON_DISTANCE),rc.bottom,AfxGetMainWnd());
		break;
	case AFX_IDW_DOCKBAR_BOTTOM:
		bcMenu.TrackPopupMenu(flags,rc.left+BUTTON_DISTANCE+index*(BUTTON_SIZE+BUTTON_DISTANCE),rc.top,AfxGetMainWnd());
		break;
	case AFX_IDW_DOCKBAR_LEFT:
	case AFX_IDW_DOCKBAR_FLOAT:
		bcMenu.TrackPopupMenu(flags,rc.right,rc.top+BUTTON_DISTANCE+index*(BUTTON_SIZE+BUTTON_DISTANCE),AfxGetMainWnd());
		break;
	case AFX_IDW_DOCKBAR_RIGHT:
		bcMenu.TrackPopupMenu(flags,rc.left,rc.top+BUTTON_DISTANCE+index*(BUTTON_SIZE+BUTTON_DISTANCE),AfxGetMainWnd());
		break;
	}
	bcMenu.SetIconSize(15,16);
	bcMenu.xp_draw_3D_bitmaps=TRUE;
}

LRESULT CObjToolBar::OnBtnMouseMove(WPARAM wParam, LPARAM lParam)
{
// 	CWnd* btn=(CWnd*)wParam;
// 	int index=btn->GetDlgCtrlID();
// 	if (m_bSelecting && index!=m_nSelection)
// 	{
// 		popup->DestroyWindow();
// 		delete popup;
// 		
// 		SetSelection(index);
// 		CCommandArray* cmdArray=&pDoc->m_cmdArray;
// 		popup=new CButtonPopup();
// 		popup->Create(this);
// 		for (int i=0;i<m_btnTextArray[index]->GetSize();i++)
// 		{
// 			popup->AddButton(m_btnTextArray[index]->GetAt(i),
// 				cmdArray->m_ImageList.ExtractIcon(cmdArray->GetToolImageIndex(m_btnTextArray[index]->GetAt(i))));
// 		}
// 		CRect rc;
// 		GetClientRect(&rc);
// 		ClientToScreen(rc);
// 		if (m_bHorz)
// 			popup->Popup(CPoint(rc.left+BUTTON_DISTANCE+index*(BUTTON_SIZE+BUTTON_DISTANCE),rc.bottom));
// 		else
// 			popup->Popup(CPoint(rc.right,rc.top+BUTTON_DISTANCE+index*(BUTTON_SIZE+BUTTON_DISTANCE)));
// 	}
// 	return TRUE;


	
// 	CWnd* btn=(CWnd*)wParam;
// 	int index=btn->GetDlgCtrlID();
// 	if (m_bSelecting && index!=m_nSelection)
// 	{
// 		SetSelection(index);
// 		PopupMenu(index,false);
// 	}
	return TRUE;
}

void CObjToolBar::SetSelection(int nSelection)
{
	for (int i=0;i<m_btnArray.GetSize();i++)
		m_btnArray[i]->SetCheck(FALSE);
	m_btnArray[nSelection]->SetCheck(TRUE);
	m_nSelection=nSelection;
}

void CObjToolBar::RemoveAll()
{
	for (int i=0;i<m_btnTextArray.GetSize();i++)
		delete m_btnTextArray[i];
	m_btnTextArray.RemoveAll();
	for (int i=0;i<m_btnArray.GetSize();i++)
		delete m_btnArray[i];
	m_btnArray.RemoveAll();
}

void CObjToolBar::LoadButtons()
{
	RemoveAll();
	CFile file;
	file.Open(GetAppDirectory()+L"\\data\\tbitem.dat",CFile::modeRead);
	CArchive ar(&file,CArchive::load);
	CString str;

	BOOL b;

	int count;
	ar >> count;
	int imgIndex;
	CCommandArray* cmdArray=&pDoc->m_cmdArray;
	for (int i=0;i<count;i++)
	{
		ar >> str;
		ar >> b;
		imgIndex=pDoc->m_cmdArray.GetToolImageIndex(str);
		if (b)
		{
			CStringArray* strArray=new CStringArray();
			m_btnTextArray.Add(strArray);
			CBtnItem* btnItem=new CBtnItem();
			btnItem->Create(str,WS_VISIBLE | BS_OWNERDRAW, 
				CRect(0,0,0,0),
				this, m_btnArray.GetCount());
			btnItem->SetIcon(cmdArray->m_ImageList.ExtractIcon(cmdArray->GetToolImageIndex(str)));
			m_btnArray.Add(btnItem);
		}
		else 
		{
			m_btnTextArray[m_btnTextArray.GetSize()-1]->Add(str);
		}
	}

	ar.Close();
	file.Close();
	SetSelection(0);
	m_bHorz=!this->IsHorzDocked();
	ReArangeButton();
}

BOOL CObjToolBar::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CSizingControlBar::PreTranslateMessage(pMsg);
}

CSize CObjToolBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
	if (dwMode & LM_HORZDOCK)
	{
		ReArangeButton();
		return CSize(BUTTON_DISTANCE+m_btnArray.GetSize()*(BUTTON_DISTANCE+BUTTON_SIZE)+8,BUTTON_SIZE+2*BUTTON_DISTANCE+8);
	}
	else
	{
		ReArangeButton();
		return CSize(BUTTON_SIZE+2*BUTTON_DISTANCE+8,BUTTON_DISTANCE+m_btnArray.GetSize()*(BUTTON_DISTANCE+BUTTON_SIZE)+8);
	}
	return CSizingControlBar::CalcDynamicLayout(nLength,dwMode);
}

void CObjToolBar::ReArangeButton()
{
	if (m_bHorz==this->IsHorzDocked()) return;
	m_bHorz=this->IsHorzDocked();
	for (int i=0;i<m_btnArray.GetSize();i++)
	{
		CBtnItem* btnItem=(CBtnItem*)m_btnArray[i];
		if (this->IsHorzDocked())
		{
			btnItem->MoveWindow(CRect(
				BUTTON_DISTANCE+(BUTTON_DISTANCE+BUTTON_SIZE)*(i), 
				BUTTON_DISTANCE,
				(BUTTON_DISTANCE+BUTTON_SIZE)*(i+1),
				BUTTON_DISTANCE+BUTTON_SIZE
				));
		}
		else
		{
			btnItem->MoveWindow(CRect(
				BUTTON_DISTANCE,
				BUTTON_DISTANCE+(BUTTON_DISTANCE+BUTTON_SIZE)*(i), 
				BUTTON_DISTANCE+BUTTON_SIZE,
				(BUTTON_DISTANCE+BUTTON_SIZE)*(i+1)
				));
		}
	}
}
void CObjToolBar::OnSize(UINT nType, int cx, int cy)
{
	CSizingControlBar::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}

void CObjToolBar::OnContextMenu( CWnd* pWnd, CPoint pos )
{
	CSizingControlBar::OnContextMenu(pWnd,pos);
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_POPUP));
	CMenu* pPopup = menu.GetSubMenu(4);
	ASSERT(pPopup != NULL);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pos.x, pos.y, AfxGetMainWnd());
}