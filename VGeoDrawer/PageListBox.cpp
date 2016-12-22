// PageListBox.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "PageListBox.h"
#include "appfunc.h"

// CGeoObjTreeCtrl

IMPLEMENT_DYNAMIC(CPageListBox, CListBox)

CPageListBox::CPageListBox()
{
	m_contArr=NULL;
}

CPageListBox::~CPageListBox()
{

}


BEGIN_MESSAGE_MAP(CPageListBox, CListBox)
	ON_WM_CONTEXTMENU()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM_REFLECT()
	ON_WM_DRAWITEM_REFLECT()
	ON_WM_DELETEITEM_REFLECT()
	ON_WM_COMPAREITEM_REFLECT()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

void CPageListBox::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: Add your message handler code here
}

void CPageListBox::ResetBitmapArray()
{
	for (int i=0;i<m_bmpArray.GetSize();i++) delete m_bmpArray[i];
	m_bmpArray.RemoveAll();
}

void CPageListBox::FillList()
{
	if (!m_contArr) return;
	SetRedraw(FALSE);
	ResetContent();
	ResetBitmapArray();

	float zoom=nZoom;
	nZoom=(GetItemHeight(-1))*100/(*m_PadHeight);

	for (int i=0;i<m_contArr->GetCount();i++)
	{
		CRect rect; GetClientRect(&rect);

		Bitmap* contBmp=NULL;
		//Graphics contGr(contBmp); contGr.Clear(Color::White);

		//m_contArr->GetAt(i)->DrawBackground(&contGr,contBmp->GetWidth(),contBmp->GetHeight());
		//m_contArr->GetAt(i)->Draw(&contGr,FALSE);
		m_bmpArray.Add(contBmp);
		DrawItemBitmap(i);

		AddString(m_contArr->GetAt(i)->m_Name);
	}
	
	nZoom=zoom;
	SetRedraw(TRUE);
}

void CPageListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	
}

void CPageListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (lpDrawItemStruct->itemID==-1) return;

	Graphics graph(lpDrawItemStruct->hDC);
	//graph.Clear(Color::White);

	Bitmap bmp(lpDrawItemStruct->rcItem.right-lpDrawItemStruct->rcItem.left,lpDrawItemStruct->rcItem.bottom-lpDrawItemStruct->rcItem.top,PixelFormat32bppARGB);
	Graphics gr(&bmp);
	
	Bitmap* contBmp=m_bmpArray[lpDrawItemStruct->itemID];

// 	if (GetCurSel()==lpDrawItemStruct->itemID) 
// 	{
// 		//Color clr; clr.SetFromCOLORREF(::GetSysColor(COLOR_HIGHLIGHT));
// 		//gr.Clear(clr);
// 	}
// 	else 
// 	{
// 		gr.Clear(Color::White);
// 	}
	gr.Clear(Color::White);

	gr.DrawImage(contBmp,ITEM_BORDER,ITEM_BORDER);
	Pen pen(Color::Gray,1);
	gr.DrawRectangle(&pen,ITEM_BORDER,ITEM_BORDER,contBmp->GetWidth(),contBmp->GetHeight());
	if (GetCurSel()==lpDrawItemStruct->itemID) 
	{
		Color clr; clr.SetFromCOLORREF(::GetSysColor(COLOR_HIGHLIGHT));
		Pen pen(clr,3);
 		gr.DrawRectangle(&pen,ITEM_BORDER,ITEM_BORDER,contBmp->GetWidth(),contBmp->GetHeight());
	}
	graph.DrawImage(&bmp,lpDrawItemStruct->rcItem.left,lpDrawItemStruct->rcItem.top);
}

void CPageListBox::DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct)
{
	Invalidate();
}

int CPageListBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	return 0;
}

void CPageListBox::OnSize(UINT nType, int cx, int cy)
{
	CListBox::OnSize(nType, cx, cy);
	RefreshItemSize();
}

void CPageListBox::RefreshItemSize()
{
	if (drPadSize.Width==0) return;
	CRect r;
	GetClientRect(&r);
	SetItemHeight(0,2*ITEM_BORDER+(r.Width()-2*ITEM_BORDER)*drPadSize.Height/drPadSize.Width);
	FillList();
	Invalidate();
}

void CPageListBox::DrawItemBitmap(int nIndex)
{
	//return;
	//if (!IsWindowVisible()) return;
	float zoom=nZoom;
	
	CRect rect; GetClientRect(&rect);
	nZoom=float((rect.Width()-2*ITEM_BORDER)*100)/(drPadSize.Width);

	if (m_bmpArray[nIndex]!=NULL) delete m_bmpArray[nIndex]; 
	//delete contBmp;
	Bitmap* contBmp=new Bitmap(rect.Width()-2*ITEM_BORDER,GetItemHeight(-1)-2*ITEM_BORDER,PixelFormat32bppARGB);
	//Bitmap* contBmp=new Bitmap((rect.Width()-2*ITEM_BORDER),PixelFormat32bppARGB);
	m_bmpArray[nIndex]=contBmp;

	Graphics contGr(contBmp); contGr.Clear(Color::White); contGr.SetSmoothingMode(SmoothingModeAntiAlias);
	m_contArr->GetAt(nIndex)->DrawBackground(&contGr,contBmp->GetWidth(),contBmp->GetHeight());
	m_contArr->GetAt(nIndex)->Draw(&contGr,FALSE);

	nZoom=zoom;

	//DRAWITEMSTRUCT drawItemStruct;
	//drawItemStruct.itemID=nIndex;
	//GetItemRect(nIndex,&drawItemStruct.rcItem);
	//SetRedraw(FALSE);
	Invalidate(FALSE);
	//SetRedraw(TRUE);
	//DrawItem(&drawItemStruct);
}

void CPageListBox::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CListBox::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		FillList();
	}
	else
	{
		ResetBitmapArray();
	}
}
