// BtnItem.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "BtnItem.h"


// CBtnItem

IMPLEMENT_DYNAMIC(CBtnItem, CButton)

CBtnItem::CBtnItem()
{
	m_bMouseMove=FALSE;
	m_bMouseDown=FALSE;
	m_bCheck=FALSE;
	m_Bitmap=NULL;
}

CBtnItem::~CBtnItem()
{
	delete m_Bitmap;
}


BEGIN_MESSAGE_MAP(CBtnItem, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
//	ON_WM_TIMER()
ON_WM_TIMER()
END_MESSAGE_MAP()



// CBtnItem message handlers

int CBtnItem::GetIdealWidth()
{
	Graphics graph(this->m_hWnd);

	CString strText;
	CRect r; GetClientRect(&r);
	GetWindowText(strText);
	Font font(L"Verdana",8);
	RectF rect;
	graph.MeasureString(strText,strText.GetLength(),&font,PointF(0,0),&rect);

	// Draw the text

	if (m_Bitmap==NULL)
		return rect.Width+20;
	else 
		return r.Height()+rect.Width+20;
}

void CBtnItem::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)
{
	Graphics graph(this->m_hWnd);
	CRect r; GetClientRect(&r);
	Bitmap bmp(r.Width(),r.Height(),PixelFormat32bppARGB);
	Graphics gr(&bmp);

	Rect rect(r.left,r.top,r.Width()-1,r.Height()-1);
	CString strText;
	Color BackColor=Color(245,245,245);
	GetWindowText(strText);

	if (m_bMouseDown)
	{
		LinearGradientBrush br(rect,BackColor,Color::White,LinearGradientModeVertical);
		gr.FillRectangle(&br,rect);
	}
	else if (m_bMouseMove)
	{
		LinearGradientBrush br(rect,Color::White,BackColor,LinearGradientModeVertical);
		gr.FillRectangle(&br,rect);
	}
// 	else if (m_bCheck)
// 	{
// 		LinearGradientBrush br(rect,Color(240,240,240),Color(230,230,230),LinearGradientModeVertical);
// 		gr.FillRectangle(&br,rect);		
// 	}
	else
	{
		LinearGradientBrush br(rect,BackColor,Color::White,LinearGradientModeVertical);
		gr.FillRectangle(&br,rect);
// 		SolidBrush br(BackColor);
// 		gr.FillRectangle(&br,Rect(0,0,rect.Width+1,rect.Height+1));
	}
	if (m_bCheck)
	{
		Pen pen(Color(50,50,50));
		gr.DrawRectangle(&pen,rect);
	}
	else
	{
		Pen pen(Color(192,192,192));
		gr.DrawRectangle(&pen,rect);
	}

	// Draw the text

	int imgDis=(rect.Height-(m_Bitmap==NULL ? 0 : m_Bitmap->GetHeight()))/2;

	if (!strText.IsEmpty())
	{
		Font font(L"Verdana",8);

		StringFormat strF;
		strF.SetLineAlignment(StringAlignmentCenter);
		if (m_bMouseDown)
		{
			SolidBrush br(Color(0,0,0));
			gr.DrawString(strText,-1,&font,PointF(rect.Height+1,rect.Height/2+1),&strF,&br);
		}
		else 
		{
			SolidBrush br(Color(0,0,0));
			gr.DrawString(strText,-1,&font,PointF(rect.Height,rect.Height/2),&strF,&br);
		}
	}
	if (m_Bitmap!=NULL)
	{
		int x=m_Bitmap->GetWidth();
		ImageAttributes imageAttr;
		ColorMap whiteToNo;
		Color clr;
		m_Bitmap->GetPixel(1,1,&clr);
		whiteToNo.newColor=Color(0,255,255,255);
		whiteToNo.oldColor=clr;
		imageAttr.SetRemapTable(1,&whiteToNo);
		Rect rect(imgDis,imgDis,
			(int)m_Bitmap->GetWidth(),(int)m_Bitmap->GetHeight());
		gr.DrawImage(m_Bitmap,rect,0,0,(int)m_Bitmap->GetWidth(),(int)m_Bitmap->GetHeight(),UnitPixel,&imageAttr);
	}
	graph.DrawImage(&bmp,0,0);
}

void CBtnItem::OnLButtonDown(UINT nFlags, CPoint point)
{
	this->SetCapture();
	m_bMouseDown=TRUE;

	CButton::OnLButtonDown(nFlags, point);
}

void CBtnItem::SetCheck(BOOL bCheck)
{
	m_bCheck=bCheck;
	Invalidate(TRUE);
}

void CBtnItem::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (GetCapture()==this)
	{ 
		m_bMouseDown=FALSE; 
		ReleaseCapture(); 
		GetParent()->SendMessage(WM_BTNCLICK,(WPARAM)this,0);
	}

	CButton::OnLButtonUp(nFlags, point);
}

void CBtnItem::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bMouseMove)
	{
		m_bMouseMove = TRUE;
		Invalidate();
		m_nTimer=SetTimer(TimerID, 10, NULL);
	}
	GetParent()->SendMessage(WM_BTNMOUSEMOVE,(WPARAM)this);

	CButton::OnMouseMove(nFlags, point);
}

void CBtnItem::SetIcon(HICON hIcon)
{
	if (m_Bitmap!=NULL) delete m_Bitmap;
	m_Bitmap=new Bitmap(hIcon);
}

void CBtnItem::OnTimer(UINT_PTR nIDEvent)
{
	CPoint p(GetMessagePos());
	ScreenToClient(&p);

	CRect rect;
	GetClientRect(rect);

	if (!rect.PtInRect(p))
	{
		m_bMouseMove = FALSE;
		KillTimer(m_nTimer);
		Invalidate(FALSE);
	}

	CButton::OnTimer(nIDEvent);
}
