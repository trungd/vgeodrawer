// CommandPromptListBox.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "CommandPromptListBox.h"


// CCommandPromptListBox

IMPLEMENT_DYNAMIC(CCommandPromptListBox, CListBox)

CCommandPromptListBox::CCommandPromptListBox()
{
	m_currentEditLine=-1;
	m_bIBeam=false;
}

CCommandPromptListBox::~CCommandPromptListBox()
{
}


BEGIN_MESSAGE_MAP(CCommandPromptListBox, CListBox)
//	ON_WM_COMPAREITEM()
	ON_WM_MEASUREITEM_REFLECT()
	ON_WM_DRAWITEM_REFLECT()
	ON_WM_DELETEITEM_REFLECT()
	ON_WM_COMPAREITEM_REFLECT()
	ON_WM_MOUSEMOVE()
	ON_CONTROL_REFLECT(LBN_SELCHANGE, &CCommandPromptListBox::OnLbnSelchange)
	ON_MESSAGE(WM_EDIT_ENTER, &CCommandPromptListBox::OnEditEnter)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

void CCommandPromptListBox::Create( const RECT& rect, CWnd* pParentWnd, UINT nID )
{
	CListBox::Create(WS_BORDER | WS_VISIBLE | WS_CHILD | LBS_NOINTEGRALHEIGHT | 
		LBS_OWNERDRAWVARIABLE | LBS_HASSTRINGS | WS_VSCROLL,rect,pParentWnd,nID);

	m_Edit.Create(WS_CHILD, CRect(0,0,0,0),this,10);

	AddString(L"");
}

void CCommandPromptListBox::Reset()
{
	ResetContent();
	AddString(L"");
	SetCurrentEdit(0);
}


// CCommandPromptListBox message handlers

void CCommandPromptListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if (lpMeasureItemStruct->itemID%2==0) lpMeasureItemStruct->itemHeight=20;
	else lpMeasureItemStruct->itemHeight=GetItemHeight(lpMeasureItemStruct->itemID);
}

void CCommandPromptListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (lpDrawItemStruct->itemID > GetCount()) return;

	Graphics gr(lpDrawItemStruct->hDC);
	FontFamily fontFamily(L"Courier New");
	Font font(&fontFamily,10,FontStyleRegular);

	Rect rc=Rect(lpDrawItemStruct->rcItem.left,lpDrawItemStruct->rcItem.top,
		lpDrawItemStruct->rcItem.right-lpDrawItemStruct->rcItem.left,
		lpDrawItemStruct->rcItem.bottom-lpDrawItemStruct->rcItem.top);

	CString strText;
	GetText(lpDrawItemStruct->itemID,strText);

	if (lpDrawItemStruct->itemID%2==0)
	{
		CClientDC dc(this);
		CFont font;
		font.CreatePointFont(100,L"Courier New");
		CFont* oldFont=dc.SelectObject(&font);
		dc.TextOut(rc.X+2,rc.Y+2,L"[> "+strText);
		dc.SelectObject(oldFont);

// 		SolidBrush fontBr(Color(0,0,0));
// 		gr.DrawString(L"[> "+strText,-1,&font,PointF(rc.X+2,rc.Y+2),NULL,&fontBr);
	}
	else
	{
		Bitmap* bmp;
		if (strText[0]=='#')
		{
			Font font(L"Courier New",10);
			bmp=CMathDraw::DrawText(strText.Right(strText.GetLength()-1),Color::Red,&font);
			gr.DrawImage(bmp,20,rc.Y);
		}
		else
		{
			Font font(L"Times New Roman",10);
			bmp=CMathDraw::DrawText(strText,Color(0,0,255),&font);
			gr.DrawImage(bmp,(rc.Width-bmp->GetWidth())/2,rc.Y);
		}
		//SolidBrush fontBr(Color(0,0,0));
		//gr.DrawString(strText,-1,&font,PointF(rc.X+2,rc.Y+2),NULL,&fontBr);
		delete bmp;
	}
}

void CCommandPromptListBox::DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct)
{
	// TODO: Add your message handler code here
}

int CCommandPromptListBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	// TODO:  Replace the next line with your message handler code
	return 0;
}

void CCommandPromptListBox::OnMouseMove(UINT nFlags, CPoint point)
{
// 	BOOL bOutside;
// 	int index=ItemFromPoint(point,bOutside);
// 
// 	m_bIBeam=(index%2==0);
// 	SetCursor(AfxGetApp()->LoadStandardCursor(m_bIBeam ? IDC_IBEAM : IDC_ARROW));

	CListBox::OnMouseMove(nFlags, point);
}

void CCommandPromptListBox::OnLbnSelchange()
{
	int index=GetCurSel();
	if (index%2==0)
	{
		CRect rect;
		GetItemRect(index,rect);

		m_Edit.MoveWindow(rect);
		m_Edit.ShowWindow(SW_SHOW);
		CString strText;
		GetText(index,strText);

		m_Edit.SetWindowText(strText);
	}
	else m_Edit.ShowWindow(SW_HIDE);
}

