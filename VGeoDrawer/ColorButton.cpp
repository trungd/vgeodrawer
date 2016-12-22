// BtnItem.cpp : implementation file
//

#include "stdafx.h"
#include "VGeoDrawer.h"
#include "ColorButton.h"


// CBtnItem

IMPLEMENT_DYNAMIC(CColorButton, CButton)

CColorButton::CColorButton()
{
	m_bMouseMove=FALSE;
	m_bMouseDown=FALSE;
}

CColorButton::~CColorButton()
{

}


BEGIN_MESSAGE_MAP(CColorButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	//	ON_WM_TIMER()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CBtnItem message handlers

void CColorButton::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)
{
	Graphics gr(this->m_hWnd);
	CRect r; GetClientRect(&r);

	Rect rect(r.left,r.top,r.Width()-1,r.Height()-1);

	gr.Clear(m_Color);

	Pen pen(Color::Gray);
	gr.DrawRectangle(&pen,rect);

	if (m_bMouseMove && !m_bMouseDown)
	{
		Pen pen2(Color::White);
		rect.Inflate(-1,-1);
		gr.DrawRectangle(&pen2,rect);
	}
}

void CColorButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	this->SetCapture();
	m_bMouseDown=TRUE;

	CButton::OnLButtonDown(nFlags, point);
}

void CColorButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (GetCapture()==this)
	{ 
		m_bMouseDown=FALSE; 
		ReleaseCapture(); 
		
		CColorDialog dlg(m_Color.ToCOLORREF());
		if (dlg.DoModal()==IDOK)
		{
			m_Color.SetFromCOLORREF(dlg.GetColor());
		}
		this->GetParent()->SendMessage(WM_BTN_COLOR_CHANGED, 0, 0);
	}

	CButton::OnLButtonUp(nFlags, point);
}

void CColorButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bMouseMove)
	{
		m_bMouseMove = TRUE;
		Invalidate();
		m_nTimer=SetTimer(TimerID, 10, NULL);
	}

	CButton::OnMouseMove(nFlags, point);
}

void CColorButton::OnTimer(UINT_PTR nIDEvent)
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

void CColorButton::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	
}