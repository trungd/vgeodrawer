#include "stdafx.h"
#include "VGObject.h"

CVGButton::CVGButton()
{
	m_Type=OBJ_BUTTON;
	m_minHeight=30;
	m_minWidth=30;
}

CVGButton::~CVGButton()
{
	
}

void CVGButton::Draw(Graphics* gr, CAxisInfo* m_AxisInfo, bool bTrace)
{
	if (!IsVisible()) return;

	CVGBound::Draw(gr,m_AxisInfo,bTrace);

	Rect rect=GetDrawRect();

	Pen pen(m_BorderColor);
	gr->DrawRectangle(&pen,Rect(rect.X-1,rect.Y-1,rect.Width+2,rect.Height+2));

	// 	if (m_HighLight || m_Select)
	// 	{
	// 		Rect rectBig(min(m_Left,m_Left+m_Width),min(m_Top,m_Top+m_Height),abs(m_Width),abs(m_Height));
	// 
	// 		Pen pen(m_Color);pen.SetDashStyle(DashStyleDash);
	// 		gr->DrawRectangle(&pen,rectBig);
	// 	}

	Brush* brush=GetBrush(m_bButtonMouseDown ? m_ColorMouseDown : (m_bButtonMouseOver ? m_ColorMouseOver : m_ColorNormal),rect);
	gr->FillRectangle(brush,rect);
	delete brush;

	Font font(AfxGetMainWnd()->GetDC()->m_hDC,&m_Font);
	Font* f=GetResizeFont(&font,font.GetSize()*nZoom/100);
	SolidBrush textBr(Color::Black);
	StringFormat strFormat;
	strFormat.SetAlignment(StringAlignmentCenter);
	strFormat.SetLineAlignment(StringAlignmentCenter);
	gr->DrawString(m_Text,-1,f,RectF(rect.X,rect.Y,rect.Width,rect.Height),&strFormat,&textBr);
	delete f;
}

bool CVGButton::CheckMouseOverButton(Point pt)
{
	if (!IsVisible()) return false;

	Rect rect=GetDrawRect();
	return rect.Contains(pt);
}