BOOL CCommandPromptListBox::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	//HCURSOR hCursor=AfxGetApp()->LoadStandardCursor(IDC_IBEAM);
	//SetCursor(hCursor);

	//return TRUE;
	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);
	CRect rc;
	GetClientRect(rc);

	SetCursor(AfxGetApp()->LoadStandardCursor(PtInRect(rc,pt) ? IDC_IBEAM : IDC_ARROW));
	return TRUE;

	return CListBox::OnSetCursor(pWnd, nHitTest, message);
}

void CCommandPromptListBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	BOOL bOutside;
	int index=ItemFromPoint(point,bOutside);

	if (index%2==0)
	{
		if (m_currentEditLine!=index)
		{
			SetCurrentEdit(index);		
			m_Edit.SendMessage(WM_LBUTTONDOWN,(WPARAM)nFlags,(LPARAM)((point.x-26 << 16) | 1));
			int pos=m_Edit.CharFromPos(CPoint(point.x-26,1));
			m_Edit.SetSel(pos,pos);
		}
		else
		{
			m_Edit.SendMessage(WM_LBUTTONDOWN, nFlags, MAKELPARAM(point.x-26,point.y));
		}
	}
	//else m_Edit.ShowWindow(SW_HIDE);

	//CListBox::OnLButtonDown(nFlags, point);
}

void CCommandPromptListBox::SetCurrentEdit(int nIndex)
{
	CRect rect;
	GetItemRect(nIndex,rect);

	CString strText;
	GetText(nIndex,strText);

	m_Edit.SetWindowText(strText);

	m_Edit.MoveWindow(CRect(rect.left+26,rect.top+2,rect.right,rect.top+2+20));
	m_Edit.ShowWindow(SW_SHOWNORMAL);

	m_Edit.SetFocus();
	//m_Edit.SendMessage(WM_LBUTTONUP,(WPARAM)nFlags,(LPARAM)((point.x << 16) | point.y));
	//m_Edit.ShowCaret();
	
	m_currentEditLine=nIndex;
}

int CCommandPromptListBox::GetOutputHeight(CString strOutput)
{
	if (strOutput==L"") return 1;
	if (strOutput[0]=='#')
	{
		Font font(L"Courier New",10);
		Graphics gr(AfxGetApp()->GetMainWnd()->m_hWnd);
		gr.SetPageUnit(UnitPixel);
		RectF rect;
		gr.MeasureString(strOutput,-1,&font,PointF(0,0),&rect);
		return rect.Height;
	}
	else
	{
		Bitmap* bmp;
		Font font(L"Times New Roman",10);
		bmp=CMathDraw::DrawText(strOutput,Color(0,0,255),&font);
		int height=bmp->GetHeight();
		delete bmp;
		return height;
	}
}

LRESULT CCommandPromptListBox::OnEditEnter(WPARAM wParam, LPARAM lParam)
{
	m_Edit.ShowWindow(SW_HIDE);
	CString str;
	m_Edit.GetWindowText(str);

	SetRedraw(FALSE);
	
	if (str==L"Clear")
	{
		ResetContent();
		AddString(L"");
		SetCurrentEdit(0);
		Invalidate();
		return 0;
	}
// 	else if (str==L"Animate")
// 	{
// 		m_objContainer->pView->OnStartAnimate();
// 	}
// 	else if (str==L"StopAnimate")
// 	{
// 		m_objContainer->pView->OnPauseAnimate();
// 	}

	int i=CListBox::GetTopIndex();
	DeleteString(m_currentEditLine);
	InsertString(m_currentEditLine,str);

	CString strOutput;
	m_objContainer->AddCommand(str,NULL,&strOutput);
	m_objContainer->pView->Draw();
	
	if (m_currentEditLine+1==GetCount())
	{
		AddString(strOutput);
		SetItemHeight(GetCount()-1,GetOutputHeight(strOutput));
		AddString(L"");
		SetItemHeight(GetCount()-1,GetOutputHeight(strOutput));
		SetTopIndex(GetCount()-1);
		SetCurrentEdit(GetCount()-1);
		//SetTopIndex(GetCount()-1);
	}
	else
	{
		DeleteString(m_currentEditLine+1);
		InsertString(m_currentEditLine+1,strOutput);
		SetItemHeight(m_currentEditLine+1,GetOutputHeight(strOutput));
		SetTopIndex(i);
	}
	//this->SetTopIndex(i);

	SetRedraw(TRUE);
	//Invalidate();

	return 0;
}

void CCommandPromptListBox::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	Invalidate();

	CListBox::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CCommandPromptListBox::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//CListBox::OnLButtonDblClk(nFlags, point);
}
