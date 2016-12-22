// StyleComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "StyleComboBox.h"
#include "VGObject.h"


// CStyleComboBox

IMPLEMENT_DYNAMIC(CStyleComboBox, CComboBox)

CStyleComboBox::CStyleComboBox()
{

}

CStyleComboBox::~CStyleComboBox()
{
}


BEGIN_MESSAGE_MAP(CStyleComboBox, CComboBox)
	ON_WM_MEASUREITEM()
	ON_WM_COMPAREITEM()
END_MESSAGE_MAP()



// CStyleComboBox message handlers



void CStyleComboBox::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight=30;
}

void CStyleComboBox::SetLineStyleComboBox()
{
	for (int i=0;i<6;i++) AddString(L"");
	SetItemHeight(0,20);
}

void CStyleComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ASSERT(lpDrawItemStruct->CtlType == ODT_COMBOBOX);	

	Graphics gr(lpDrawItemStruct->hDC);
	Rect rc(lpDrawItemStruct->rcItem.left,lpDrawItemStruct->rcItem.top,lpDrawItemStruct->rcItem.right-lpDrawItemStruct->rcItem.left-1,lpDrawItemStruct->rcItem.bottom-lpDrawItemStruct->rcItem.top-1);
	SolidBrush whiteBrush(Color(255,255,255));
	gr.FillRectangle(&whiteBrush,Rect(rc.GetLeft(),rc.GetTop(),rc.Width+1,rc.Height+1));

	//SolidBrush br(Color(255, 255, 255));
	//gr.FillRectangle(&br,rc);

	if ((lpDrawItemStruct->itemState & ODS_SELECTED))// &&                         
		//(lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		Color clr;
		clr.SetFromCOLORREF(GetSysColor(COLOR_HIGHLIGHT));
		Pen pen(clr,1);
		gr.DrawRectangle(&pen,rc);
	}

	Pen pen(Color(0,0,0));
 	GetPen(lpDrawItemStruct->itemID, &pen);
	gr.DrawLine(&pen,Point(5,9+lpDrawItemStruct->rcItem.top),Point(lpDrawItemStruct->rcItem.right-5,lpDrawItemStruct->rcItem.top+9));


// 	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
// 
// 	if ((lpDrawItemStruct->itemState & ODS_SELECTED) &&                         
// 		(lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
// 	{
// 		CBrush br(RGB(255, 255, 255));
// 		pDC->FillRect(&lpDrawItemStruct->rcItem, &br);
// 		
// 		COLORREF crHilite = GetSysColor(COLOR_HIGHLIGHT);
// 		CPen pen(PS_SOLID,1,crHilite);
// 		CPen* oldpen = pDC->SelectObject(&pen);
// 		pDC->Rectangle(&lpDrawItemStruct->rcItem);
// 		pDC->SelectObject(oldpen);
// 	}
// 
// 	if (!(lpDrawItemStruct->itemState & ODS_SELECTED) &&
// 		(lpDrawItemStruct->itemAction & ODA_SELECT))
// 	{
// 		CBrush br(RGB(255, 255, 255));
// 		pDC->FillRect(&lpDrawItemStruct->rcItem, &br);
// 	}
// 
// 	CPen pen;
// 	switch (lpDrawItemStruct->itemID)
// 	{
// 	case 0:pen.CreatePen(PS_SOLID,1,RGB(0,0,0));break;
// 	case 1:pen.CreatePen(PS_DASH,1,RGB(0,0,0));break;
// 	case 2:pen.CreatePen(PS_DASHDOT,1,RGB(0,0,0));break;
// 	case 3:pen.CreatePen(PS_DASHDOTDOT,1,RGB(0,0,0));break;
// 	}	
// 	CPen* oldPen=pDC->SelectObject(&pen);
// 	pDC->MoveTo(0,9+lpDrawItemStruct->rcItem.top);
// 	pDC->LineTo(lpDrawItemStruct->rcItem.right,lpDrawItemStruct->rcItem.top+9);
// 	pDC->SelectObject(oldPen);
}

int CStyleComboBox::OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	return 0;
	//return CComboBox::OnCompareItem(nIDCtl, lpCompareItemStruct);
}